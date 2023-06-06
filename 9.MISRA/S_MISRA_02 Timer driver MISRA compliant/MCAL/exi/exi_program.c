/*
 *
 * Created: 6/4/2023 8:14:00 PM
 * Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */ 

/* Includes */
#include "exi_interface.h"
#include "exi_private.h"

/**
 * @brief                               :   Sets and enables an external interrupt pin with given mode
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 * @param[in]   enu_exi_sense_mode      :   sense mode enum
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_ EXI_enableInterrupt(enu_exi_int_t_ enu_exi_interrupt, enu_exi_sense_mode_t_ enu_exi_sense_mode)
{
    // enable global interrupt flag
    sei();
    // enable required interrupt
    if(enu_exi_interrupt == EXI_INT0)
    {
        switch (enu_exi_sense_mode) {
            case EXI_SENSE_LOW_LEVEL:
                EXI_MCUCR_REG &= EXI_SENSE_LOW_LEVEL;
                break;
            case EXI_SENSE_ANY_LEVEL:
            case EXI_SENSE_FALLING_EDGE:
            case EXI_SENSE_RISING_EDGE:
                EXI_MCUCR_REG &= 0xFC; // clear INT0 bits
                EXI_MCUCR_REG |= enu_exi_sense_mode; // sets INT0 sense mode
                break;
            default:
                return EXI_ERROR;
        }

        // 3. enable INT0
        SET_BIT(EXI_GICR_REG, 6);

    }else if(enu_exi_interrupt == EXI_INT1)
    {
        switch (enu_exi_sense_mode) {
            case EXI_SENSE_LOW_LEVEL:
                EXI_MCUCR_REG &= ((EXI_SENSE_LOW_LEVEL<<2) | 0x3);
                break;
            case EXI_SENSE_ANY_LEVEL:
            case EXI_SENSE_FALLING_EDGE:
            case EXI_SENSE_RISING_EDGE:
                EXI_MCUCR_REG &= 0xF3; // clear INT1 bits

                EXI_MCUCR_REG |= ((enu_exi_sense_mode << 2) | 0x3); // sets INT1 sense mode
                break;
            default:
                return EXI_ERROR;
        }

        // 3. enable INT1
        SET_BIT(EXI_GICR_REG, 7);
    }else{
        return EXI_ERROR;
    }

    return EXI_SUCCESS;
}

/**
 * @brief                               :   Disables a given interrupt pin
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_ EXI_disableInterrupt(enu_exi_int_t_ enu_exi_interrupt)
{
    switch (enu_exi_interrupt) {
        case EXI_INT0:
            CLR_BIT(EXI_GICR_REG, 6);
            break;
        case EXI_INT1:
            CLR_BIT(EXI_GICR_REG, 7);
            break;
        default:
            /* Do Nothing */
            return EXI_ERROR;
    }
    return EXI_SUCCESS;
}


/**
 * @brief                               :   Disables all external interrupts
 */
void EXI_disableAll(void)
{
    cli(); // disable global interrupts flag
    CLR_BIT(EXI_GICR_REG, 6); // disable INT0
    CLR_BIT(EXI_GICR_REG, 7); // disable INT1
}

