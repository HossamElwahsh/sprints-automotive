/**
 ** @file                   WDT_Tester.c
 ** @brief                  This file implements watchdog timer Module tester
 ** @author                 Karim Osama
 ** @date                   Jan 23, 2023
 ** @version                0.1
 */

/*- INCLUDES
----------------------------------------------*/
#include "wdt.h"

/*- LOCAL MACROS
------------------------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
static wdt_cfg_t wdt_cfg;
/*- GLOBAL EXTERN VARIABLES
-------------------------------*/

/*- LOCAL FUNCTIONS
-------------------------------*/
static void wdt_cb (void)
{
    while(1);
}
/*- APIs IMPLEMENTATION
-----------------------------------*/
int main(void)
{
	wdt_cfg.timeout_ms			= 1000;
	wdt_cfg.use_reset_mode	= 1;
	wdt_cfg.use_test_mode 	= 1;
	wdt_cfg.wdt_index 			= WDT0;
	wdt_cfg.wdt_int 				= USE_NORMAL_INT;
	wdt_cfg.pf_wdt_cb 			=	wdt_cb;
    
	wdt_init(&wdt_cfg);

	/* Superloop */
	while(1); // for testing
	while(1)
	{
		/* Other Modules Logic */
		wdt_reset(WDT0);
	}

}
