/*
 * timer.h
 *
 * Created: 6/4/2023 4:25:01 PM
 *  Author: Hossam
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Common/types.h"
#include "../../Common/bit_manipulation.h"
#include "../../MCAL/registers.h"
#include <math.h>

/* Microcontroller Related Macros */
#define timerNBits 8
#define SystemClockInMhz 1

/* Clears mode bits in timer */
#define TimerClearModes() TCCR0 &= 0xB7

/* Clears Clock selection bits */
#define TimerClearClockSelection() TCCR0 &= 0xF8

// sets bit 6, 3 (WGM00, WGM01) Waveform generation mode bit
typedef enum EN_TimerMode_t
{
    NORMAL = 0xB7,
    CTC = 0x08,
    FAST_PWM = 0x48,
    PWM_PHASE_CORRECT = 0x40
}EN_TimerMode_t;

typedef enum EN_ClockSelection_t
{
    NoClock = 0xF8,         // stops clock - no clock is set
    NoPrescaling = 0x01,    // clock matches internal clock with no prescaling
    Prescale8 = 0x02,       // prescale clock /8
    Prescale64 = 0x03,      // prescale clock /64
    Prescale256 = 0x04,     // prescale clock /256
    Prescale1024 = 0x05,    // prescale clock /1024

    /* External Clock on T0 pin with falling edge */
    ExternalFallingEdge = 0x06,

    /* External Clock on T0 pin with rising edge */
    ExternalRisingEdge = 0x07,
}EN_ClockSelection_t; // 1 byte


typedef enum EN_timerError_t
{
    TIMER_OK,
    TIMER_Error
}EN_timerError_t;

/**
 * Initialize timer-0 with given operating mode
 *  and automatically calculates init start value and overflow count to achieve the
 *  desiredDelayMs (ms)
 * @param operatingMode one of (Normal, CTC, FAST_PWM, PWM_PHASE_CORRECT)
 * @param desiredDelayMs desired delay in milliseconds
 */
EN_timerError_t timer_init(EN_TimerMode_t operatingMode);

/**
 * blocks for a given delay time before returning
 * @param desiredDelay [in] (ms) delay to wait for - Range 2ms upto 60 seconds, sensitivity ~1.2 ms
 * @return Error if any
 */
void timer_delay(uint16_t desiredDelay);

/**
 * sets given Prescaler for timer0
 * @param enClockPrescaleSelection [in] prescaler enum
 * @return
 */
static EN_timerError_t timer_start(EN_ClockSelection_t enClockPrescaleSelection);

/*
*//**
 * Manually set initial timer start value
 * @param timerInitValue [in] value (0 -> 255)
 */
static void timer_setTimerValue(uint8_t timerInitValue);

/**
 * Resets the timer
 */
void timer_reset();

#endif /* TIMER_H_ */