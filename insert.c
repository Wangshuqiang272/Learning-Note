/* Insert_sort Function 
 * 
 * A function that sort the order which array passed into the Function 	
 */
#include "stdio.h"
typedef unsigned char uint8;
void transposition(uint8* A,uint8* B)
{
	uint8 temp = 0;
	temp = *B;
	*B = *A;
	*A = temp;
}

int insert_sort(uint8* data,int num)
{
	uint8 i,j;
	printf("num is %d\n",num);
	for(i = 0;i < num; i++)
	{
		if((data[i] < 0)||(data[i] > 9))
		{
			printf("parmater Error %d \n",data[i]);
			return -1;
		}	
		for(j = i;j >= 0;j--)
		{
			if(data[j] < data[j-1])
				transposition(&data[j],&data[j - 1]);
				//transposition(data + j,data + j - 1);
			else
				break;
		}
	}
	for(i = 0;i < num;i++)
		printf("%d\t",data[i]);
	return 0;
}
int main()
{
	uint8 data[] = {6,2,3,9,8,1,4,7,5};
	return insert_sort(data,sizeof(data));
}
