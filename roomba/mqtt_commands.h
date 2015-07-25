/*
 * mqtt_commands.h
 *
 *  Created on: Jul 22, 2015
 *      Author: marcok
 */

#ifndef MQTT_COMMANDS_H_
#define MQTT_COMMANDS_H_

#define MQTT_ROOMBA_CMD_TOPIC		"pit/roomba/cmd"
#define MQTT_ROOMBA_STATUS_TOPIC	"pit/roomba/state"

#define MQTT_ROOMBA_CMD_WAKEUP		"wakeup"
#define MQTT_ROOMBA_CMD_SLEEP		"sleep"
#define MQTT_ROOMBA_CMD_DOCK		"dock"
#define MQTT_ROOMBA_CMD_CLEAN		"clean"
#define MQTT_ROOMBA_CMD_SPOT_CLEAN	"spot_clean"
#define MQTT_ROOMBA_CMD_MOTORS		"motors"
#define MQTT_ROOMBA_CMD_PLAY_SONG	"play"

#endif /* MQTT_COMMANDS_H_ */
