#include "main.h"

// Configuration constants
#define MAX_LOGIN_ATTEMPTS 3
#define ID_LENGTH 3
#define PASSWORD_LENGTH 3


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

	     USART_VoidSendString((u8*)"Max Login Attempts Reached");

	} else{
	     USART_VoidSendString((u8*)"Welcome\r\n");
	     _delay_ms(500);
         getUserInput(id, ID_LENGTH, "Enter ID", 0);
         getUserInput(password, PASSWORD_LENGTH, "Enter Password", 1);
         checkCredentials(id, password,&numberOfLogins);

	}
}

void initializeSystem(void) {
    LCD_8_bit_init();
    Keypad_enu_Init();
    USART_voidINIT();
    ADC_voidInit();
    // Initialize other peripherals
   DIO_init(PORT_A, PIN0, OUT);
   DIO_init(PORT_A, PIN1, OUT);
   DIO_init(PORT_A, PIN3, OUT);
   DIO_init(PORT_A, PIN4, IN);
   DIO_init(PORT_A, PIN5, OUT);
   DIO_init(PORT_A, PIN6, OUT);
   DIO_init(PORT_D, PIN5, OUT);
   DIO_init(PORT_D, PIN6, IN);
}


















