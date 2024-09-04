#include "main.h"

// Configuration constants
#define MAX_LOGIN_ATTEMPTS 3
#define ID_LENGTH 3
#define PASSWORD_LENGTH 3
#define ID_ARRAY { "111", "222" }
#define PASSWORD_ARRAY { "111", "222" }

u8 numberOfLogins = 0;
char id[ID_LENGTH + 1] = "";
    char password[PASSWORD_LENGTH + 1] = "";

int main() {
    initializeSystem();
    myAPP();
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

void displayWelcomeMessage() {
	 LCD_CLR();
    LCD_8_bit_sendString("Welcome");
    _delay_ms(100);
    LCD_CLR();
}

void showOptions() {
    LCD_CLR();
    LCD_8_bit_sendString("1:Temp, ");
    LCD_8_bit_sendString("2:Motors");
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("3:LEDs, ");
    LCD_8_bit_sendString("4:Logout");

    u8 isLoggedOut = 0;

    while (!isLoggedOut) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    showTemp();
                    break;
                case '2':
                    controlWithMotor();
                    break;
                case '3':
                    controlWithLEDs();
                    break;
                case '4':
                	myAPP();
                    break;
                default:
                    break;
            }
        }
    }

    LCD_CLR();
}

void controlWithLEDs() {
    LCD_CLR();
    LCD_8_bit_sendString("1:Green,");
    LCD_8_bit_sendString("2:Red");
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("3:Blue,");
    LCD_8_bit_sendString("4:Back");

    u8 returnToMain = 0;

    while (!returnToMain) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    DIO_toggle(PORT_C, PIN3);
                    break;
                case '2':
                    DIO_toggle(PORT_C, PIN7);
                    break;
                case '3':
                    DIO_toggle(PORT_A, PIN1);
                    break;
                case '4':
                    returnToMain = 1;
                    showOptions();
                    break;
                default:
                    break;
            }
        }
    }
}

void controlWithMotor() {
    LCD_CLR();

    LCD_8_bit_sendString("1:FAN+, ");
    LCD_8_bit_sendString("2:FAN-");
    LCD_8_bit_GoToPos(1, 0);
    LCD_8_bit_sendString("3:Motor,");
    LCD_8_bit_sendString("4:Back");

    u8 returnToMain = 0;

    while (!returnToMain) {
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                    DIO_write(PORT_C, PIN5, HIGH);
                    DIO_write(PORT_C, PIN6, LOW);
                    break;
                case '2':
                    DIO_write(PORT_C, PIN6, HIGH);
                    DIO_write(PORT_C, PIN5, LOW);
                    break;
                case '3':
                    DIO_toggle(PORT_C, PIN4);
                    break;
                case '4':
                    returnToMain = 1;
                    showOptions();
                    break;
                default:
                    break;
            }
        }
    }
}

void showTemp() {
    LCD_CLR();

    u8 returnToMain = 0;
    u16 analog_value;
	char buffer[10];

	LCD_8_bit_GoToPos(1, 0);
	LCD_8_bit_sendString("1:back");

    while (!returnToMain) {
   	 analog_value = ADC_u16GetChannalResult(2);
       itoa(analog_value, buffer, 10);
   	LCD_8_bit_sendString(buffer);
    LCD_CLR();
        u8 key;
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
            switch (key) {
                case '1':
                	showOptions();
                    break;
                default:
                    break;
            }
        }
    }
}
