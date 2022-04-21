#include "stdio.h"
typedef unsigned char uint8;
typedef union 
{
	uint8 byte;
	struct
	{
		uint8 bit0 :1;
		uint8 bit1 :1;
		uint8 bit2 :1;
		uint8 bit3 :1;
		uint8 bit4 :1;
		uint8 bit5 :1;
		uint8 bit6 :1;
		uint8 bit7 :1;
	}Bits;
} BitType;

int main()
{
	int i;
	BitType data_bit;
	data_bit.byte = 27;
	printf("%d\t",data_bit.Bits.bit0);
	printf("%d\t",data_bit.Bits.bit1);
	printf("%d\t",data_bit.Bits.bit2);
	printf("%d\t",data_bit.Bits.bit3);
	printf("%d\t",data_bit.Bits.bit4);
	printf("%d\t",data_bit.Bits.bit5);
	printf("%d\t",data_bit.Bits.bit6);
	printf("%d\t",data_bit.Bits.bit7);
	return 0;
}

