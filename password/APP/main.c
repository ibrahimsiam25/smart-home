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
   DIO_init(PORT_A, PIN0, OUT);
   DIO_init(PORT_A, PIN1, OUT);
   DIO_init(PORT_A, PIN5, OUT);
   DIO_init(PORT_A, PIN6, OUT);
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













