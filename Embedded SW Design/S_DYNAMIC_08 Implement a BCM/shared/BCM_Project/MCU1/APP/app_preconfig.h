/*
 * app_preconfig.h
 *
 * Created: 25/5/2023 11:44:12 AM
 *  Author: hossam
 */ 


#ifndef APP_PRECONFIG_H_
#define APP_PRECONFIG_H_

#define SEND_LED_PORT   DIO_PORT_B
#define SEND_LED_PIN    DIO_PIN_1

#define RECEIVE_LED_PORT   DIO_PORT_B
#define RECEIVE_LED_PIN    DIO_PIN_2

#define TEST_STR "\r\rLorem ipsum dolor sit amet, consectetur adipiscing elit.\r\r"


/* ECHO MODE */
#define APP_TEST_ENABLE 1
//#define APP_TEST_ENABLE 0

#define SYN_STR "BCM Operating"
#define ACK_STR "Confirm BCM Operating"

#endif /* APP_PRECONFIG_H_ */