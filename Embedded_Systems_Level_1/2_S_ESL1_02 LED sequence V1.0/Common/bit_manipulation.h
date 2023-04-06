/*
 * bit_manipulation.h
 *
 * Created: 6/4/2023 1:12:17 AM
 *  Author: Hossam
 */ 


#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_

#define bitRead(byte, nbit) (((byte) >> (nbit)) & 0x01)
#define bitSet(byte, nbit) ((byte) |= (1UL << (nbit)))
#define bitClear(byte, nbit) ((byte) &= ~(1UL << (nbit)))
#define bitWrite(byte, nbit, bitValue) ((bitValue) ? bitSet(byte, nbit) : bitClear(byte, nbit))

#endif /* BIT_MANIPULATION_H_ */