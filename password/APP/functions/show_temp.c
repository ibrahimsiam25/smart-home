#include "../main.h"

u8 getChannelForRoom(u8 selectedRoom) {
    return (selectedRoom == 1) ? 2 : 7;
}

void controlTemp(u8 selectedRoom,u8 flag) {

    u8 tempControl = 0;
    u16 analog_value;


    while (!tempControl) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            if (key == 'C') {
                LCD_CLR();
                showOptions(selectedRoom);
                tempControl = 1;
            } else {
                USART_VoidSendString((u8*)"Invalid selection, try again\r\n");
            }
        }

        u8 channel = getChannelForRoom(selectedRoom);
        analog_value = ADC_u16GetChannalResult(channel)*0.5;

      if(flag==0){
    	  displayTemperature(analog_value);
      }

       controlHeater(selectedRoom,analog_value );
    }
}


void displayTemperature(u16 analog_value) {
    char buffer[10];
    itoa(analog_value, buffer, 10);
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("Temp: ");
    LCD_8_bit_sendString(buffer);
    LCD_8_bit_sendString(" C");
    _delay_ms(500);
}


void controlHeater(u8 selectedRoom, int temperature) {
	DIO_write(PORT_A, PIN4, HIGH);
	DIO_write(PORT_D, PIN5, HIGH);
    u8 buttonValueRoom1 = DIO_read(PORT_A, PIN4);
    u8 buttonValueRoom2 = DIO_read(PORT_D, PIN6);

    // Check for Room 1
    if (selectedRoom == 1 && (!buttonValueRoom1 || temperature > 30)) {
        DIO_write(PORT_A, PIN3, HIGH);  // Turn on heater in Room 1
    } else if (selectedRoom == 1) {
        DIO_write(PORT_A, PIN3, LOW);   // Turn off heater in Room 1
    }

    // Check for Room 2
    if (selectedRoom == 2 && (!buttonValueRoom2 || temperature > 30)) {
        DIO_write(PORT_D, PIN5, HIGH);  // Turn on heater in Room 2
    } else if (selectedRoom == 2) {
        DIO_write(PORT_D, PIN5, LOW);   // Turn off heater in Room 2
    }
}
