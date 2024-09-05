#include "../main.h"

void controlTemp() {


    DIO_write(PORT_A, PIN0, HIGH); // Assume sensor activation or an indicator LED is on PIN0
    DIO_write(PORT_A, PIN3, HIGH); // Assume another device is on PIN3

    u8 tempControl = 0;
    u16 analog_value;
	char buffer[10];

    while (!tempControl) {
   	 analog_value = ADC_u16GetChannalResult(2);
         itoa(analog_value, buffer, 10);

        LCD_8_bit_GoToPos(1, 0);
        LCD_8_bit_sendString("Temp: ");
    	LCD_8_bit_sendString(buffer);
        LCD_8_bit_sendString(" C");
        _delay_ms(500);
        int temperature = atoi(buffer);
        // Temperature control logic remains the same
        if (temperature > 30.0) {
            DIO_write(PORT_A, PIN0, HIGH); // Turn on buzzer
            DIO_write(PORT_A, PIN3, HIGH); // Turn on lamp
        } else {
            DIO_write(PORT_A, PIN0, LOW); // Turn off buzzer
            DIO_write(PORT_A, PIN3, LOW); // Turn off lamp
        }

        // Delay to allow the display to update
    }
}
