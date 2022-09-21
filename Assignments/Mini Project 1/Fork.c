/*
    Name:       Byron Dowling
    Course:     5143 Advanced Operating Systems
    Date:       9/16/2022

    Assignment: Posix Fork

        Original Assignment Instructions:

        Write a C program that will read in two values and then fork two additional processes
        so that the arithmetic operations will run in parallel.

        Run in Cygiwin using GCC
*/

#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char* argv[])
{
    // Variables to hold our two values
	unsigned int A = 0;
    unsigned int B = 0;

    // File pointer to read in the numbers from input
	FILE *fileptr;

	fileptr = fopen("input.txt","r");
	
    // Read the A and B values from the input file
	fscanf(fileptr, "%d", &A);
    fscanf(fileptr, "%d", &B);

    // First fork/Parent process that will handle multiplication
    if (fork() == 0)
    {
        printf("Multiply, %d * %d, = %d\n", A, B, A*B);
    }

    else
    {

        // Child fork to handle the additional two arithmetic processes
        if (fork() == 0)
        {
            printf("Add, %d + %d, = %d\n", A, B, A+B);
        }

        else
        {
            printf("Sub, %d - %d, = %d\n", A, B, A-B);
        }
    }
	
    // Close the file buffer
	fclose(fileptr);
	return 0;
}
