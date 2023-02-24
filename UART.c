/**
  Section: Included Files
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include <stdlib.h> //for atoi and atof functions
#include <ctype.h> //for toupper command
#include "Led.h"

/**
  Section: UART Module APIs
 */

static char setpoint;
static char blue;
static char green;
static char red;

static char command;
static int index;
static char data[8]; //"S20" of "p1.25"
static char value[7];
static int printCycle = 0;

void UART(void) {

    //Read from PC
    if (EUSART_DataReady) {
        index = 0;
        __delay_ms(5); // wacht tot alle data ontvangen is
        while (EUSART_DataReady) {
            data[index] = EUSART_Read(); // ontvangen data lezen          
            index++;
        }
        data[index] = '\0'; // \0 toevoegen voor atoi en atof functies
        command = data[0]; // eerste char = command
        command = (char) toupper(command); //converteer naar hoofdletter (voor de zekerheid)
        for (int i = 0; i <8; i++){ //value = data vanaf het 2e karakter
            value[i] = data[i+1];
        }

        switch (command) {
            case 'L':                            
                //setpoint = (uint8_t) atoi(value); //atoi = ASCII to integer
                LED_SetSetpoint(setpoint);
                break;
            case 'b':                           
                //Send_LED_Frame()
                LED_Setblue(blue);
                break;
            case 'g':                                          
                //Send_LED_Frame()
                LED_Setgreen(green);
                break;
            case 'r':                                          
                //Send_LED_Frame()
                LED_Setred(red);
                break;
        };
    }
}

/**
 End of File
 */
