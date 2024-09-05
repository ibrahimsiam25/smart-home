#include "../main.h"

void controlLED(u8 selectedRoom) {
    USART_VoidSendString((u8*)"1:LED ON\r\n2:LED OFF\r\n");

    u8 ledControl = 1;
    u8 ledPin;
    u8 isClicked =0;
    // Determine the LED pin based on the selected room
    switch (selectedRoom) {
        case 1:
            ledPin = PIN0; // LED for room 1
            break;
        case 2:
            ledPin = PIN5; // LED for room 2
            break;
        default:
            USART_VoidSendString((u8*)"Invalid room number\n");
            return; // Exit if room number is invalid
    }

    while (ledControl) {
        u8 key;

        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case 'C':
                	if(isClicked!=0)
                	DIO_toggle (PORT_A, ledPin );
                    showOptions(selectedRoom);
                    break;
                case '1': // LED ON
                	isClicked++;
                    DIO_write(PORT_A, ledPin, HIGH);
                    displayLEDStatus(selectedRoom, "ON");
                    USART_VoidSendString((u8*)"LED ON\n");
                    break;
                case '2': // LED OFF
                	isClicked++;
                    DIO_write(PORT_A, ledPin, LOW);
                    displayLEDStatus(selectedRoom, "OFF");
                    USART_VoidSendString((u8*)"LED OFF\n");
                    ledControl = 0;
                  //  showOptions();
                    break;
                default:
                    USART_VoidSendString((u8*)"Invalid selection, try again\n");
                    break;
            }
        }
    }
}

// Helper function to display LED status on LCD
void displayLEDStatus(u8 room, const char* status) {
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("LED ");
    LCD_8_bit_sendString(room); // Display the selected room number
    LCD_8_bit_sendString(" ");
    LCD_8_bit_sendString(status); // Display the status (ON/OFF)
}




