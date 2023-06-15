/**
 ** @file                   wdt.c
 ** @brief                  This file implements watchdog timer HAL for TM4C123GH6PM
 ** @author                 Karim Osama
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

/*----------------------------------------------------------/
/- INCLUDES -----------------------------------------------/
/----------------------------------------------------------*/
#include "wdt.h"

/*---------------------------------------------------------/
/- LOCAL MACROS ------------------------------------------/
/---------------------------------------------------------*/
/*Module Registers*/
#define RCGCWD				((*(volatile uint32_t*)(0x400FE600)))
#define WDTLOAD(x)			((*(volatile uint32_t*)((0x40000000)+(x==0?0:0x1000))))
#define WDTCTL(x)			((*(volatile uint32_t*)((0x40000008)+(x==0?0:0x1000))))
#define WDTRIS(x)			((*(volatile uint32_t*)((0x40000010)+(x==0?0:0x1000))))
#define WDTTEST(x)			((*(volatile uint32_t*)((0x40000418)+(x==0?0:0x1000))))
/*Macros*/
#define WRC_IDX				(31)
#define INTTYPE_IDX			(2)
#define RESEN_IDX			(1)
#define INTEN_IDX			(0)
#define WDTRIS_IDX			(0)
#define STALL_IDX			(8)

/*----------------------------------------------------------/
/- STRUCTS AND UNIONS -------------------------------------/
/----------------------------------------------------------*/

/*---------------------------------------------------------/
/- GLOBAL STATIC VARIABLES -------------------------------/
/---------------------------------------------------------*/
static tpf_wdt_cb  	gpf_wdt_cb = NULL;
static uint32_t ga_timeout[INVALID_WDn] = {0,0};
extern uint32_t SystemCoreClock;
static volatile uint64_t timeout_ticks ;
/*---------------------------------------------------------/
/- LOCAL FUNCTIONS IMPLEMENTATION ------------------------/
/---------------------------------------------------------*/

void WDT0_Handler(void)
{
    static volatile uint8_t x;
    if(gpf_wdt_cb != NULL)
    {
        gpf_wdt_cb();
    }
}
void NMI_Handler (void)
{
    while(1);
}

static void set_wdt_timeout (wdt_index_t wdt_index, uint32_t timeout_ms)
{
	if (timeout_ms != 0 && (wdt_index < INVALID_WDn))
	{
        timeout_ticks = (uint64_t)(timeout_ms*(SystemCoreClock/1000));
		/*we need to convert time to ticks here*/
		//timeout_ticks = CONVERT_MS_TO_TICKS(timeout_ms);
		ga_timeout[wdt_index] = (uint32_t)timeout_ticks;
		WDTLOAD(wdt_index) = ga_timeout[wdt_index];
	}
	else
	{
		/*Invalid Inputs*/
	}
}
static void wait_for_wdt1(wdt_index_t wdt_ind)
{
	if(wdt_ind == WDT1)
	{
		while (!GET_BIT_STATUS(WDTCTL(WDT1),WRC_IDX));
	}
}


/*---------------------------------------------------------/
/- APIs IMPLEMENTATION -----------------------------------/
/---------------------------------------------------------*/
/*
 *  @brief 			This function initializes the wdt hal.
 *  @param[in]		pwdt_cfg pointer to input configuration structure.
 *  @return         ::SUCCESS in case of success, otherwise, review error code
 */
int32_t wdt_init(wdt_cfg_t* pwdt_cfg)
{
	int32_t result = ERROR;
	if(pwdt_cfg != NULL)
	{
		SET_BIT(RCGCWD,pwdt_cfg->wdt_index);
		set_wdt_timeout(pwdt_cfg->wdt_index,pwdt_cfg->timeout_ms);
		if(pwdt_cfg->wdt_index == WDT1)
		wait_for_wdt1(pwdt_cfg->wdt_index);
		if (pwdt_cfg->use_reset_mode)
		{
			SET_BIT(WDTCTL(pwdt_cfg->wdt_index),RESEN_IDX);
		}
		wait_for_wdt1(pwdt_cfg->wdt_index);
		if (pwdt_cfg->wdt_int == USE_NMI)
		{
			SET_BIT(WDTCTL(pwdt_cfg->wdt_index),INTTYPE_IDX);
			wait_for_wdt1(pwdt_cfg->wdt_index);
			SET_BIT(WDTCTL(pwdt_cfg->wdt_index),INTEN_IDX);
            wait_for_wdt1(pwdt_cfg->wdt_index);
            NVIC_EnableIRQ(WATCHDOG0_IRQn);
            __enable_irq();


		}
        else if (pwdt_cfg->wdt_int == USE_NORMAL_INT)
		{
			SET_BIT(WDTCTL(pwdt_cfg->wdt_index),INTEN_IDX);
            wait_for_wdt1(pwdt_cfg->wdt_index);
            NVIC_EnableIRQ(WATCHDOG0_IRQn);
            __enable_irq();

		}
		if (pwdt_cfg->use_test_mode)
		{
			SET_BIT(WDTTEST(pwdt_cfg->wdt_index),STALL_IDX);
			wait_for_wdt1(pwdt_cfg->wdt_index);
		}
        if(pwdt_cfg->pf_wdt_cb != NULL)
        {
            gpf_wdt_cb = pwdt_cfg->pf_wdt_cb;
        }

		result = SUCCESS;
	}
	else
	{
		result = INVALID_INPUT;
	}
	return result;
}
/*
 *  @brief 			This function resets the WDT to start from the max.
 *  @param[in]		wdtn: WDT index
 */
void wdt_reset(wdt_index_t wdtn)
{
	if(ga_timeout[wdtn] != 0)
	{
		WDTLOAD(wdtn) = ga_timeout[wdtn];
	}
}
/*
 *   @brief This function check the status of an interrupt.
 *   @param[in]	wdtn: WDT index to check its interrupt status
 *  @return ::TRUE in case of timeout occured, fasle, if timeout did not occur
 */
boolean wdt_get_int_status(wdt_index_t wdtn)
{
	boolean result = FALSE;
	if(GET_BIT_STATUS(WDTRIS(wdtn),WDTRIS_IDX))
	{
		result = TRUE;
	}
	return result;
}
/*
 *   @brief This function deinitializes the wdt hal.
 *   @param[in]	wdtn: WDT index to disable
 */
void wdt_deinit(wdt_index_t wdtn)
{
	/*Disable WDT clock to disable its functionality*/
	if(wdtn < INVALID_WDn)
	{
		CLR_BIT(RCGCWD,wdtn);
	}
	else
	{
		/*Invalid Index*/
	}
}
