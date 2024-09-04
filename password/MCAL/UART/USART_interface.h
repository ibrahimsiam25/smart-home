/*
 * USART_interface.h
 *
 *  Created on: May 3, 2021
 *      Author: INTEL
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidINIT(void);
void USART_voidTRANSMITR(u8 DATA);
u8   USART_u8RECIVER(void);
void USART_VoidSendString(u8 *COPYu8StringPtr);
u8 *USART_PtrRecieveString(void);

#endif /* USART_INTERFACE_H_ */
