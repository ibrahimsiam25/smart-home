#include "../main.h"

#define ID_ARRAY { "111", "222" }
#define PASSWORD_ARRAY { "111", "222" }

void getUserInput(char *buffer, u8 maxLength, const char *promptMessage, u8 maskInput) {
    u16 key;
    u8 counter = 0;
    USART_VoidSendString((u8*)promptMessage);
    USART_VoidSendString((u8*)"\r\n");
    while (counter < maxLength) {
        if (Keypad_enu_getKey(&key) == STATE_OK && key != KEYPAD_U8_NO_KEY_PRESSED) {
        	USART_VoidSendString((u8*)(maskInput ? "*" : &key));
            buffer[counter] = key;
            counter++;
        }
    }
    USART_VoidSendString((u8*)"\r\n");

    buffer[counter] = '\0';
    _delay_ms(200);
}

void checkCredentials(const char *id, const char *password, u8 *numberOfLogins) {


    const char *idArray[] = ID_ARRAY;
    const char *passwordArray[] = PASSWORD_ARRAY;

    u8 loginSuccess = 0;


        	    for (uint8_t i = 0; i < sizeof(idArray)/sizeof(idArray[0]); i++) {
        	        if (strcmp(id, idArray[i]) == 0 && strcmp(password, passwordArray[i]) == 0) {
        	            // Credentials matched
        	            displayLoginSuccessful(i + 1); // Display the user index (i + 1)
        	            showRoomSelection();
        	            loginSuccess = 1;
        	            break;
        	        }
        	    }

        	    if (!loginSuccess) {
        	    	 (*numberOfLogins)++;
        	        USART_VoidSendString((u8*) *numberOfLogins);
        	        USART_VoidSendString((u8*)"Login Failed\r\n");
        	        _delay_ms(100);
        	        myAPP();

        	    }

        	    _delay_ms(500);
}

void displayLoginSuccessful(u8 userIndex) {
	 USART_VoidSendString((u8*)"Login Successful\r\n");

    char message[16];
    snprintf(message, sizeof(message), "Hello User %d", userIndex);
    USART_VoidSendString((u8*)message);
    USART_VoidSendString((u8*)"\r\n");
    _delay_ms(500);
}
