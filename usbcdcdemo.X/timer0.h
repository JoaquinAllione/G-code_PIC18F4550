#ifndef TIMER0_H
#define	TIMER0_H

#define TMR1_PS_DIV_BY_2 0b000
#define TMR1_PS_DIV_BY_4 0b001
#define TMR1_PS_DIV_BY_8 0b010
#define TMR1_PS_DIV_BY_16 0b011
#define TMR1_PS_DIV_BY_32 0b100
#define TMR1_PS_DIV_BY_64 0b101
#define TMR1_PS_DIV_BY_128 0b110
#define TMR1_PS_DIV_BY_256 0b111

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

void Timer0_Init(void);

#endif	/* TIMER0_H */

