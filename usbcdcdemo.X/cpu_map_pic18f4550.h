/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CPU_MAP_PIC18f4550_H
#define	CPU_MAP_PIC18f4550_H

#include <xc.h> // include processor files - each processor file is guarded.  

// BIT(x) regresa el bit x puesto a uno y los demas bits en cero, ej. BIT(3) regresa 00001000
#define BIT(x)         (1<<(x))

// BIT_GET(x,b) regresa el bit b-esimo de x ej. BIT_GET(PINC,3)
#define BIT_GET(x,b)   ((x) & BIT(b))

// BIT_SET(x,b) establece en '1' el bit b de x ej. BIT_SET(PORTD,4)
#define BIT_SET(x,b)   ((x) |= BIT(b))

// BIT_CLEAR(x,b) establece en '0' el bit b de x
#define BIT_CLEAR(x,b) ((x) &= ~BIT(b))

// BIT_TOGGLE(x,b) invierte el valor del bit b de x a su complemento,
#define BIT_TOGGLE(x,b)  ((x) ^= BIT(b))

// -----  STEP  -----
#define X_STEP_BIT  0   // Pin8  
#define Y_STEP_BIT  1   // Pin9  
#define Z_STEP_BIT  2   // Pin10  

#define X_STEP_CONFIG_REG       TRISE
#define Y_STEP_CONFIG_REG       TRISE
#define Z_STEP_CONFIG_REG       TRISE

#define X_STEP_STATUS_REG       LATE
#define Y_STEP_STATUS_REG       LATE
#define Z_STEP_STATUS_REG       LATE

// -----  DIRECTION  -----

#define DIR_CLOCK_WISE 1
#define DIR_UNCLOCK_WISE 0

#define X_DIR_BIT 0   // Pin15  
#define Y_DIR_BIT 1   // Pin16 
#define Z_DIR_BIT 0   // Pin2 (PORT A) 

#define X_DIR_CONFIG_REG       TRISC
#define Y_DIR_CONFIG_REG       TRISC
#define Z_DIR_CONFIG_REG       TRISA

#define X_DIR_STATUS_REG       LATC
#define Y_DIR_STATUS_REG       LATC
#define Z_DIR_STATUS_REG       LATA

// -----  ENABLE  -----

#define X_ENABLE_BIT    0   // Pin19  
#define Y_ENABLE_BIT    1   // Pin20  
#define Z_ENABLE_BIT    2   // Pin21   

#define X_ENABLE_CONFIG_REG TRISD
#define Y_ENABLE_CONFIG_REG TRISD
#define Z_ENABLE_CONFIG_REG TRISD

#define X_ENABLE_STATUS_REG     LATD
#define Y_ENABLE_STATUS_REG     LATD
#define Z_ENABLE_STATUS_REG     LATD

// -----  LIMITS  -----

#define X1_LIMIT_BIT    6      // Pin29  (PORT D)
#define Y1_LIMIT_BIT    2      // Pin35  
#define Z1_LIMIT_BIT    4      // Pin37  

#define X2_LIMIT_BIT    1      // Pin34  
#define Y2_LIMIT_BIT    0      // Pin33  
#define Z2_LIMIT_BIT    5      // Pin38  

#define X1_LIMIT_STATUS_REG       PORTD
#define X2_LIMIT_STATUS_REG       PORTB
#define Y1_LIMIT_STATUS_REG       PORTB
#define Y2_LIMIT_STATUS_REG       PORTB
#define Z1_LIMIT_STATUS_REG       PORTB
#define Z2_LIMIT_STATUS_REG       PORTB

#define X1_LIMIT_CONFIG_REG       TRISD
#define X2_LIMIT_CONFIG_REG       TRISB
#define Y1_LIMIT_CONFIG_REG       TRISB
#define Y2_LIMIT_CONFIG_REG       TRISB
#define Z1_LIMIT_CONFIG_REG       TRISB
#define Z2_LIMIT_CONFIG_REG       TRISB

// -----  MICRO STEP  -----

#define MS1_BIT 3   // Pin22 
#define MS2_BIT 4   // Pin27 
#define MS3_BIT 5   // Pin28 

#define MS1_CONFIG_REG TRISD
#define MS2_CONFIG_REG TRISD
#define MS3_CONFIG_REG TRISD

#define MS1_STATUS_REG LATD
#define MS2_STATUS_REG LATD
#define MS3_STATUS_REG LATD

// ---- RELAY -----
#define RELAY_BIT 2   // Pin17 
#define RELAY_CONFIG_REG       TRISC

#endif	/* CPU_MAP_PIC18f4550_H */

