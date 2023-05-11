/*
 * uart_private.h
 *
 * Created: 11/5/2023 11:21:08 PM
 *  Author: hossam
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* ****************************************************/
/*            UART  Registers Locations               */
/* ****************************************************/

/* USART I/O DATA REGISTER */
#define UART_UDR_REG   *( ( volatile u8 * ) 0x2C )

/* USART Control and status Register A */
/* 7: RXC   (R)     Reception Complete
 * 6: TXC   (R/W)   Transmission Complete
 * 5: UDRE  (R)     Data register empty (initial 1)
 * 4: FE    (R)     Frame error (bad frame - stop bits)
 * 3: DOR   (R)     Data overrun
 * 2: PE    (R)     Parity Error
 * 1: U2X   (R/W)   Double Speed (1), Normal Speed (0)
 * 0: MPCM  (R/W)   Multiprocessor Communication Mode
 * */
#define UART_UCSRA_REG   *( ( volatile u8 * ) 0x2B )

/* USART Control and status Register B */
/* 7: RXCIE (R/W)   Receive Interrupt Enable
 * 6: TXCIE (R/W)   Transmit Interrupt Enable
 * 5: UDRIE (R/W)   Data register Interrupt Enable (if data UDR register empty)
 * 4: RXEN  (R/W)   Enable Receive
 * 3: TXEN  (R/W)   Enable Transmit
 * 2: UCSZ2 (R/W)   Data Length
 * 1: RXB8  (R)     Receive Data Bit 8 // must be read before reading the low bits to the UDR
 * 0: TXB8  (R/W)   Transmit Dat Bit 8 // must be written before writing the low bits to the UDR
 * */
#define UART_UCSRB_REG   *( ( volatile u8 * ) 0x2A )

/* USART Control and status Register C */
/* 7: URSEL (R/W)   Select bit for which register (1: UCSRC, 0: UBRRH)
 * 6: UMSEL (R/W)
 * 5: UPM1  (R/W)   Parity Mode
 * 4: UPM0  (R/W)   Parity Mode
 * 3: USBS  (R/W)
 * 2: UCSZ1 (R/W)   Data Length
 * 1: UCSZ0 (R/W)   Data Length
 * 0: UCPOL (R/W)
 * */
#define UART_UCSRC_REG   *( ( volatile u8 * ) 0x40 )

/* Baud Rate Register Low Byte */
/* 7: UBRR 7
 * 6: UBRR 6
 * 5: UBRR 5
 * 4: UBRR 4
 * 3: UBRR 3
 * 2: UBRR 2
 * 1: UBRR 1
 * 0: UBRR 0
 * */
#define UART_UBRRL_REG   *( ( volatile u8 * ) 0x29 )

/* Baud Rate Register High Byte */
/* 7: URSEL (R/W)   Select bit for which register (1: UCSRC, 0: UBRRH)
 * 6: -
 * 5: -
 * 4: -
 * 3: UBRR 11
 * 2: UBRR 10
 * 1: UBRR 9
 * 0: UBRR 8
 * */
#define UART_UBRRH_REG   *( ( volatile u8 * ) 0x40 )


#endif /* UART_PRIVATE_H_ */