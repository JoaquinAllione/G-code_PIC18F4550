#include <xc.h>
#include "sysconfig.h"
#include "GPIO.h"
#include "cpu_map_pic18f4550.h"
#include "usb_cdc_lib.h"

void MicroStepConfig_Get(MicroStep_enum MS){//permite imprimir en el puerto serial la informacion referente a la configuracion de micro paso
    switch(MS){
        case Full_Step:
            putUSBUSART("MS config: FULL STEP",sizeof("MS config: FULL STEP"));
            break;
        case Half_Step:
            putUSBUSART("MS config: HALF STEP",sizeof("MS config: HALF STEP"));
            break;
        case Quater_Step:
            putUSBUSART("MS config: QUATER STEP",sizeof("MS config: QUATER STEP"));
            break;
        case Eighth_Step:
            putUSBUSART("MS config: EIGHTH STEP",sizeof("MS config: EIGHTH STEP"));
            break;
        case Sixtheenth_Step:
            putUSBUSART("MS config: SIXTHEENTH STEP",sizeof("MS config: SIXTHEENTH STEP"));
            break;
    }
}

void DirectionConfig_Set(Axes_enum axis, int dir){
    switch(axis){
        case Axis_X:
            if(dir) {
                BIT_SET(X_DIR_STATUS_REG, X_DIR_BIT);
            }else{
                BIT_CLEAR(X_DIR_STATUS_REG, X_DIR_BIT);
            }
            break;
        case Axis_Y:
            if(dir) {
                BIT_SET(Y_DIR_STATUS_REG, Y_DIR_BIT);
            }else{
                BIT_CLEAR(Y_DIR_STATUS_REG, Y_DIR_BIT);
            }
            break;
        case Axis_Z:
            if(dir) {
                BIT_SET(Z_DIR_STATUS_REG, Z_DIR_BIT);
            }else{
                BIT_CLEAR(Z_DIR_STATUS_REG, Z_DIR_BIT);
            }
            break;
        case All_Axes:
            if(dir) {
                BIT_SET(X_DIR_STATUS_REG, X_DIR_BIT);
                BIT_SET(Y_DIR_STATUS_REG, Y_DIR_BIT);
                BIT_SET(Z_DIR_STATUS_REG, Z_DIR_BIT);
            }else{
                BIT_CLEAR(X_DIR_STATUS_REG, X_DIR_BIT);
                BIT_CLEAR(Y_DIR_STATUS_REG, Y_DIR_BIT);
                BIT_CLEAR(Z_DIR_STATUS_REG, Z_DIR_BIT);
            }
            break;
    }
}

MicroStep_enum MicroStepConfig_Set(MicroStep_enum MS){ ////perimite configurar los micro pasos segun el valor pasado como parametro (Ver GPIO.h - MicroStep_enum)
    //retorna el mismo valor que fue enviado como parametro 
    //para hacer uso de ese valor en la funcion MicroStepConfig_Get
    //la cual informa a la PC sobre la configuracion establecida.
    switch(MS){
        case Full_Step:
            BIT_CLEAR(MS1_STATUS_REG, MS1_BIT);
            BIT_CLEAR(MS2_STATUS_REG, MS2_BIT);
            BIT_CLEAR(MS3_STATUS_REG, MS3_BIT);
            break;
        case Half_Step:
            BIT_SET(MS1_STATUS_REG, MS1_BIT);
            BIT_CLEAR(MS2_STATUS_REG, MS2_BIT);
            BIT_CLEAR(MS3_STATUS_REG, MS3_BIT);
            break;
        case Quater_Step:
            BIT_CLEAR(MS1_STATUS_REG, MS1_BIT);
            BIT_SET(MS2_STATUS_REG, MS2_BIT);
            BIT_CLEAR(MS3_STATUS_REG, MS3_BIT);
            break;
        case Eighth_Step:
            BIT_SET(MS1_STATUS_REG, MS1_BIT);
            BIT_SET(MS2_STATUS_REG, MS2_BIT);
            BIT_CLEAR(MS3_STATUS_REG, MS3_BIT);
            break;
        case Sixtheenth_Step:
            BIT_SET(MS1_STATUS_REG, MS1_BIT);
            BIT_SET(MS2_STATUS_REG, MS2_BIT);
            BIT_SET(MS3_STATUS_REG, MS3_BIT);
            break;
    }
    return MS;
}

void GPIO_Init(void){ //inicializa las funcionalidades de los pines de control
    
    // Config DIRECTION pins
    BIT_CLEAR(X_DIR_CONFIG_REG, X_DIR_BIT); //output
    BIT_CLEAR(Y_DIR_CONFIG_REG, Y_DIR_BIT); //output
    BIT_CLEAR(Z_DIR_CONFIG_REG, Z_DIR_BIT); //output
    
    // Config STEP pins
    BIT_CLEAR(X_STEP_CONFIG_REG, X_STEP_BIT); //output
    BIT_CLEAR(Y_STEP_CONFIG_REG, Y_STEP_BIT); //output
    BIT_CLEAR(Z_STEP_CONFIG_REG, Z_STEP_BIT); //output

    BIT_CLEAR(X_STEP_STATUS_REG, X_STEP_BIT); //output
    BIT_CLEAR(Y_STEP_STATUS_REG, Y_STEP_BIT); //output
    BIT_CLEAR(Z_STEP_STATUS_REG, Z_STEP_BIT); //output
    
    // Config ENABLE pins
    BIT_CLEAR(X_ENABLE_CONFIG_REG, X_ENABLE_BIT); //output
    BIT_CLEAR(Y_ENABLE_CONFIG_REG, Y_ENABLE_BIT); //output
    BIT_CLEAR(Z_ENABLE_CONFIG_REG, Z_ENABLE_BIT); //output
    
    // Config MS pins
    BIT_CLEAR(MS1_CONFIG_REG, MS1_BIT); //output
    BIT_CLEAR(MS2_CONFIG_REG, MS2_BIT); //output
    BIT_CLEAR(MS3_CONFIG_REG, MS3_BIT); //output
    
    // Config LIMIT pins
    BIT_SET(X1_LIMIT_CONFIG_REG, X1_LIMIT_BIT); //input
    BIT_SET(X2_LIMIT_CONFIG_REG, X2_LIMIT_BIT); //input
    BIT_SET(Y1_LIMIT_CONFIG_REG, Y1_LIMIT_BIT); //input
    BIT_SET(Y2_LIMIT_CONFIG_REG, Y2_LIMIT_BIT); //input
    BIT_SET(Z1_LIMIT_CONFIG_REG, Z1_LIMIT_BIT); //input
    BIT_SET(Z2_LIMIT_CONFIG_REG, Z2_LIMIT_BIT); //input
    
    // Config RELAY pin
    BIT_CLEAR(RELAY_CONFIG_REG, RELAY_BIT); //output
    
}

void Enable_Axes(Axes_enum axis){ //perimite habilitar el motor pasado como parametro (Ver GPIO.h - Axes_enum)
    switch(axis){
        case Axis_X:
            BIT_CLEAR(X_ENABLE_STATUS_REG, X_ENABLE_BIT);
            break;
        case Axis_Y:
            BIT_CLEAR(Y_ENABLE_STATUS_REG, Y_ENABLE_BIT);
            break;
        case Axis_Z:
            BIT_CLEAR(Z_ENABLE_STATUS_REG, Z_ENABLE_BIT);
            break;
        case All_Axes:
            BIT_CLEAR(X_ENABLE_STATUS_REG, X_ENABLE_BIT);
            BIT_CLEAR(Y_ENABLE_STATUS_REG, Y_ENABLE_BIT);
            BIT_CLEAR(Z_ENABLE_STATUS_REG, Z_ENABLE_BIT);
            break;
    }
}

void Disable_Axes(Axes_enum axis){ //perimite deshabilitar el motor pasado como parametro (Ver GPIO.h - Axes_enum)
    switch(axis){
        case Axis_X:
            BIT_SET(X_ENABLE_STATUS_REG, X_ENABLE_BIT);
            break;
        case Axis_Y:
            BIT_SET(Y_ENABLE_STATUS_REG, Y_ENABLE_BIT);
            break;
        case Axis_Z:
            BIT_SET(Z_ENABLE_STATUS_REG, Z_ENABLE_BIT);
            break;
        case All_Axes:
            BIT_SET(X_ENABLE_STATUS_REG, X_ENABLE_BIT);
            BIT_SET(Y_ENABLE_STATUS_REG, Y_ENABLE_BIT);
            BIT_SET(Z_ENABLE_STATUS_REG, Z_ENABLE_BIT);
            break;
    }
}
