/* 
 * File:   timer0.c
 * Author: joaqu
 *
 * Created on 9 de noviembre de 2021, 23:55
 */

#include <xc.h>
#include "sysconfig.h"
#include "timer0.h"

void Timer0_Init(void){
    
    RCONbits.IPEN = 0; //Disable priority levels on interrupts
    
    INTCONbits.GIE = 0; //Disables all interrupts 
    INTCONbits.PEIE = 1; //Enables all unmasked peripheral interrupts
    INTCONbits.TMR0IE = 1; //Enables the TMR0 overflow interrupt
    INTCONbits.TMR0IF = 0; //Clear TIMER0 Flag interrupt
    
    T0CONbits.TMR0ON = 0; //Stop Timer0
    T0CONbits.T08BIT = 1; //Timer0 is configured as a 8-bit timer/counter
    T0CONbits.T0CS = 0; //Internal instruction cycle clock (CLKO)
    T0CONbits.PSA = 0; //Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
    T0CONbits.T0PS = TMR1_PS_DIV_BY_256; //Prescale value 
    
    /* EQ
          4*Prescaler*(255-TMR0L)
     T = -------------------------
                  Fosc
  
     * 
                      T*Fosc           1mS * 48MHz
     TMR0L = 255 - -------------- = ----------------- = 208.125
                    4*Prescaler           4*256
    */
    
    TMR0L = 208; //T = 1mS
    
    /* T0PS2:T0PS0: Timer0 Prescaler Select bits 
        111 = 1:256 Prescale value
        110 = 1:128 Prescale value
        101 = 1:64 Prescale value
        100 = 1:32 Prescale value
        011 = 1:16 Prescale value
        010 = 1:8 Prescale value
        001 = 1:4 Prescale value
        000 = 1:2 Prescale value
     */
    
    T0CONbits.TMR0ON = 1; //Enables Timer0
    INTCONbits.GIE = 1; //Enables all interrupts
    
}

