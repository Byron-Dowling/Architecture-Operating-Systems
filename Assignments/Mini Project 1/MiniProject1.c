// Mini Project #1
// Byron Dowling

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	unsigned int input_num = 0;
	FILE *fileptr;
	
	fileptr = fopen("input.txt","r");
	
	fscanf(fileptr, "%d", &input_num);
	
	
	for (int i = 0; i < input_num; i++)
	{
		if (i < (input_num / 3))
		{
			int first = fork();
      printf("\nFirst Child\n");
			printf("%d", i+1);
      // printf("\n");
		}
		
		else if ((i < ( 2 * input_num) / 3 ) && i > (input_num / 3))
		{
			int second = fork();
      printf("\nSecond Child\n");
			printf("%d", i+1);
      // printf("\n");
		}
		
		else
		{
      printf("\nParent\n");
			printf("%d", i+1);
      // printf("\n");
		}
		
	}
	
	fclose(fileptr);
	return 0;
}
