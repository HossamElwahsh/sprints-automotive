/*
 * bit_manipulation.h
 *
 * Created: 23/5/2023 7:34:29 AM
*  Author: hossam Elwahsh - https://github.com/HossamElwahsh
 */


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

#define SET_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER | ( 1UL << BIT_NUMBER ) )
#define CLR_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER & ~( 1UL << BIT_NUMBER ) )
#define TOGGLE_BIT( REGISTER, BIT_NUMBER )		REGISTER = ( REGISTER ^ ( 1UL << BIT_NUMBER ) )
#define GET_BIT( REGISTER, BIT_NUMBER )		( ( REGISTER & ( 1UL << BIT_NUMBER ) ) >> BIT_NUMBER ) // ( ( REGISTER >> BIT_NUMBER ) & 1 )

#define WRITE_BIT(REGISTER,BIT_NUMBER, BIT_VAL) ((BIT_VAL) ? ((REGISTER) |= (1UL << (BIT_NUMBER))) : ((REGISTER) &= ~(1UL << (BIT_NUMBER))))

#endif /* BIT_MANIPULATION_H_ */