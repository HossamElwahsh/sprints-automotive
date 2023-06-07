/*
 * exi_private.h
 *
 * Created: 29/5/2023 3:01:33 AM
 *  Author: hossam
 */ 


#ifndef EXI_PRIVATE_H_
#define EXI_PRIVATE_H_

#include "std.h"

/* PRIVATE UTILS */
#include "interrupts.h"
#include "bit_manipulation.h"

/*------------------ External Interrupt Registers ------------------*/

/* MCUCR: MCU Control Register */
#define EXI_MCUCR_REG *((volatile uint8_t_* )0x55)  // 8-bit register

/* General Interrupt Control Register */
#define EXI_GICR_REG *((volatile uint8_t_* )0x5B)  // 8-bit register

/* General Interrupt Flag Register */
#define EXI_GIFR_REG *((volatile uint8_t_* )0x5A)  // 8-bit register




#endif /* EXI_PRIVATE_H_ */