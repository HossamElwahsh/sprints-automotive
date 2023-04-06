/*
 * timer.c
 *
 * Created: 6/4/2023 4:24:55 PM
 *  Author: Hossam
 */

/* Include .h */
#include "timer.h"

/**
 * Initialize timer-0 with given operating mode, clears timer data
 * @param operatingMode one of (Normal, CTC, FAST_PWM, PWM_PHASE_CORRECT)
 */
EN_timerError_t timer_init(EN_TimerMode_t operatingMode)
{
    switch (operatingMode) {
        case NORMAL:
            TCCR0 &= NORMAL;
            return OK;
        case CTC:
        case FAST_PWM:
        case PWM_PHASE_CORRECT:
            TimerClearModes();
            TCCR0 |= operatingMode; // set requested timer mode
            return OK;
        default:
            return Error; // error bad operation mode
    }

    // Reset timer initial value
    TCNT0 = 0;
}

/**
 * starts the timer
 */
EN_timerError_t timer_start(EN_ClockSelection_t enClockPrescaleSelection)
{
    switch (enClockPrescaleSelection) {
        case NoClock:
            TCCR0 &= NoClock; // set timer pre-scaler & start
            return OK;
        case NoPrescaling:
        case Prescale8:
        case Prescale64:
        case Prescale256:
        case Prescale1024:
        case ExternalFallingEdge:
        case ExternalRisingEdge:
            TimerClearClockSelection();
            TCCR0 |= enClockPrescaleSelection; // set timer pre-scaler & start
            return OK;
        default:
            return Error;
    }
}

/**
 * Manually set initial timer start value
 * @param timerInitValue [in] value (0 -> 255)
 */
void timer_setTimerValue(uint8_t timerInitValue)
{
    TCNT0 = timerInitValue;
}

/**
 * Busy until lock next overflow occurrence (counter/timer reset)
 */
void timer_awaitNextOverflow()
{
    while((bitRead(TIFR, 0)) == 0); // wait for overflow
}

/**
 * Stops the timer, clears overflow flags
 */
void timer_stop()
{
    TCCR0 &= NoClock; // clear last 3 bits (CS2:CS0) Clock selection bits
    bitClear(TIFR, 0); // clear overflow flag
    TCNT0 = 0; // clear timer data
}