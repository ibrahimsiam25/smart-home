#include "../main.h"
void showRoomSelection() {
    USART_VoidSendString((u8*)"Select a room:\r\n");
    USART_VoidSendString((u8*)"1: Room one, ");
    USART_VoidSendString((u8*)"2: Room two\r\n");

    while (1) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    showOptions(1); // Room 1 selected
                    break;
                case '2':
                    showOptions(2); // Room 2 selected
                    break;
                default:
                    USART_VoidSendString((u8*)"Invalid selection, try again\r\n");
                    break;
            }
        }
    }
}

void showOptions(u8 selectedRoom) {
    displayRoomSelection(selectedRoom); // Display room on LCD and USART

    USART_VoidSendString((u8*)"1:Temp, 2:Motors,");
    USART_VoidSendString((u8*)" 3:LEDs, 4:back,");
    u8 isClicked =0;
    u8 isLoggedOut = 0;

    while (!isLoggedOut) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case 'C':
                    LCD_CLR();
                    showOptions(selectedRoom); // Clear and show options again
                    break;
                case '1':
                    controlTemp();
                    break;
                case '2':
                    controlMotor(selectedRoom);
                    break;
                case '3':
                    controlLED(selectedRoom);
                    break;
                case '4':
                	showRoomSelection();
                    isLoggedOut = 1;
                    break;

                default:
                    USART_VoidSendString((u8*)"Invalid selection, try again\r\n");
                    break;
            }
        }
    }
}

// Helper function to display room selection
void displayRoomSelection(u8 selectedRoom) {
    // Clear the LCD display
    LCD_CLR();

    // Convert the room number to a string
    char str[10];
    convertNumberToString(selectedRoom, str);

    // Display the room selection on the LCD
    LCD_8_bit_sendString("Room ");
    LCD_8_bit_sendString(str);

    // Send the room selection via USART
    USART_VoidSendString((u8*)"Room ");
    USART_VoidSendString((u8*)str);
    USART_VoidSendString((u8*)" Selected\r\n");
}

// Helper function to convert a number to a string
void convertNumberToString(u8 number, char* buffer) {
    sprintf(buffer, "%d", number);
}
