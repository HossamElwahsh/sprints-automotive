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


/* TURN OFF FOR PRODUCTION USE */
//#define UART_DEBUG 1
#define UART_DEBUG 0

#define UART_EOT_CHAR '\0'

#define UART_CARRIAGE_RETURN_CHAR 0x13  // Enter Key
#define UART_NEW_LINE_CHAR 0x0D         // \r


#endif /* UART_PRECONFIG_H_ */