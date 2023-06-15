/**
 ** @file                   common.h
 ** @brief                  This is header file for common typedefs and macros
 ** @author                 Hossam Elwahsh
 ** @date                   Jun 15, 2023
 ** @version                0.1
 */

#ifndef COMMON_H_
#define COMMON_H_

/*- TYPEDEFS
-------------------------------*/

typedef unsigned char boolean;

/*- MACROS
-------------------------------*/

#ifndef TRUE
	#define TRUE		(1U)
#endif

#ifndef FALSE
	#define FALSE		(0U)
#endif


#define SUCCESS	(0)

#define NULL		((void *) 0)
#define ERROR 	(-1)
#define INVALID_INPUT 	(-2)

/*- BIT OPERATIONS
-------------------------------*/

#define SET_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER | ( 1UL << BIT_NUMBER ) )
#define CLR_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER & ~( 1UL << BIT_NUMBER ) )
#define TOG_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER ^ ( 1UL << BIT_NUMBER ) )
#define GET_BIT_STATUS( REGISTER, BIT_NUMBER )		( ( REGISTER & ( 1UL << BIT_NUMBER ) ) >> BIT_NUMBER ) // ( ( REGISTER >> BIT_NUMBER ) & 1 )

#define WRITE_BIT(REGISTER,BIT_NUMBER, BIT_VAL) ((BIT_VAL) ? ((REGISTER) |= (1UL << (BIT_NUMBER))) : ((REGISTER) &= ~(1UL << (BIT_NUMBER))))

#endif
