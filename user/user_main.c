/* main.c -- MQTT client example
*
* Copyright (c) 2014-2015, Tuan PM <tuanpm at live dot com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Redis nor the names of its contributors may be used
* to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/
#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mem.h"
#include "eagle_soc.h"
#include "stdio.h"

#include "roomba.h"
#include "mqtt_commands.h"

#define DEVICE_ID	"123"
#define DEVICE_NAME	"roomba_woonkamer"


MQTT_Client mqttClient;

void ICACHE_FLASH_ATTR mqtt_advertise(MQTT_Client* client){
	struct ip_info ipconfig;
	wifi_get_ip_info(STATION_IF, &ipconfig);

	//assemble advertise string
	char advertise_str[150];

	sprintf(advertise_str, "advertise %s %s %s", DEVICE_ID, DEVICE_NAME, ipconfig.ip);
	MQTT_Publish(client, MQTT_ROOMBA_STATUS_TOPIC, "advertise ", 6, 0, 0);

}

void ICACHE_FLASH_ATTR wifiConnectCb(uint8_t status)
{
	if(status == STATION_GOT_IP){
		MQTT_Connect(&mqttClient);
	} else {
		MQTT_Disconnect(&mqttClient);
	}
}
void ICACHE_FLASH_ATTR mqttConnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Connected\r\n");

	MQTT_Subscribe(client, MQTT_ROOMBA_CMD_TOPIC, 0);

	mqtt_advertise(client);
}

void mqttDisconnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Disconnected\r\n");
}

void mqttPublishedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Published\r\n");
}

bool strEquals(const char *str, const char *match)
{
	return (strcmp(str, match) == 0);

}

bool strStartsWith(const char *str, const char *pre)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}

void get_command(char * buff, char ** command)
{
	char *p = buff;

    while( p != NULL ){
    	p = strchr(p, ' ');

        if( p != NULL){
        	// Found the delimiter, get next char
            p++;
            os_printf("Found command 0x%X\n", *p);
            *command = p;
            break;
        }else{
            p++;
        }
    }
}


void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
	char *topicBuf = (char*)os_zalloc(topic_len+1),
			*dataBuf = (char*)os_zalloc(data_len+1);

	MQTT_Client* client = (MQTT_Client*)args;

	os_memcpy(topicBuf, topic, topic_len);
	topicBuf[topic_len] = 0;

	os_memcpy(dataBuf, data, data_len);
	dataBuf[data_len] = 0;

	INFO("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);

	if(strEquals(topicBuf, MQTT_ROOMBA_CMD_TOPIC) == 0){
		//compare the first token with known commands
		if(strEquals(dataBuf, MQTT_ROOMBA_CMD_WAKEUP)){
			roomba_wakeup();
		}else if(strEquals(dataBuf, MQTT_ROOMBA_CMD_CLEAN)){
			roomba_clean();
		}else if(strEquals(dataBuf, MQTT_ROOMBA_CMD_DOCK)){
			roomba_dock();
		}else if(strEquals(dataBuf, MQTT_ROOMBA_CMD_SLEEP)){
			roomba_sleep();
		}else if(strStartsWith(dataBuf, MQTT_ROOMBA_CMD_MOTORS)){		//controls the cleaning motors (main brush, vaccuum, side brush)
			//get the param
			char *command;
			get_command(dataBuf, &command);

			os_printf("Command is: 0x%X\n", *command);

			roomba_motors(command);
		}else if(strStartsWith(dataBuf, MQTT_ROOMBA_CMD_PLAY_SONG)){
			//make sure the songs are programmed
			roomba_program_songs();

			//get the param
			char *command;
			get_command(dataBuf, &command);

			os_printf("Command is: 0x%X\n", *command);
			roomba_play_song(command);
		}else{
			os_printf("Unknown command received: %s at topic %s\n", dataBuf, topicBuf);
		}
	}

	os_free(topicBuf);
	os_free(dataBuf);
}


void user_init(void)
{
	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	os_delay_us(1000000);

	CFG_Load();

	// Initialize the GPIO subsystem.
    gpio_init();

    //Set GPIO2 to output mode
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
    //Set GPIO2 low
    gpio_output_set(0, ROOMBA_WAKEUP_PIN, ROOMBA_WAKEUP_PIN, 0);

	MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);
	//MQTT_InitConnection(&mqttClient, "192.168.11.122", 1880, 0);

	MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);
	//MQTT_InitClient(&mqttClient, "client_id", "user", "pass", 120, 1);

	MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);
	MQTT_OnConnected(&mqttClient, mqttConnectedCb);
	MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
	MQTT_OnPublished(&mqttClient, mqttPublishedCb);
	MQTT_OnData(&mqttClient, mqttDataCb);

	WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

	INFO("\r\nSystem started ...\r\n");
}
