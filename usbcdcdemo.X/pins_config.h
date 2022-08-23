/* 
 * File:   pins_config.h
 * Author: joaqu
 *
 * Created on 20 de abril de 2022, 00:40
 */

#ifndef PINS_CONFIG_H
#define	PINS_CONFIG_H

#define MS1_PIN TRISDbits.TRISD3 //pin 22
#define MS2_PIN TRISDbits.TRISD4 //pin 27
#define MS3_PIN TRISDbits.TRISD5 //pin 28

#define MS1_STATE LATDbits.LATD3 
#define MS2_STATE LATDbits.LATD4 
#define MS3_STATE LATDbits.LATD5 

#define DIR_X_PIN TRISCbits.TRISC0 //pin 15
#define DIR_Y_PIN TRISCbits.TRISC1 //pin 16
#define DIR_Z_PIN TRISAbits.TRISA0 //pin 2

#define DIR_X_STATE LATCbits.LATC0 
#define DIR_Y_STATE LATCbits.LATC1 
#define DIR_Z_STATE LATAbits.LATA0 

#define ENABLE_X_AXIS_PIN TRISDbits.TRISD0 //pin 19
#define ENABLE_Y_AXIS_PIN TRISDbits.TRISD1 //pin 20
#define ENABLE_Z_AXIS_PIN TRISDbits.TRISD2 //pin 21

#define ENABLE_X_AXIS_STATE LATDbits.LATD0
#define ENABLE_Y_AXIS_STATE LATDbits.LATD1
#define ENABLE_Z_AXIS_STATE LATDbits.LATD2

#define STEP_X_AXIS_PIN TRISEbits.TRISE0 //pin 8
#define STEP_Y_AXIS_PIN TRISEbits.TRISE1 //pin 9
#define STEP_Z_AXIS_PIN TRISEbits.TRISE2 //pin 10 

#define STEP_X_AXIS_STATE LATEbits.LATE0
#define STEP_Y_AXIS_STATE LATEbits.LATE1
#define STEP_Z_AXIS_STATE LATEbits.LATE2

#define LIMIT_X1_PIN TRISDbits.TRISD6 //pin 29
#define LIMIT_X2_PIN TRISBbits.TRISB1 //pin 34
#define LIMIT_Y1_PIN TRISBbits.TRISB2 //pin 35
#define LIMIT_Y2_PIN TRISBbits.TRISB0 //pin 33
#define LIMIT_Z1_PIN TRISBbits.TRISB4 //pin 37
#define LIMIT_Z2_PIN TRISBbits.TRISB5 //pin 38

#define LIMIT_X1_STATE PORTDbits.RD6
#define LIMIT_X2_STATE PORTBbits.RB1
#define LIMIT_Y1_STATE PORTBbits.RB2
#define LIMIT_Y2_STATE PORTBbits.RB0
#define LIMIT_Z1_STATE PORTBbits.RB4
#define LIMIT_Z2_STATE PORTBbits.RB5

#define RELAY_PIN TRISCbits.TRISC2 //pin 17 
#define RELAY_STATE LATCbits.LATC2

void GPIO_Init(void);

#endif	/* PINS_CONFIG_H */

