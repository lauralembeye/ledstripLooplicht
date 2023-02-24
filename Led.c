#include "Led.h"
#include "mcc_generated_files/mcc.h"
#include <xc.h>

static uint8_t blue = 0x1F, green = 0x1F, red = 0x1F;
static uint8_t setpoint;
const int NumberOfLEDs = 60;

void LED_SetSetpoint(uint8_t value)
{
    setpoint = value;
}
void LED_Setblue(uint8_t value){ 
    
    blue = value;
}
void LED_Setgreen(uint8_t value){
    
    green = value;
}
void LED_Setred(uint8_t value){
    
    red = value;
} 

void LED(void)
{
    Send_LED_StartFrame();
    for (char led = 0; led < NumberOfLEDs; led++) {
        if (led == setpoint) {
            Send_LED_Frame(0x1F, blue, green , red);
        } else {
            Send_LED_Frame(0x00, 0x00, 0x00, 0x00);
        } 
    }
    
    //stop frame
    Send_LED_EndFrame();
}

void Send_LED_Frame(uint8_t intensity, uint8_t blue, uint8_t green, uint8_t red) {
    SPI1_Exchange8bit(0xE0 | intensity);
    SPI1_Exchange8bit(blue);
    SPI1_Exchange8bit(green);
    SPI1_Exchange8bit(red);
}

void Send_LED_StartFrame(void) {
    for (int i = 0; i < 4; i++) {
        SPI1_Exchange8bit(0x00);
    }
}

void Send_LED_EndFrame(void) {
    for (int i = 0; i < 4; i++) {
        SPI1_Exchange8bit(0xFF);
    }
}