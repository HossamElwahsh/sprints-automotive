/**
 ** @file                   wdt.h
 ** @brief                  This is header file for watchdog timer HAL for TM4C123GH6PM
 ** @author                 Karim Osama
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

#ifndef WDT_H_
#define WDT_H_

/*----------------------------------------------------------/
/- INCLUDES -----------------------------------------------/
/----------------------------------------------------------*/
#include "common.h"
#include "TM4C123.h"
/*----------------------------------------------------------/
/- PRIMITIVE TYPES ----------------------------------------/
/----------------------------------------------------------*/
typedef void(*tpf_wdt_cb)(void);
/*---------------------------------------------------------/
/- ENUM --------------------------------------------------/
/---------------------------------------------------------*/
typedef enum 
{
	WDT0 =0,
	WDT1 = 1,
	INVALID_WDn
}wdt_index_t;

typedef enum 
{
	USE_NORMAL_INT = 0,
	USE_NMI =1,
	DISABLE_INT = 2,
	INVALID_INT_VALUE
}wdt_int_t;
/*----------------------------------------------------------/
/- STRUCTS AND UNIONS -------------------------------------/
/----------------------------------------------------------*/
typedef struct
{
	wdt_index_t wdt_index; 		/*Index of the WDT 0 or 1*/
	uint32_t timeout_ms;		/*Timeout in milliseconds*/
	boolean use_test_mode; 		/*Pass true to run in test mode*/
	boolean use_reset_mode; 		/*Pass true to enable restting mode*/
	wdt_int_t wdt_int;			/*Type of interrupt (NMI or Normal)*/
	tpf_wdt_cb pf_wdt_cb;		/*Callback to the app*/
}wdt_cfg_t;


/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/
/**
 *  @brief 			This function initializes the wdt hal.
 *  @param[in]		pwdt_cfg pointer to input configuration structure.
 *  @return         ::SUCCESS in case of success, otherwise, review error code
 */
int32_t wdt_init(wdt_cfg_t* pwdt_cfg);
/**
 *  @brief 			This function resets the WDT to start from the max.
 *  @param[in]		wdtn: WDT index
 */
void wdt_reset(wdt_index_t wdtn);
/**
 *   @brief This function check the status of an interrupt.
 *   @param[in]	wdtn: WDT index to check its interrupt status
 *  @return ::TRUE in case of timeout occured, fasle, if timeout did not occur
 */
boolean wdt_get_int_status(wdt_index_t wdtn);

/**
 *  @brief 			This function resets the WDT to start from the max.
 *  @param[in]		wdtn: WDT index
 */
void wdt_reset(wdt_index_t wdtn);
/**
 *   @brief This function check the status of an interrupt.
 *   @param[in]	wdtn: WDT index to check its interrupt status
 *  @return ::TRUE in case of timeout occured, fasle, if timeout did not occur
 */
boolean wdt_get_int_status(wdt_index_t wdtn);
/**
 *   @brief This function deinitializes the wdt hal.
 *   @param[in]	wdtn: WDT index to disable
 */
void wdt_deinit(wdt_index_t wdtn);

#endif
