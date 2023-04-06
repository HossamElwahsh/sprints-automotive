/*
 * registers.h
 *
 * Created: 5/4/2023 9:40:34 PM
 *  Author: Hossam
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "../Common/types.h"

/**********************************************************/
/**                 ATmega32 registers                   **/
/**********************************************************/

/* Status Register */
#define SREG *((volatile uint8_t* )0x5F) // 8-bit register

/**********************************************************/
/**                     PORTS registers                  **/
/**********************************************************/

/* PORT A */
#define PORT_A *((volatile uint8_t* )0x3B) // 8-bit register
#define DDR_A *((volatile uint8_t* )0x3A)  // 8-bit register
#define PIN_A *((volatile uint8_t* )0x39)  // 8-bit register

/* PORT B */
#define PORT_B *((volatile uint8_t* )0x38) // 8-bit register
#define DDR_B *((volatile uint8_t* )0x37)  // 8-bit register
#define PIN_B *((volatile uint8_t* )0x36)  // 8-bit register

/* PORT C */
#define PORT_C *((volatile uint8_t* )0x35) // 8-bit register
#define DDR_C *((volatile uint8_t* )0x34)  // 8-bit register
#define PIN_C *((volatile uint8_t* )0x33)  // 8-bit register

/* PORT D */
#define PORT_D *((volatile uint8_t* )0x32) // 8-bit register
#define DDR_D *((volatile uint8_t* )0x31)  // 8-bit register
#define PIN_D *((volatile uint8_t* )0x30)  // 8-bit register


/**********************************************************/
/**            Timer-0 Registers                          */
/**********************************************************/

// Timer/Counter Control Register
#define TCCR0 *((volatile uint8_t* )0x53)  // 8-bit register

// Timer/Counter Data Register - 8 bit
#define TCNT0 *((volatile uint8_t* )0x52)  // 8-bit register

/* TIMER-0 OUTPUT COMPARE REGISTER */
#define OCR0 *((volatile uint8_t* )0x5c)  // 8-bit register

/* Timer/Counter Interrupt Flag Register */
#define TIFR *((volatile uint8_t* )0x58)  // 8-bit register

// Timer/Counter Interrupt Mask Register
#define TIMSK *((volatile uint8_t* )0x59)  // 8-bit register

/**********************************************************/
/**              External Interrupt Registers             */
/**********************************************************/
/* MCUCR: MCU Control Register */
#define MCUCR *((volatile uint8_t* )0x55)  // 8-bit register

/* General Interrupt Control Register */
#define GICR *((volatile uint8_t* )0x5B)  // 8-bit register

/* General Interrupt Flag Register */
#define GIFR *((volatile uint8_t* )0x5A)  // 8-bit register


#endif /* REGISTERS_H_ */