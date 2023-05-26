/*
 * uart_private.h
 *
 * Created: 23/5/2023 6:57:31 AM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 


#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* UART TX Transmitter States */
typedef enum{
    UART_TX_STATE_IDLE = 0,

    /* Handshake States */
//    UART_TX_STATE_WAIT_FOR_HANDSHAKE,
//    UART_TX_STATE_HANDSHAKING,
//    UART_TX_STATE_HANDSHAKING_WAIT_ACK,
//    UART_TX_STATE_HANDSHAKE_OK,
//    UART_TX_STATE_HANDSHAKE_FAILED,

    /* Sending SOT */
//    UART_TX_STATE_STARTING,

    /* Wait for byte to transmit */
    UART_TX_STATE_WAIT,

    /* Sending Data */
    UART_TX_STATE_IN_PROGRESS,

    /* Sending EOT */
    UART_TX_STATE_ENDING,

    /* Sending Single Byte (fallback) */
    UART_TX_STATE_SINGLE_TRANSMIT,

    /* Sending control chars silently */
//    UART_TX_STATE_TRANSMITTING_CONTROL_CHARS,

    UART_TX_STATE_COMPLETE
}enu_uart_tx_state_t_;

/* UART RX Receiver States */
typedef enum{
    UART_RX_STATE_IDLE = 0,
    UART_RX_STATE_IN_PROGRESS,
    UART_RX_STATE_HAS_DATA, // Just completed or has previous data
    UART_RX_STATE_BUFFER_FULL,
//    UART_RX_STATE_COMPLETE,

    /* Waiting for ACK to start transmission */
//    UART_RX_STATE_HANDSHAKING_WAIT_ACK,
}enu_uart_rx_state_t_;

/* UART General States */
typedef enum{
    UART_STATE_IDLE = 0,
    UART_STATE_TRANSMITTING,
    UART_STATE_RECEIVING,
}enu_uart_state_t_;

typedef struct{
    enu_uart_state_t_ enu_uart_state;
    enu_uart_rx_state_t_ enu_uart_rx_state;
    enu_uart_tx_state_t_ enu_uart_tx_state;
}str_uart_state_t_;


/* ****************************************************/
/*            UART  Registers Locations               */
/* ****************************************************/

/* USART I/O DATA REGISTER */
#define UART_UDR_REG   *( ( volatile uint8_t_ * ) 0x2C )

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
#define UART_UCSRA_REG   *( ( volatile uint8_t_ * ) 0x2B )
#define UART_UCSRA_RXC  7 // (R)     Reception Complete
#define UART_UCSRA_TXC  6 // (R/W)   Transmission Complete
#define UART_UCSRA_UDRE 5 // (R)     Data register empty (initial 1)
#define UART_UCSRA_U2X  1 // (R/W)   Double Speed (1), Normal Speed (0)

/* USART Control and status Register B */
/* 7: RXCIE (R/W)   Receive Interrupt Enable
 * 6: TXCIE (R/W)   Transmit Interrupt Enable
 * 5: UDRIE (R/W)   Data register Interrupt Enable (if data UDR register empty)
 * 4: RXEN  (R/W)   Enable Receive
 * 3: TXEN  (R/W)   Enable Transmit
 * 2: UCSZ2 (R/W)   Data Length
 * 1: RXB8  (R)     Receive Data Bit 8 // must be read before reading the low bits to the UDR
 * 0: TXB8  (R/W)   Transmit Data Bit 8 // must be written before writing the low bits to the UDR
 * */
// Register
#define UART_UCSRB_REG   *( ( volatile uint8_t_ * ) 0x2A )
// Bits
#define UART_UCSRB_RXCIE 7 // (R/W)   Receive Interrupt Enable
#define UART_UCSRB_TXCIE 6 // (R/W)   Transmit Interrupt Enable
#define UART_UCSRB_UDRIE 5 // (R/W)   Data register Interrupt Enable (if data UDR register empty)
#define UART_UCSRB_RXEN  4 // (R/W)   Enable Receive
#define UART_UCSRB_TXEN  3 // (R/W)   Enable Transmit
#define UART_UCSRB_UCSZ2 2 // (R/W)   Data Length
#define UART_UCSRB_RXB8  1 // (R)     Receive Data Bit 8 // must be read before reading the low bits to the UDR
#define UART_UCSRB_TXB8  0 // (R/W)   Transmit Dat Bit 8 // must be written before writing the low bits to the UDR

/* USART Control and status Register C */
/* 7: URSEL (R/W)   Select bit for which register (1: UCSRC, 0: UBRRH)
 * 6: UMSEL (R/W)
 * 5: UPM1  (R/W)   Parity Mode
 * 4: UPM0  (R/W)   Parity Mode
 * 3: USBS  (R/W)   Stop bit select
 * 2: UCSZ1 (R/W)   Data Length
 * 1: UCSZ0 (R/W)   Data Length
 * 0: UCPOL (R/W)
 * */
#define UART_UCSRC_REG   *( ( volatile uint8_t_ * ) 0x40 )
#define UART_UCSRC_URSEL 7 // (R/W)   Select bit for which register (1: UCSRC, 0: UBRRH)
#define UART_UCSRC_UMSEL 6 // (R/W)
#define UART_UCSRC_UPM1  5 // (R/W)   Parity Mode
#define UART_UCSRC_UPM0  4 // (R/W)   Parity Mode
#define UART_UCSRC_USBS  3 // (R/W)   Stop bit select
#define UART_UCSRC_UCSZ1 2 // (R/W)   Data Length
#define UART_UCSRC_UCSZ0 1 // (R/W)   Data Length
#define UART_UCSRC_UCPOL 0 // (R/W)

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
#define UART_UBRRL_REG   *( ( volatile uint8_t_ * ) 0x29 )

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
#define UART_UBRRH_REG   *( ( volatile uint8_t_ * ) 0x40 )
#define UART_UBRRH_URSEL 7




#endif /* UART_PRIVATE_H_ */