/*
 * interrupts.c
 *
 * Created: 6/4/2023 8:14:00 PM
 *  Author: Hossam
 */ 

/// Include .h files
#include "interrupts.h"

/**
 * 2. Choose interrupt sense -> use MCUCR
 * @param interrupt [in] Interrupt number (INT0, INT1)
 * @param interruptSenseMode [in] sense mode enum
 */
void EXI_enableInterrupt(EN_EXI_INT_t interrupt, EN_EXI_SENSE_t interruptSenseMode)
{
    // enable global interrupt flag
    sei();

    // enable required interrupt
    if(interrupt == INT0)
    {
        switch (interruptSenseMode) {
            case LOW_LEVEL:
                MCUCR &= LOW_LEVEL;
                break;
            case ANY_LEVEL:
            case FALLING_EDGE:
            case RISING_EDGE:
                MCUCR &= 0xFC; // clear INT0 bits
                MCUCR |= interruptSenseMode; // sets INT0 sense mode
                break;
        }

        // 3. enable INT0
        bitSet(GICR, 6);

    }else if(interrupt == INT1)
    {
        switch (interruptSenseMode) {
            case LOW_LEVEL:
                // todo check calculation
                MCUCR &= ((LOW_LEVEL<<2) | 0x3);
                break;
            case ANY_LEVEL:
            case FALLING_EDGE:
            case RISING_EDGE:
                MCUCR &= 0xF3; // clear INT1 bits

                // todo check calculation
                MCUCR |= ((interruptSenseMode << 2) | 0x3); // sets INT1 sense mode
                break;
        }

        // 3. enable INT1
        bitSet(GICR, 7);
    }
}

/**
 * Disables a given interrupt pin
 * @param interrupt [in] enum (INT0, INT1)
 */
void EXI_disableInterrupt(EN_EXI_INT_t interrupt)
{
    switch (interrupt) {
        case INT0:
            bitClear(GICR, 6);
            break;
        case INT1:
            bitClear(GICR, 7);
            break;
        default:
            /* Do Nothing */
            break;
    }
}


/**
 * Disables global interrupts
 *  sets I-(7th) bit in SREG to 0
 */
void EXI_disableAll(void)
{
    cli(); // disable global interrupts flag
    bitClear(GICR, 6); // disable INT0
    bitClear(GICR, 7); // disable INT1
}

