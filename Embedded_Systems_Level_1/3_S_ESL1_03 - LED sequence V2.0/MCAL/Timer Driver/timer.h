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

#define nBits 8
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
    OK,
    Error
}EN_timerError_t;

typedef struct ST_timerCalculations_t
{
    int overflowsNo;        // 4 bytes
    uint8_t initialValue;   // 1 byte
    EN_ClockSelection_t enClockSelection; // 1 byte
} ST_timerCalculations_t; // 6 bytes

/**
 * Initialize timer-0 with given operating mode
 *  and automatically calculates init start value and overflow count to achieve the
 *  desiredDelayMs (ms)
 * @param operatingMode one of (Normal, CTC, FAST_PWM, PWM_PHASE_CORRECT)
 * @param desiredDelayMs desired delay in milliseconds
 */
EN_timerError_t timer_init(EN_TimerMode_t operatingMode);

/**
 * Manually set initial timer start value
 * @param timerInitValue [in] value (0 -> 255)
 */
void timer_setTimerValue(uint8_t timerInitValue);

/**
 * Automatically calculates init start value and overflow count to achieve the desiredDelayMs (ms)
 * @param desiredDelayMs desired delay in milliseconds
 * then starts the timer
 */
ST_timerCalculations_t timer_calculateAndSetTimerValue(float desiredDelayMs);

/**
 * Automatically calculates init start value and overflow count to achieve the desiredDelayMs (ms)
 * then starts the timer
 * @param desiredDelayMs desired delay in milliseconds
 * then starts the timer
 */
ST_timerCalculations_t timer_calculateAndStartTimer(float desiredDelayMs);

/**
 * Retrieves timer start value and store it in timerValue
 * @param timerValue [out] current timer value
 */
void timer_getTimerValue(uint8_t * timerValue);

EN_timerError_t timer_start(EN_ClockSelection_t enClockPrescaleSelection);

/**
 * Stops the timer
 */
void timer_stop();


void timer_getState();

/**
 * Busy lock until next overflow occurrence (counter/timer reset)
 */
void timer_awaitNextOverflow();

#endif /* TIMER_H_ */