#include "../main.h"

void controlMotor(u8 selectedRoom) {
    USART_VoidSendString((u8*)"1:Motor ON\r\n2:Motor OFF\r\n");
    u8 motorPin;
    u8 isClicked =0;
    u8 motorControl = 1;
    // Determine the motor pin based on the selected room
    switch (selectedRoom) {
        case 1:
            motorPin = PIN1; // Motor for room 1
            break;
        case 2:
            motorPin = PIN6; // Motor for room 2
            break;
        default:
            USART_VoidSendString((u8*)"Invalid room number\n");
            return; // Exit if room number is invalid
    }

    while (motorControl) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case 'C':
                	if(isClicked!=0)
                	DIO_toggle (PORT_A, motorPin);
                    showOptions(selectedRoom);
                    motorControl=0;
                    break;
                case '1': // Motor ON
                	isClicked++;
                    DIO_write(PORT_A, motorPin, HIGH);
                    displayMotorStatus(selectedRoom, "ON");
                    USART_VoidSendString((u8*)"Motor ON\n");
                    break;
                case '2': // Motor OFF
                	isClicked++;
                    DIO_write(PORT_A, motorPin, LOW);
                    displayMotorStatus(selectedRoom, "OFF");
                    USART_VoidSendString((u8*)"Motor OFF\n");
                    break;
                default:
                    USART_VoidSendString((u8*)"Invalid selection, try again\n");
                    break;
            }
        }
    }
}

// Helper function to display motor status on LCD
void displayMotorStatus(u8 room, const char* status) {
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("Motor ");
    LCD_8_bit_sendString(status); // Display the status (ON/OFF)
}
