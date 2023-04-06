/*
 * interrupts.h
 *
 * Created: 6/4/2023 7:33:50 PM
 *  Author: Hossam
 */
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/* Include .h */
#include "../registers.h"
#include "../../Common/bit_manipulation.h"

/************************************************************************/
/** MACROS   										                    */
/************************************************************************/

/* External Interrupt Request 0 */
#define EXT_INT_0 __vector_1

/* External Interrupt Request 1 */
#define EXT_INT_1 __vector_2

/* External Interrupt Request 2 */
#define EXT_INT_2 __vector_3

/* Macro for global interrupt enable / disable */

/**
 * 1. Enables global interrupts
 *  sets I-(7th) bit in SREG to 1
 */
#define sei() __asm__ __volatile__ ("sei" ::: "memory")

/**
* Disables global interrupts
*  sets I-(7th) bit in SREG to 0
*/
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

/* ISR definition */
#define ISR(INT_VECT) void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)


/************************************************************************/
/** TYPEDEFS										                    */
/************************************************************************/

typedef enum EN_EXI_INT_t {
    INT0, INT1
} EN_EXI_INT_t;


typedef enum EN_EXI_ERROR_t {
    EXI_OK,
    EXI_ERROR
} EN_EXI_ERROR_t;

/**
 * Interrupt sense modes
 */
typedef enum EN_EXI_SENSE_t {

    // Interrupts on low level
    LOW_LEVEL = 0xFC, // also clear bits 0, 1 (Interrupt sense control bits)

    // Interrupts on any logical change
    ANY_LEVEL = 0x01,

    // Interrupts on Falling edge
    FALLING_EDGE = 0x02,

    // Interrupts on Rising edge
    RISING_EDGE = 0x03
} EN_EXI_SENSE_t;


/************************************************************************/
/** EX_interrupts Functions     										*/
/************************************************************************/


/**
 * Sets and enables an external interrupt pin with given mode
 * @param interrupt [in] Interrupt number (INT0, INT1)
 * @param interruptSenseMode [in] sense mode enum
 */
EN_EXI_ERROR_t EXI_enableInterrupt(EN_EXI_INT_t interrupt, EN_EXI_SENSE_t interruptSenseMode);

/**
 * Disables a given interrupt pin
 * @param interrupt [in] enum (INT0, INT1)
 */
EN_EXI_ERROR_t EXI_disableInterrupt(EN_EXI_INT_t interrupt);


/**
* Disables global interrupts
*  sets I-(7th) bit in SREG to 0
*/
void EXI_disableAll(void);


#endif /* INTERRUPTS_H_ */