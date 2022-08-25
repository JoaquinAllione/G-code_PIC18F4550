#include "pins_config.h"
#include "xc.h"

void GPIO_Init(void){
    
    // ******OUTPUT PINS CONFIG******** //
    
    //----------MS-MicroStep-----------
    MS1_PIN = 0;//RD3 output (MS1)
    MS1_STATE = 0; //Initial value 0
    
    MS2_PIN = 0; //RD4 output (MS2)
    MS2_STATE = 0; //Initial value 0
    
    MS3_PIN = 0; //RD5 output (MS3)
    MS3_STATE = 0; //Initial value 0
    //---------------------------------
    
    //-----------ENABLE-Axis-----------
    ENABLE_X_AXIS_PIN = 0; //RD0 output (X-axis)
    ENABLE_X_AXIS_STATE = 0; //Initial value 0
    
    ENABLE_Y_AXIS_PIN = 0; //RD1 output (Y-axis)
    ENABLE_Y_AXIS_STATE = 0; //Initial value 0
    
    ENABLE_Z_AXIS_PIN = 0; //RD2 output (Z-axis)
    ENABLE_Z_AXIS_STATE = 0; //Initial value 0
    //---------------------------------
    
    //------------DIR-Axis-------------
    DIR_X_PIN = 0; //RC0 output (DIR-X-axis)
    DIR_X_STATE = 0; //Initial value 0
    
    DIR_Y_PIN = 0; //RC1 output (DIR-Y-axis)
    DIR_Y_STATE = 0; //Initial value 0
    
    DIR_Z_PIN = 0; //RA0 output (DIR-Z-axis)
    DIR_Z_STATE = 0; //Initial value 0
    //---------------------------------
    
    //------------STEP-Axis------------
    STEP_X_AXIS_PIN = 0; //RE0 output (STEP-X-axis)
    STEP_X_AXIS_STATE = 0; //Initial value 0
    
    STEP_Y_AXIS_PIN = 0; //RE1 output (STEP-Y-axis)
    STEP_Y_AXIS_STATE = 0; //Initial value 0
    
    STEP_Z_AXIS_PIN = 0; //RE2 output (STEP-Z-axis)
    STEP_Z_AXIS_STATE = 0; //Initial value 0
    //---------------------------------
    
    //--------------RELAY--------------
    RELAY_PIN = 0; //RC2 output
    RELAY_STATE = 0;
    //---------------------------------
    
    // *******INPUT PINS CONFIG******** //
    
    //---------LIMIT-SWITCHS-----------
    LIMIT_X1_PIN = 1; //RB4 input (X1)
    LIMIT_X2_PIN = 1; //RB4 input (X2)
    
    LIMIT_Y1_PIN = 1; //RB4 input (Y1)
    LIMIT_Y2_PIN = 1; //RB4 input (Y2)
    
    LIMIT_Z1_PIN = 1; //RB4 input (Z1)
    LIMIT_Z2_PIN = 1; //RB4 input (Z2)
    //---------------------------------   
}
