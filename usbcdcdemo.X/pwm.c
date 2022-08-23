#include <xc.h>
#include "sysconfig.h"
#include "pwm.h"

void PWM_On(void){
    T2CONbits.TMR2ON = 1;
}

void PWM_Off(void){
    T2CONbits.TMR2ON = 0;
}

void PWM_Duty(unsigned int duty){
    CCPR1L = (duty&(0b1111111100))>>2;
    CCP1CONbits.DC1B = duty & (0b0000000011);
    
}

void PWM_Init(void){

    //Configura frecuencia del PWM a 5kHz
    PR2 = 150;
    
    //Configura el pin RC2 como salida para el PWM1
    TRISCbits.RC2 = 0;
 
    //Configura el funcionamiento como PWM
    CCP1CONbits.CCP1M = 0b1100;
    
    T2CON = 0x00;
    
    //LImpia el registro del TImer2 que guarda la cuenta
    TMR2 = 0;
    
    //Configura la pre-escala de 16
    T2CONbits.T2CKPS = TMR2_PS_16;
    
    //Activa el funcionamiento del TImer2
    T2CONbits.TMR2ON = 1;

}