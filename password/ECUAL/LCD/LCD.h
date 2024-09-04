/*
 * LCD.h
 *
 *  Created on: Mar 7, 2023
 *      Author: Mahmoud
 */

#ifndef ECUAL_LCD_LCD_H_
#define ECUAL_LCD_LCD_H_

// Driver Inclusions

#include "../../MCAL/DIO/DIO.h"
#include "../../Library/STD.h"
#include <util/delay.h>


// Driver Macros

#define LCD_CMD_PORT_DIR	DDRD
#define LCD_CMD_PORT		PORTD

#define LCD_DATA_PORT_DIR	DDRB
#define LCD_DATA_PORT		PORTB

#define RS		2
#define RW		3
#define EN		4



// Driver Functions Prototypes

void LCD_8_bit_init (void);
void LCD_8_bit_sendCMD (u8 cmnd);
void LCD_8_bit_sendChar (u8 charData);
void LCD_8_bit_sendString (u8 *str);
void LCD_createCustomCharacter (u8 *pattern, u8 location);
void LCD_CLR (void);


#endif /* ECUAL_LCD_LCD_H_ */
