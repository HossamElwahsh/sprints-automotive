/*
 * timer.c
 *
 * Created: 6/4/2023 4:24:55 PM
 *  Author: Hossam
 */

/* Include .h */
#include "timer.h"


/* Variables */
EN_ClockSelection_t clockPrescaler = Prescale1024;
//int desiredOverflowsCount = 0;
//int currentOverflowNumber = 0;

/**
 * Initialize timer-0 with given operating mode, clears timer data
 * @param operatingMode one of (Normal, CTC, FAST_PWM, PWM_PHASE_CORRECT)
 */
EN_timerError_t timer_init(EN_TimerMode_t operatingMode)
{
    switch (operatingMode) {
        case NORMAL:
            TCCR0 &= NORMAL;
            return TIMER_OK;
        case CTC:
        case FAST_PWM:
        case PWM_PHASE_CORRECT:
            TimerClearModes();
            TCCR0 |= operatingMode; // set requested timer mode
            return TIMER_OK;
        default:
            return TIMER_Error; // error bad operation mode
    }

    // Reset timer initial value
    TCNT0 = 0;
}

/**
 * starts the timer
 */
static EN_timerError_t timer_start(EN_ClockSelection_t enClockPrescaleSelection)
{
    switch (enClockPrescaleSelection) {
        case NoClock:
            TCCR0 &= NoClock; // set timer pre-scaler & start
            return TIMER_OK;
        case NoPrescaling:
        case Prescale8:
        case Prescale64:
        case Prescale256:
        case Prescale1024:
        case ExternalFallingEdge:
        case ExternalRisingEdge:
            TimerClearClockSelection();
            TCCR0 |= enClockPrescaleSelection; // set timer pre-scaler & start
            return TIMER_OK;
        default:
            return TIMER_Error;
    }
}

/**
 * Manually set initial timer start value
 * @param timerInitValue [in] value (0 -> 255)
 */
static void timer_setTimerValue(uint8_t timerInitValue)
{
    TCNT0 = timerInitValue;
}

/**
 * blocks for a given delay time before returning
 * @param desiredDelay [in] (ms) delay to wait for - Range 2ms upto 60 seconds, sensitivity ~2 ms
 * @return Error if any
 */
void timer_delay(uint16_t desiredDelay)
{
    // calculate number of overflows needed
    double systemClock = SystemClockInMhz * 1000000.0f;

    // timer pre-scaler is pre-set to /1024

    // todo variable pre-scaler
    double oneTickTime = (1024 / systemClock) * 1000; // in ms

    // Calculate max delay time in one timer runs
    // using bitShift instead of power to reduce time, i.e. (1 << timerNBits) is equal to (2^timerNBits)
    double maxDelay = oneTickTime * (1 << timerNBits); // in ms

    // Calculate number of overflows needed to achieve desired delay
    int overflowsCount = ceil(desiredDelay / maxDelay); // in counts #

    // Calculate Timer Initial value to achieve desired delay
    uint8_t timerInitValue;
    if (overflowsCount > 1)
    {
//        timerInitValue = floor(pow(2, timerNBits) - ((desiredDelay / oneTickTime) / overflowsCount)); // in decimal  (0 - 255)

        // using bitShift instead of power to reduce time
        timerInitValue = (uint8_t)((1 << timerNBits) - ((desiredDelay - (maxDelay * (overflowsCount - 1))) / oneTickTime)); // in decimal  (0 - 255)
    }
    else
    {
        timerInitValue = floor((maxDelay - desiredDelay)/oneTickTime); // in decimal (0 - 255)
    }

    // Update Timer0 Registers with calculated values
    timer_setTimerValue(timerInitValue);


    // todo variable pre-scaler choice
    // Timer Start
    timer_start(clockPrescaler);

    // desired delay wait loop
    int currentOverflowNumber = 0;

    do{
        while((bitRead(TIFR, 0)) == 0); // wait for next overflow

        // increment
        currentOverflowNumber++;

        // reset timer overflow
        bitSet(TIFR, 0);
    } while (currentOverflowNumber < overflowsCount);

    // Stop timer
    timer_reset();
}

/**
 * Stops the timer, clears overflow flags
 */
void timer_reset()
{
    TCCR0 &= 0x00; // clear last 3 bits (CS2:CS0) Clock selection bits
    bitClear(TIFR, 0); // clear overflow flag
    TCNT0 = 0; // clear timer data
}