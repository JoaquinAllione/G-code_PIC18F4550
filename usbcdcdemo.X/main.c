#include "sysconfig.h"

#include <xc.h>

#include "main.h"
#include "usb_cdc_lib.h"
#include "timer0.h"
#include "pwm.h"
#include "cpu_map_pic18f4550.h"
#include "GPIO.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "pins_config.h"
#include "commands.h"

#define TIME_LIMIT_SW 100//mSeg. (tiempo de muestreo para lecturad de los fines de carrera)

void protocol_main_loop(void);

void main(void) 
{
    GPIO_Init();
    
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
    processUSBTasks();
}


void gc_execute_command_line(char* line){

    char* token = strtok(line, " "); //fracciona el comando usando como separador el caracter " " (espacio)
    char* endPtr;
    char letter;
    int interger;
    bool invalid_command = false;

    while((token != NULL)&&(!invalid_command)) {
        
        letter = token[0]; //leer la primera letra del fragmento de comando 
        token[0] = '0'; //"borra" la letra para recuperar solo el numero flotante
        
        switch(letter){
            
            case 'G': // ------------------------------------------ G commands
                
                interger = trunc(strtof(token, &endPtr));
                switch(interger) {
                    case 0: // ------------------------------------ G0 commands
                        
                        putUSBUSART(PSTR("G0-command arrive!\n"),sizeof("G0-command arrive!\n"));
                        
                        break;
                    case 1: // ------------------------------------ G1 commands
                        
                        putUSBUSART(PSTR("G1-command arrive!\n"),sizeof("G1-command arrive!\n"));
                     
                        break;
                    case 4: // ------------------------------------ G4 commands
                        
                        putUSBUSART(PSTR("G4-command arrive!\n"),sizeof("G4-command arrive!\n"));
                        
                        break;
                    case 21: // ----------------------------------- G21 commands
                        
                        putUSBUSART(PSTR("G21-command arrive!\n"),sizeof("G21-command arrive!\n"));
                        
                        break;
                    case 28: // ----------------------------------- G28 commands
                        
                        putUSBUSART(PSTR("G28-command arrive!\n"),sizeof("G28-command arrive!\n"));
                        
                        break;
                    case 90: // ----------------------------------- G90 commands
                        
                        putUSBUSART(PSTR("G90-command arrive!\n"),sizeof("G90-command arrive!\n"));
                        
                        break;
                    case 91: // ----------------------------------- G91 commands
                        
                        putUSBUSART(PSTR("G91-command arrive!\n"),sizeof("G91-command arrive!\n"));
                        
                        break;
                    case 92: // ----------------------------------- G92 commands
                        
                        putUSBUSART(PSTR("G92-command arrive!\n"),sizeof("G92-command arrive!\n"));
                        
                        break;
                    default:
                        putUSBUSART(PSTR("Unsupported Command.\n"),sizeof("Unsupported Command.\n"));
                        invalid_command = true;
                        break;

                }

                break;
            
            case 'M': // ------------------------------------------ M commands
                
                interger = trunc(strtof(token, &endPtr));
                switch(interger) {
                    case 0: // ------------------------------------ M0 commands
                        
                        putUSBUSART(PSTR("M0-command arrive!\n"),sizeof("M0-command arrive!\n"));
                        
                        break;
                    case 1: // ------------------------------------ M1 commands
                        
                        putUSBUSART(PSTR("M1-command arrive!\n"),sizeof("M1-command arrive!\n"));
                       
                        break;
                    case 2: // ------------------------------------ M2 commands
                        
                        putUSBUSART(PSTR("M2-command arrive!\n"),sizeof("M2-command arrive!\n"));
                        
                        break;
                    case 84: // ----------------------------------- M84 commands
                        
                        putUSBUSART(PSTR("M84-command arrive!\n"),sizeof("M84-command arrive!\n"));
                        
                        break;
                    default:
                        putUSBUSART(PSTR("Unsupported Command.\n"),sizeof("Unsupported Command.\n"));
                        invalid_command = true;
                        break;
                }
                
                break;
            
            case 'X':
                
      
                break;
            
            case 'Y':
                
                
                break;
            
            case 'Z':

                
                break;
            
            case 'F':
                
                break;
                
            default:
                invalid_command = true;
                putUSBUSART(PSTR("Error\n"),sizeof("Error\n"));
                break;
        }

        token = strtok(NULL, " ");

    }

    //printf("End of command analysis!!");

}

void protocol_main_loop(void)
{
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
    return;
}