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

      button( selectedRoom);
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
void button(u8 selectedRoom){
	DIO_write(PORT_A, PIN4, HIGH);
	DIO_write(PORT_D, PIN6, HIGH);
	   if (selectedRoom == 1) {
		u8 buttonValue=   DIO_read(PORT_A, PIN4);
		   if(buttonValue){
			   DIO_write(PORT_A, PIN3, LOW);
		   }else{
			   DIO_write(PORT_A, PIN3, HIGH);
		   }
	        }else if(selectedRoom == 2) {
	    		u8 buttonValue=   DIO_read(PORT_D, PIN6);
	    		   if(buttonValue){
	    			   DIO_write(PORT_D, PIN5, LOW);
	    		   }else{
	    			   DIO_write(PORT_D, PIN5, HIGH);
	    		   }
	    	        }
}

void controlHeater(u8 selectedRoom, int temperature) {
    if (temperature > 30) {

        if (selectedRoom == 1) {
            DIO_write(PORT_A, PIN3, HIGH);
        } else if (selectedRoom == 2) {
            DIO_write(PORT_D, PIN5, HIGH);
        }
    } else {

        if (selectedRoom == 1) {

            DIO_write(PORT_A, PIN3, LOW);
        } else if (selectedRoom == 2) {

            DIO_write(PORT_D, PIN5, LOW);
        }
    }
}
