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


void roomba_startup(void) {
	os_printf("startup");
	uart_tx_one_char(UART0, START);
	uart_tx_one_char(UART0, CONTROL);
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
    uart_tx_one_char(UART0, DOCK);
}

void roomba_clean(void) {
    roomba_startup();
    uart_tx_one_char(UART0, CLEAN);
}

void roomba_sleep(void) {
	roomba_startup();
	uart_tx_one_char(UART0, POWER);
}

void roomba_motors(char * data){
	roomba_startup();
	uart_tx_one_char(UART0, MOTORS);
	uart_tx_one_char(UART0, data);
}

#if 0
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
    uart_tx_one_char(UART0, DRIVE);
    uart_tx_one_char(UART0, velocity / 256);
    uart_tx_one_char(UART0, velocity);
    uart_tx_one_char(UART0, radius / 256);
    uart_tx_one_char(UART0, radius);
}
#endif

void roomba_program_songs(){
    roomba_startup();
	//start csi
    //uart_tx_one_char(UART0, 128);
    //in safe mode
    //uart_tx_one_char(UART0, 131);
    uart_tx_one_char(UART0, SONG);				//define a song
    uart_tx_one_char(UART0, SONG_GENERAL_LEE);	//at position 0
    uart_tx_one_char(UART0, 12);				//song is 12 notes long

    uart_tx_one_char(UART0, 64);
    uart_tx_one_char(UART0, 8);
    uart_tx_one_char(UART0, 62);
    uart_tx_one_char(UART0, 8);

    uart_tx_one_char(UART0, 60);
    uart_tx_one_char(UART0, 32);
    uart_tx_one_char(UART0, 60);
    uart_tx_one_char(UART0, 32);
    uart_tx_one_char(UART0, 60);
    uart_tx_one_char(UART0, 16);
    uart_tx_one_char(UART0, 61);
    uart_tx_one_char(UART0, 16);
    uart_tx_one_char(UART0, 62);
    uart_tx_one_char(UART0, 16);
    uart_tx_one_char(UART0, 63);
    uart_tx_one_char(UART0, 16);

    uart_tx_one_char(UART0, 64);
    uart_tx_one_char(UART0, 32);
    uart_tx_one_char(UART0, 64);
    uart_tx_one_char(UART0, 32);
    uart_tx_one_char(UART0, 64);
    uart_tx_one_char(UART0, 32);
    uart_tx_one_char(UART0, 62);
    uart_tx_one_char(UART0, 32);
}

void roomba_play_song( int song ){
	roomba_startup();

	uart_tx_one_char(UART0, PLAY);		//play song
    uart_tx_one_char(UART0, song);		//song
}
