/*
 * uart_preconfig.h
 *
 * Created: 24/5/2023 2:59:47 AM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 


#ifndef UART_PRECONFIG_H_
#define UART_PRECONFIG_H_

#ifndef F_OSC
    // System frequency Oscillator in Hz
    #define F_OSC 8000000UL // 8 MHz
#endif

/*
 * Shows Syn/Ack/SOT/EOT characters on Virtual Terminal
 * To easily differentiate between data packets
 * */
#define UART_SHOW_DEBUG_CHARS TRUE

/* TURN OFF FOR PRODUCTION USE */
#define UART_DEBUG FALSE

#if UART_SHOW_DEBUG_CHARS == TRUE
    // Start of Transmission character
    #define UART_SOT_CHAR '^'
    // End of Transmission character
    #define UART_EOT_CHAR '$'

    #define UART_HANDSHAKE_SYN_CHAR '&'
    #define UART_HANDSHAKE_ACK_CHAR '%'
#else
    // Start of Transmission character
    #define UART_SOT_CHAR 0x02
    // End of Transmission character
    #define UART_EOT_CHAR 0x03

    #define UART_HANDSHAKE_SYN_CHAR 0x05
    #define UART_HANDSHAKE_ACK_CHAR 0x06
#endif

#define UART_CARRIAGE_RETURN_CHAR 0x13  // Enter Key
#define UART_NEW_LINE_CHAR 0x0D         // \r

#define UART_TX_RETRY_COUNT 3 // Retries to transmit before failing

#endif /* UART_PRECONFIG_H_ */