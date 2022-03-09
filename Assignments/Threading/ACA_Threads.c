/*
	Name: Byron Dowling
	Class: 5133 Advanced Computer Architecture
	Date: 11/3/2021
	Assignment: Homework #5 Pthreads Programming
	
	Details:
	- Perform the Addition of A + B
	- Perform the Difference of A - B
	- Perform the Product of A * B
	- Perform the Quotient of A / B

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * 
 * Defined globally accessible variables:
 * 
 *  - Number of THREADS = 4 
 *  - Size of the Array = 1 000 000
 *  - Mutex
 *  - 2 Arrays: Array A & B of size = 1 000 000
 *  - Addition Summation set it to zero
 *  - Substraction Summation set it to zero
 *  - Multiplication Summation set it to zero
 *  - Division Summation set it to zero
 *  
 */

#define NUM_THREADS 4               // Predefining our 4 threads
#define ARR_SIZE 1000000            // Global Array Size Varible
pthread_mutex_t mutexsum;

int Arr_A[ARR_SIZE];                // Array A
int Arr_B[ARR_SIZE];                // Array B


// Running Total Variables
double Add_Sum = 0;
double Sub_Sum = 0;
double Mul_Sum = 0;
double Div_Sum = 0;

/**
 *  Implemeting all the operation in this function.
 *  - Initialize an Unsigned long long variable call t_id (thread ID).
 *  - Then use a for loop to do our operations.
 *  - Lock a mutex prior to updating the value in the shared structure.
 *  - Then unlock it upon updating.
 * 
 * @param t 
 * @return void* 
 */
void *Operation(void *t)
{
    size_t t_id = (size_t)t; // Unsigned long long

    /*
        Lock a mutex prior to updating the value in the shared structure.


        In the for loop below, we utilize the thread id to divide the size
        of the arrays into equal sections. By doing this, when the threads
        run in parallel, they are not accessing the same index of the array
        but rather "working on their section" of the array.

        Ex: Thread ID #1 passed in
            i = 0 (Thread ID int value) * Array Size / 4 = 0
            i < (thread ID 0 + 1) = 1 * (1,000,000 / # of Threads 4) = i < 1 * 250,000
            i++

            Therefore this example will loop from 0 to 250,000 indexes in the array

    */
    pthread_mutex_lock(&mutexsum);

    for (int i = (t_id * ARR_SIZE) / 4; i < (t_id + 1) * ARR_SIZE / NUM_THREADS; i++)
    {
        Add_Sum += Arr_A[i] + Arr_B[i];

        Sub_Sum += Arr_A[i] - Arr_B[i];

        Mul_Sum += Arr_A[i] * Arr_B[i];

        Div_Sum += (double)Arr_A[i] / (double)Arr_B[i];
    }

    /* 
        Then unlock it upon updating. 
    */
    pthread_mutex_unlock(&mutexsum);

    pthread_exit((void *)0);
}

/**
 * 
 * The main program creates threads which do all the work and then print out result upon completion. 
 * Before creating the threads,The input data is created. 
 * Since all threads update a shared structure, we need a mutex for mutual exclusion. 
 * The main thread needs to wait for all threads to complete, it waits for each one of the threads. 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    pthread_t thread_ids[NUM_THREADS];

    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);


    /**
     * 
     * Initialize Array A to all 1.
     * Initialize Array B to all 2.
     * 
     */
    for (int i = 0; i < ARR_SIZE; i++)
    {
        Arr_A[i] = 1;
        Arr_B[i] = 2;
    }

    /*
        Creating four threads, each evaluating its own Operation.
	*/
    for (t = 0; t < NUM_THREADS; ++t) 
    {
        rc = pthread_create(&thread_ids[t], &attr, Operation, (void *)t);

        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);

    /**
     * Joining and waiting for all threads to complete
     * 
     */
    for (size_t i = 0; i < NUM_THREADS; i++) 
    {
        rc = pthread_join(thread_ids[i], NULL);
        if (rc)
        {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    // /**
    //  * 
    //  * Debugging Purposes.
    //  * 
    //  */
    // printf("\n --- Matrix ---\n\n");
    // printf("\n -- A    B ---\n\n");

    // for (int x = 0; x < ARR_SIZE; x++)
    // {
    //     printf("%5d", Arr_A[x]);
    //     printf("%5d", Arr_B[x]);
    //     printf("\n\n");
    // }

    /**
     *
     * Displaying the result matrix
     * 
     */
    printf("\nAddition summation is:       %f\n", Add_Sum);
    printf("Susbtraction  summation is: %f\n", Sub_Sum);
    printf("Multipliaction summation is: %f\n", Mul_Sum);
    printf("Division summation is:       %f\n", Div_Sum);

    /**
     * 
     * After joining, print out the results and NOW we cleanup 
     * 
     */
    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);
}
