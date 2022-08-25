#include "sysconfig.h"

#include <xc.h>

#include "main.h"
#include "usb_cdc_lib.h"
#include "timer0.h"
#include "math.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "pins_config.h"
#include "commands.h"

void protocol_main_loop(void);
int CommandDetermine(char* line);

typedef enum{
    FULL_STEP = 0,
    HALF_STEP,
    QUATER_STEP,
    EIGHTH_STEP,
    SIXTEENTH_STEP,
}MicroStep_enum;

typedef enum {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z,
}Axis_enum;

typedef enum{
    CLOCKWISE = 0,
    UNCLOCKWISE,
}direction_enum;

typedef enum{
    ENABLED = 0,
    DISABLED,
}state_enum;

typedef struct{
    Axis_enum designator;
    bool limit_1;
    bool limit_2;
}axis;

typedef struct {
    int count;
    state_enum state;
    direction_enum dir;
    float position_current;
    float position_set; 
    axis axis_commanded;
    float steps_per_mm;
}motor;

#define FULL_STEPS_PER_MM 100 //Tornillo de paso 2mm. Motor nema 17 200 pasos por revolucion.

motor motor_1 = (motor){
    .count = 0,
    .position_current = 0.0,
    .position_set = 0.0,
    .dir = CLOCKWISE,
    .state = DISABLED, //default value
    .axis_commanded.designator = AXIS_X,
    .steps_per_mm = FULL_STEPS_PER_MM, //default value
};

void DirectionSet(motor *M, direction_enum dir){
    switch((*M).axis_commanded.designator){ //en todos los ejes se usa el mismo micro paso. Se deja la posibilidad en el codigo de que esto no sea asi.
        case AXIS_X:
            DIR_X_STATE = dir;
            break;
        case AXIS_Y:
            DIR_Y_STATE = dir;
            break;
        case AXIS_Z:
            DIR_Z_STATE = dir;
            break;
    }
    (*M).dir = dir;
}

void MotorStateSet(motor *M, state_enum state){
    switch((*M).axis_commanded.designator){ //en todos los ejes se usa el mismo micro paso. Se deja la posibilidad en el codigo de que esto no sea asi.
        case AXIS_X:
            ENABLE_X_AXIS_STATE = state;
            break;
        case AXIS_Y:
            ENABLE_Y_AXIS_STATE = state;
            break;
        case AXIS_Z:
            ENABLE_Z_AXIS_STATE = state;
            break;
    }
    (*M).state = state;
}

void MicroStepSet(motor *M, MicroStep_enum MS){
    
    MS1_STATE = 0; MS2_STATE = 0; MS3_STATE = 0;
    
    switch(MS){
        case FULL_STEP:
            (*M).steps_per_mm = FULL_STEPS_PER_MM;
            break;
        case HALF_STEP:
            (*M).steps_per_mm = 2*FULL_STEPS_PER_MM;
            MS1_STATE = 1;
            break;
        case QUATER_STEP:
            (*M).steps_per_mm = 4*FULL_STEPS_PER_MM;
            MS2_STATE = 1;
            break;
        case EIGHTH_STEP:
            (*M).steps_per_mm = 8*FULL_STEPS_PER_MM;
            MS1_STATE = 1; MS2_STATE = 1;
            break;
        case SIXTEENTH_STEP:
            (*M).steps_per_mm = 16*FULL_STEPS_PER_MM;
            MS1_STATE = 1; MS2_STATE = 1; MS3_STATE = 1;
            break;
    }
    
}


void Motors_Init(void){ //Initial config.
    
    // -----------------MOTOR 1 - AXIS X-------------------
    DirectionSet(&motor_1, UNCLOCKWISE);
    MicroStepSet(&motor_1, FULL_STEP); //initial value MS
    MotorStateSet(&motor_1, DISABLED);

}

void PrintMotorDirConfig(motor *M){
    
    if ((*M).dir == CLOCKWISE){
        putUSBUSART(PSTR("Direction: CLOCKWISE\n"),sizeof("Direction: CLOCKWISE\n"));
    }else{
        putUSBUSART(PSTR("Direction: UNCLOCKWISE\n"),sizeof("Direction: UNCLOCKWISE\n"));
    }
    
    
    
}

void main(void) 
{
    GPIO_Init();
    Motors_Init();
    
    initUSBLib();
    
    while(1)
    {
        if(isUSBReady())
        {
            protocol_main_loop();
        }
    }
    
    return;
}

void __interrupt() mainISR (void)
{
    if (INTCONbits.T0IF == 1){
        
        INTCONbits.T0IF=0; //Clear TIMER0 Flag interrupt
        
        motor_1.axis_commanded.limit_1 = LIMIT_X1_STATE;
        motor_1.axis_commanded.limit_2 = LIMIT_X2_STATE;
        
    }
    processUSBTasks();
}


int CommandDetermine(char* line){

    char* token = strtok(line, " "); //fracciona el comando usando como separador el caracter " " (espacio)
    char* endPtr;
    char letter;
    int interger;
    bool invalid_command = false;
    int command = NONE_COMMAND;
    while((token != NULL)&&(!invalid_command)) {
        
        letter = token[0]; //leer la primera letra del fragmento de comando 
        token[0] = '0'; //"borra" la letra para recuperar solo el numero flotante
        
        switch(letter){
            
            case 'G': // ------------------------------------------ G commands
                
                interger = trunc(strtof(token, &endPtr));
                switch(interger) {
                    case 0: // ------------------------------------ G0 commands
                        
                        command = G0_COMMAND;
                        putUSBUSART(PSTR("G0-command arrive!\n"),sizeof("G0-command arrive!\n"));
                       
                        break;
                    case 1: // ------------------------------------ G1 commands
                        
                        command = G1_COMMAND;
                        putUSBUSART(PSTR("G1-command arrive!\n"),sizeof("G1-command arrive!\n"));
                     
                        break;
                    case 4: // ------------------------------------ G4 commands
                        
                        command = G4_COMMAND;
                        putUSBUSART(PSTR("G4-command arrive!\n"),sizeof("G4-command arrive!\n"));
                        
                        break;
                    case 21: // ----------------------------------- G21 commands
                        
                        command = G21_COMMAND;
                        putUSBUSART(PSTR("G21-command arrive!\n"),sizeof("G21-command arrive!\n"));
                        
                        break;
                    case 28: // ----------------------------------- G28 commands
                        
                        command = G28_COMMAND;
                        putUSBUSART(PSTR("G28-command arrive!\n"),sizeof("G28-command arrive!\n"));
                        
                        break;
                    case 90: // ----------------------------------- G90 commands
                        
                        command = G90_COMMAND;
                        putUSBUSART(PSTR("G90-command arrive!\n"),sizeof("G90-command arrive!\n"));
                        
                        break;
                    case 91: // ----------------------------------- G91 commands
                        
                        command = G91_COMMAND;
                        putUSBUSART(PSTR("G91-command arrive!\n"),sizeof("G91-command arrive!\n"));
                        
                        break;
                    case 92: // ----------------------------------- G92 commands
                        
                        command = G92_COMMAND;
                        putUSBUSART(PSTR("G92-command arrive!\n"),sizeof("G92-command arrive!\n"));
                        
                        break;
                    default:
                        putUSBUSART(PSTR("Unsupported Command.\n"),sizeof("Unsupported Command.\n"));
                        invalid_command = true;
                        command = NONE_COMMAND;
                        break;

                }

                break;
            
            case 'M': // ------------------------------------------ M commands
                
                interger = trunc(strtof(token, &endPtr));
                switch(interger) {
                    case 0: // ------------------------------------ M0 commands
                        
                        command = M0_COMMAND;
                        putUSBUSART(PSTR("M0-command arrive!\n"),sizeof("M0-command arrive!\n"));
                        
                        break;
                    case 1: // ------------------------------------ M1 commands
                        
                        command = M1_COMMAND;
                        putUSBUSART(PSTR("M1-command arrive!\n"),sizeof("M1-command arrive!\n"));
                       
                        break;
                    case 2: // ------------------------------------ M2 commands
                        
                        command = M2_COMMAND;
                        putUSBUSART(PSTR("M2-command arrive!\n"),sizeof("M2-command arrive!\n"));
                        
                        break;
                    case 84: // ----------------------------------- M84 commands
                        
                        command = M84_COMMAND;
                        putUSBUSART(PSTR("M84-command arrive!\n"),sizeof("M84-command arrive!\n"));
                        
                        break;
                    default:
                        putUSBUSART(PSTR("Unsupported Command.\n"),sizeof("Unsupported Command.\n"));
                        invalid_command = true;
                        command = NONE_COMMAND;
                        break;
                }
                
                break;
            
            case 'X':
                
                
      
                break;
            
            case 'Y':
                
                command = CUSTOM_COMMAND_1;
                
                break;
            
            case 'Z':
                
                PrintMotorDirConfig(&motor_1);
                
                break;
            
            case 'F':
                
                break;
                
            default:
                invalid_command = true;
                putUSBUSART(PSTR("Unsupported Command.\n"),sizeof("Unsupported Command.\n"));
                command = NONE_COMMAND;
                break;
        }

        token = strtok(NULL, " ");

    }
    
    return command;
    //End of command frame analysis!!

}

void G_CommandExecute(int command){
    
    switch(command){
        case G0_COMMAND:
            
            break;
        case G1_COMMAND:
            
            break;
        case G4_COMMAND:
            
            break;
        case G21_COMMAND:
            
            break;
        case G28_COMMAND:
            
            break;
        case G90_COMMAND:
            
            break;
        case G91_COMMAND:
            
            break;
        case G92_COMMAND:
            
            break;
        case G94_COMMAND:
            
            break;
    }
    
}

void M_CommandExecute(int command){
    
    switch(command){
        case M0_COMMAND:
            
            break;
        case M1_COMMAND:
            
            break;
        case M2_COMMAND:
            
            break;
        case M84_COMMAND:
            
            //putUSBUSART(PSTR("All motors OFF\n"),sizeof("All motors OFF\n"));
            MotorStateSet(&motor_1, DISABLED);
            
            break;
        case M117_COMMAND:
            
            break;
    }
    
}

void Custom_CommandExecute(int command){
    
    switch(command){
        case CUSTOM_COMMAND_1:
            
            putUSBUSART(PSTR("TOGGLE OUTPUT RELAY\n"),sizeof("TOGGLE OUTPUT RELAY\n"));
            RELAY_STATE = !RELAY_STATE;
            
            break;
        case CUSTOM_COMMAND_2:
            
            break;
    }
    
}

bool MEF_DataArrive(void);
int command;

void protocol_main_loop(void)
{
    if(MEF_DataArrive()){
        command = CommandDetermine(usbReadBuffer);
    }
    
    G_CommandExecute(command);
    M_CommandExecute(command);
    Custom_CommandExecute(command);
    
    CDCTxService();
    /*
     * 
    uint8_t numBytesRead;
    
    for (;;) {
        
        numBytesRead = getsUSBUSART(usbReadBuffer, sizeof(usbReadBuffer));
        
        if(numBytesRead > 0) {
            if ((usbReadBuffer[numBytesRead-1] == '\n') || (usbReadBuffer[numBytesRead-1] == '\r')) {
                gc_execute_command_line(usbReadBuffer);
            }
        }
        
        CDCTxService();
        
    }
     * 
    */
    return;
}

typedef enum{
    EST_MEF_DATA_INIT = 0,
    EST_MEF_DATA_WAIT,
}estMefDataArrive_enum;

uint8_t numBytesRead;
bool dataIn = false;

bool MEF_DataArrive(void){
    
    static estMefDataArrive_enum estMefDataArrive = EST_MEF_DATA_INIT;
    
    switch(estMefDataArrive){
        
        case EST_MEF_DATA_INIT:
            
            dataIn = false;
            numBytesRead = getsUSBUSART(usbReadBuffer, sizeof(usbReadBuffer));
            if(numBytesRead > 0) {
                estMefDataArrive = EST_MEF_DATA_WAIT;
            }
            break;
            
        case EST_MEF_DATA_WAIT:
            
            if ((usbReadBuffer[numBytesRead-1] == '\n') || (usbReadBuffer[numBytesRead-1] == '\r')) {
                estMefDataArrive = EST_MEF_DATA_INIT;
                dataIn = true;
            }
            break;
        
        default:
            estMefDataArrive = EST_MEF_DATA_INIT;
            break;
        
    }
    
}