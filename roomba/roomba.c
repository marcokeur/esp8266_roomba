/*
 * roomba.c
 *
 *  Created on: Jul 22, 2015
 *      Author: marcok
 */

#include "osapi.h"

#include "roomba_opcodes.h"
#include "roomba.h"
#include "uart.h"

void roomba_send_command(char command){
	uart_tx_one_char(command);
	os_delay_us(1000);
}

void roomba_startup(void) {
	os_printf("startup");
	roomba_send_command(START);
	roomba_send_command(SAFE);

	os_delay_us(30000);
}

void roomba_wakeup(void) {
    unsigned char j;

    // Wakeup roomba
    roomba_startup();
    gpio_output_set(0, ROOMBA_WAKEUP_PIN, ROOMBA_WAKEUP_PIN, 0); // ESP01 io2  Low

    for (j = 0; j < 50; j++) // 0,5 Sekunden
    {
        //feedwdt();
        os_delay_us(10000); // 10ms
    }
    gpio_output_set(ROOMBA_WAKEUP_PIN, 0, ROOMBA_WAKEUP_PIN, 0); // ESP01 io2  High

    for (j = 0; j < 100; j++) // 1 Sekunde
    {
        //feedwdt();
        os_delay_us(10000); //10ms
    }
    roomba_startup();
}

void roomba_dock(void) {
    roomba_startup();
    roomba_send_command(DOCK);
}

void roomba_clean(void) {
    roomba_startup();
    roomba_send_command(CLEAN);
}

void roomba_spot_clean(void){
	roomba_startup();
	roomba_send_command(SPOT);
}

void roomba_sleep(void) {
	roomba_startup();
	roomba_send_command(POWER);
}

#if 0
void roomba_motors(char * data){
	roomba_startup();
	roomba_send_command(MOTORS);
	roomba_send_command(data);
}

void roomba_go_forward(void) {
    roomba_drive(speed, 0x8000);
}

void roomba_go_backward(void) {
    roomba_drive(-speed, 0x8000);
}

void roomba_spin_right(void) {
    roomba_drive(speed, 0xffff);
}

void roomba_spin_left(void) {
    roomba_drive(speed, 1);
}

void roomba_stop(void) {
    roomba_drive(0, 0);
}

void roomba_drive(unsigned int velocity, unsigned int radius) {
    roomba_startup();
    uart_tx_one_char(DRIVE);
    uart_tx_one_char(velocity / 256);
    uart_tx_one_char(velocity);
    uart_tx_one_char(radius / 256);
    uart_tx_one_char(radius);
}
#endif

void roomba_program_songs(){
    roomba_startup();

    roomba_send_command(SONG);				//define a song
    roomba_send_command(SONG_GENERAL_LEE);	//at position 0
    roomba_send_command(12);				//song is 12 notes long

    roomba_send_command(64);
    roomba_send_command(8);
    roomba_send_command(62);
    roomba_send_command(8);

    roomba_send_command(60);
    roomba_send_command(32);
    roomba_send_command(60);
    roomba_send_command(32);
    roomba_send_command(60);
    roomba_send_command(16);
    roomba_send_command(61);
    roomba_send_command(16);
    roomba_send_command(62);
    roomba_send_command(16);
    roomba_send_command(63);
    roomba_send_command(16);

    roomba_send_command(64);
    roomba_send_command(32);
    roomba_send_command(64);
    roomba_send_command(32);
    roomba_send_command(64);
    roomba_send_command(32);
    roomba_send_command(62);
    roomba_send_command(32);
}

void roomba_play_dixie_song(){
	roomba_startup();

	roomba_send_command(PLAY);		//play song
	roomba_send_command(SONG_GENERAL_LEE);		//song
}
