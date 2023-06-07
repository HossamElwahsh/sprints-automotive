/*
 * timer_private.h
 *
 * Created: 29/5/2023 5:34:51 AM
 *  Author: hossam
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/* ----------------------------- Timer-0 Registers ----------------------------- */

// Timer/Counter Control Register
#define TCCR0 *((volatile uint8_t_* )0x53)  // 8-bit register

// Timer/Counter Data Register - 8 bit
#define TCNT0 *((volatile uint8_t_* )0x52)  // 8-bit register

/* TIMER-0 OUTPUT COMPARE REGISTER */
#define OCR0 *((volatile uint8_t_* )0x5c)  // 8-bit register

/* Timer/Counter Interrupt Flag Register */
#define TIFR *((volatile uint8_t_* )0x58)  // 8-bit register

// Timer/Counter Interrupt Mask Register
#define TIMSK *((volatile uint8_t_* )0x59)  // 8-bit register


#endif /* TIMER_PRIVATE_H_ */