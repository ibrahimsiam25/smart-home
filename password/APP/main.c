#include "main.h"

// Configuration constants
#define MAX_LOGIN_ATTEMPTS 3
#define ID_LENGTH 3
#define PASSWORD_LENGTH 3
#define ID_ARRAY { "111", "222" }
#define PASSWORD_ARRAY { "111", "222" }

u8 selectedRoom = 0;
u8 numberOfLogins = 0;
char id[ID_LENGTH + 1] = "";
char password[PASSWORD_LENGTH + 1] = "";

int main() {
    initializeSystem();
    displayWelcomeMessage();
    showRoomSelection();
    return 0;
}



void myAPP(){
	if (numberOfLogins >= MAX_LOGIN_ATTEMPTS) {
	    while(1){
	    	 displayMaxLoginAttemptsReached();
	    }
	} else{
         displayWelcomeMessage();
         getUserInput(id, ID_LENGTH, "Enter ID", 0);
         getUserInput(password, PASSWORD_LENGTH, "Enter Password", 1);
         checkCredentials(id, password);}
}

void initializeSystem(void) {
    LCD_8_bit_init();
    Keypad_enu_Init();
    USART_voidINIT();
    // Initialize other peripherals

   // DIO_init(PORT_A, PIN1, OUT);
     ADC_voidInit();
}

void getUserInput(char *buffer, u8 maxLength, const char *promptMessage, u8 maskInput) {
    u8 key;
    u8 counter = 0;

    LCD_8_bit_sendString(promptMessage);
    _delay_ms(100);

    while (counter < maxLength) {
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            LCD_8_bit_GoToPos(1, counter);
            LCD_8_bit_sendChar(maskInput ? '*' : key);
            buffer[counter] = key;
            counter++;
        }
    }

    buffer[counter] = '\0';
    _delay_ms(50);
    LCD_CLR();
}

void checkCredentials(const char *id, const char *password) {
    LCD_CLR();

    const char *idArray[] = ID_ARRAY;
    const char *passwordArray[] = PASSWORD_ARRAY;

    u8 loginSuccess = 0;


        	    for (uint8_t i = 0; i < sizeof(idArray)/sizeof(idArray[0]); i++) {
        	        if (strcmp(id, idArray[i]) == 0 && strcmp(password, passwordArray[i]) == 0) {
        	            // Credentials matched
        	            displayLoginSuccessful(i + 1); // Display the user index (i + 1)
        	            showOptions();
        	            loginSuccess = 1;
        	            break;
        	        }
        	    }

        	    if (!loginSuccess) {
        	        numberOfLogins++;
        	        LCD_8_bit_sendString("Login Failed");
        	        _delay_ms(100);
        	        LCD_CLR();
        	        myAPP();

        	    }


    LCD_CLR();
}

void displayLoginSuccessful(u8 userIndex) {
    LCD_8_bit_sendString("Login Successful");
    LCD_8_bit_GoToPos(1, 0);
    char message[16];
    snprintf(message, sizeof(message), "Hello User %d", userIndex);
    LCD_8_bit_sendString(message);
    _delay_ms(100);
}

void displayMaxLoginAttemptsReached() {
    LCD_8_bit_sendString("Max Login");
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("Attempts Reached");
    _delay_ms(100);
}


//******************************************************//


void displayWelcomeMessage() {
    USART_VoidSendString((u8*)"Welcome\r\n");
    _delay_ms(500);
}

void showRoomSelection() {
    USART_VoidSendString((u8*)"Select a room:\r\n");
    USART_VoidSendString((u8*)"1: Room 1\r\n");
    USART_VoidSendString((u8*)"2: Room 2\r\n");

    while (selectedRoom == 0) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    selectedRoom = 1;
                    LCD_CLR();
                    LCD_8_bit_sendString("Room 1");
                    USART_VoidSendString((u8*)"Room 1 Selected\r\n");
                    showOptions();
                    break;
                case '2':
                    selectedRoom = 2;
                    LCD_CLR();
                    LCD_8_bit_sendString("Room 2");
                    USART_VoidSendString((u8*)"Room 2 Selected\r\n");
                    showOptions();
                    break;
                default:
                    USART_VoidSendString((u8*)"Invalid selection, try again\r\n");
                    break;
            }
        }
    }
}

void showOptions() {
    USART_VoidSendString((u8*)"1:Temp, 2:Motors,");
    USART_VoidSendString((u8*)" 3:LEDs, 4:Logout,");
    USART_VoidSendString((u8*)" 5:CLR");

    u8 isLoggedOut = 0;

    while (!isLoggedOut) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    controlTemp();
                    break;
                case '2':
                    controlMotor();
                    break;
                case '3':
                    controlLED();
                    break;
                case '4':
                    myAPP();
                    break;
                case 'C':
                    LCD_CLR();
                    showOptions();
                    break;
                default:
                    break;
            }
        }
    }
}

void controlMotor() {
    USART_VoidSendString((u8*)"1:Motor ON, 2:Motor OFF\n");

    u8 motorControl = 1;

    while (motorControl) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            if (key == 'C') {
                motorControl = 0;
                showOptions();
            } else {
                switch (key) {
                    case '1':
                        if (selectedRoom == 1) {
                            DIO_write(PORT_A, PIN1, HIGH);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("Motor 1 ON");
                        } else if (selectedRoom == 2) {
                            DIO_write(PORT_A, PIN0, HIGH);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("Motor 2 ON");
                        }
                        USART_VoidSendString((u8*)"Motor ON\n");
                        break;
                    case '2':
                        if (selectedRoom == 1) {
                            DIO_write(PORT_A, PIN1, LOW);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("Motor 1 OFF");
                        } else if (selectedRoom == 2) {
                            DIO_write(PORT_A, PIN0, LOW);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("Motor 2 OFF");
                        }
                        USART_VoidSendString((u8*)"Motor OFF\n");
                        motorControl = 0;
                        showOptions();
                        break;
                    default:
                        USART_VoidSendString((u8*)"Invalid selection, try again\n");
                        break;
                }
            }
        }
    }
}

void controlLED() {
    USART_VoidSendString((u8*)"1:LED ON, 2:LED OFF\n");

    u8 ledControl = 1;

    while (ledControl) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            if (key == 'C') {
                ledControl = 0;
                showOptions();
            } else {
                switch (key) {
                    case '1':
                        if (selectedRoom == 1) {
                            DIO_write(PORT_A, PIN5, HIGH);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("LED 1 ON");
                        } else if (selectedRoom == 2) {
                            DIO_write(PORT_A, PIN0, HIGH);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("LED 2 ON");
                        }
                        USART_VoidSendString((u8*)"LED ON\n");
                        break;

                    case '2':
                        if (selectedRoom == 1) {
                            DIO_write(PORT_A, PIN5, LOW);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("LED 1 OFF");
                        } else if (selectedRoom == 2) {
                            DIO_write(PORT_A, PIN0, LOW);
                            LCD_8_bit_GoToPos(1, 0);
                            LCD_8_bit_sendString("LED 2 OFF");
                        }
                        USART_VoidSendString((u8*)"LED OFF\n");
                        ledControl = 0;
                        showOptions();
                        break;
                    default:
                        USART_VoidSendString((u8*)"Invalid selection, try again\n");
                        break;
                }
            }
        }
    }
}
//***********************************************************************??
void controlTemp() {
    LCD_CLR();
    LCD_8_bit_sendString("Temperature sensor on");

    DIO_write(PORT_A, PIN0, HIGH); // Assume sensor activation or an indicator LED is on PIN0
    DIO_write(PORT_A, PIN3, HIGH); // Assume another device is on PIN3

    u8 tempControl = 1;

    while (tempControl) {
        u8 key;
        u16 adcValue =  ADC_u16GetChannalResult(2);
        float temperature = (adcValue / 1024.0) * 500.0; // Convert ADC reading to temperature in Celsius (assuming LM35)

        if (temperature > 30.0) {
            DIO_write(PORT_A, PIN0, HIGH); // Assume the buzzer is connected to PORT_B and PIN0
            DIO_write(PORT_A, PIN3, HIGH); // Assume the lamp is connected to PORT_C and PIN3
            LCD_8_bit_GoToPos(1, 0);
            LCD_8_bit_sendString("High Temp Alert!"); // Display high temperature alert
        } else {
            DIO_write(PORT_A, PIN0, LOW); // Turn off buzzer
            DIO_write(PORT_A, PIN3, LOW); // Turn off lamp
        }

        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            if (key == 'C') {
                DIO_write(PORT_A, PIN0, LOW);
                DIO_write(PORT_A, PIN3, LOW);
                tempControl = 0;
                showOptions(); // Return to main options menu
            }
        }

        _delay_ms(30000); // Delay to allow time between readings
    }
}


