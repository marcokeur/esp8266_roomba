/* 
 * File:   roomba.h
 * Author: admin
 *
 * Created on 13 November 2014, 07:47
 */

#ifndef ROOMBA_OPCODES_H
#define	ROOMBA_OPCODES_H

	// Roomba ROI opcodes
    #define START               128  // 0
    #define BAUD                129  // 1
    #define CONTROL             130  // 0
    #define SAFE                131  // 0
    #define FULL                132  // 0
    #define POWER               133  // 0
    #define SPOT                134  // 0
    #define CLEAN               135  // 0
    #define MAX                 136  // 0
    #define DRIVE               137  // 4
    #define MOTORS              138  // 1
    #define LEDS                139  // 3
    #define SONG                140  // 2N+2
    #define PLAY                141  // 1
    #define SENSORS             142  // 1
    #define DOCK                143  // 0
    #define PWMMOTORS           144 // 3
    #define DRIVEWHEELS         145 	// 4
    #define DRIVEPWM            146  // 4
    #define STREAM              148  // N+1
    #define QUERYLIST           149 // N+1
    #define STOPSTARTSTREAM     150  // 1
    #define SCRIPT              152
    #define PLAYSCRIPT          153
    #define SCHEDULINGLEDS      162 	// 2
    #define DIGITLEDSRAW        163 	// 4
    #define DIGITLEDSASCII      164	// 4
    #define BUTTONSCMD          165 // 1
    #define SCHEDULE            167  // n
    #define SETDAYTIME          168 // 3

    // own opcodes
	/*
    #define WAKEUP              200 // DD Signal auf low
    #define goDistanceForward   201 // 2  distance in cm 16 Bit
    #define goDistanceBackward  202 // 2  distance in cm 16 Bit
    #define turnRight           203 // 2  degrees  16Bit
    #define turnLeft            204 // 2  degrees 16Bit
    #define mySTOP              205
    #define myDOCK              206
    #define myCLEAN             207
    #define myReset             210
    #define mySong              211
	*/
	#define SONG_GENERAL_LEE	0	//sound the general lee horn!

    // Sensors
    #define SENSORS_ALL          0
    #define SENSORS_PHYSICAL     1
    #define SENSORS_INTERNAL     2
    #define SENSORS_POWER        3

    // speed
    #define default_speed  200


	// offsets into sensor_bytes data
    #define SENSORS_ALL_BUMPSWHEELDROPS      0
    #define SENSORS_ALL_WALL                 1
    #define SENSORS_ALL_CLIFFLEFT            2
    #define SENSORS_ALL_CLIFFFRONTLEFT       3
    #define SENSORS_ALL_CLIFFFRONTRIGHT      4
    #define SENSORS_ALL_CLIFFRIGHT           5
    #define SENSORS_ALL_VIRTUALWALL          6
    #define SENSORS_ALL_MOTOROVERCURRENTS    7
    #define SENSORS_ALL_DIRTLEFT             8
    #define SENSORS_ALL_DIRTRIGHT            9
    #define SENSORS_ALL_REMOTEOPCODE         10
    #define SENSORS_ALL_BUTTONS              11
    #define SENSORS_ALL_DISTANCE_HI          12
    #define SENSORS_ALL_DISTANCE_LO          13  
    #define SENSORS_ALL_ANGLE_HI             14
    #define SENSORS_ALL_ANGLE_LO             15
    #define SENSORS_ALL_CHARGINGSTATE        16
    #define SENSORS_ALL_VOLTAGE_HI           17
    #define SENSORS_ALL_VOLTAGE_LO           18  
    #define SENSORS_ALL_CURRENT_HI           19
    #define SENSORS_ALL_CURRENT_LO           20
    #define SENSORS_ALL_TEMPERATURE          21
    #define SENSORS_ALL_CHARGE_HI            22
    #define SENSORS_ALL_CHARGE_LO            23
    #define SENSORS_ALL_CAPACITY_HI          24
    #define SENSORS_ALL_CAPACITY_LO          25

    #define SENSORS_POWER_CHARGINGSTATE        0
    #define SENSORS_POWER_VOLTAGE_HI           1
    #define SENSORS_POWER_VOLTAGE_LO           2  
    #define SENSORS_POWER_CURRENT_HI           3
    #define SENSORS_POWER_CURRENT_LO           4
    #define SENSORS_POWER_TEMPERATURE          5
    #define SENSORS_POWER_CHARGE_HI            6
    #define SENSORS_POWER_CHARGE_LO            7
    #define SENSORS_POWER_CAPACITY_HI          8
    #define SENSORS_POWER_CAPACITY_LO          9

    // bitmasks for various thingems
    #define WHEELDROP_MASK       0x1C
    #define BUMP_MASK            0x03
    #define BUMPRIGHT_MASK       0x01
    #define BUMPLEFT_MASK        0x02
    #define WHEELDROPRIGHT_MASK  0x04
    #define WHEELDROPLEFT_MASK   0x08
    #define WHEELDROPCENT_MASK   0x10

    #define MOVERDRIVELEFT_MASK  0x10
    #define MOVERDRIVERIGHT_MASK 0x08
    #define MOVERMAINBRUSH_MASK  0x04
    #define MOVERVACUUM_MASK     0x02
    #define MOVERSIDEBRUSH_MASK  0x01

    #define POWERBUTTON_MASK     0x08  
    #define SPOTBUTTON_MASK      0x04  
    #define CLEANBUTTON_MASK     0x02  
    #define MAXBUTTON_MASK       0x01  

#endif	/* ROOMBA_H */

