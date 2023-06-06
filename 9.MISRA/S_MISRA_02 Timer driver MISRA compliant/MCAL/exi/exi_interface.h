/*
 * exi_interface.h
 *
 * Created: 6/4/2023 7:33:50 PM
*  Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 */
#ifndef EXI_INTERFACE_H_
#define EXI_INTERFACE_H_

/*------------------ TYPEDEFS ------------------*/

/**
 * @brief       :   EXI Interrupt number
 */
typedef enum{
    EXI_INT0        =   0,
    EXI_INT1,
    EXI_INT2,
    EXI_INT_TOTAL
} enu_exi_int_t_;


typedef enum {
    EXI_SUCCESS     =   0,
    EXI_ERROR
} enu_exi_error_t_;

/**
 * Interrupt sense modes
 */
typedef enum {

    /** Interrupts on low level */
    EXI_SENSE_LOW_LEVEL     =   0xFC, // also clear bits 0, 1 (Interrupt sense control bits)

    /** Interrupts on any logical change */
    EXI_SENSE_ANY_LEVEL     =   0x01,

    /** Interrupts on Falling edge */
    EXI_SENSE_FALLING_EDGE  =   0x02,

    /** Interrupts on Rising edge */
    EXI_SENSE_RISING_EDGE   =   0x03,
} enu_exi_sense_mode_t_;


/*------------------ Functions' Prototypes ------------------*/

/**
 * @brief                               :   Sets and enables an external interrupt pin with given mode
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 * @param[in]   enu_exi_sense_mode      :   sense mode enum
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_    EXI_enableInterrupt     (enu_exi_int_t_ enu_exi_interrupt, enu_exi_sense_mode_t_ enu_exi_sense_mode);

/**
 * @brief                               :   Disables a given interrupt pin
 *
 * @param[in]   enu_exi_interrupt       :   Interrupt number (EXI_INT0, EXI_INT1, EXI_INT2)
 *
 * @return  EXI_SUCCESS                 :   In case of Successful Operation
 *          EXI_ERROR                   :   In case of Failed Operation
 */
enu_exi_error_t_    EXI_disableInterrupt    (enu_exi_int_t_ enu_exi_interrupt);


/**
 * @brief                               :   Disables all external interrupts
 */
void    EXI_disableAll          (void);


#endif /* EXI_INTERFACE_H_ */