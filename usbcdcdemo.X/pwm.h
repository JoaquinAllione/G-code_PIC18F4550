#ifndef XC_PWM_H
#define	XC_PWM_H

#define TMR2_PS_1 0b00
#define TMR2_PS_4 0b01
#define TMR2_PS_16 0b11

/*PR2
     * PR2 = (T_PWM)*48MHz/(4*PS)-1
     * T_PWM = 1/F_PWM
     */
    
/*Duty Cycle
     * Duty = (CCPR1L:CCP1CON<5:4>)*Tosc*PS (maximo 1023 (es de 10 bits))
     * T_PWM = 1/F_PWM
     * Fosc = 16MHz (cristal)
     */

void PWM_Duty(unsigned int duty);
void PWM_Init(void);
void PWM_On(void);
void PWM_Off(void);

#endif	/* XC_PWM_H */

