/*
Assignment  :   Mini Project 2
Date        :   10/19/2021
Class       :   CMPS-4103
Students    :   Byron Dowling, Fowzy Alsaud, Elijah
Desciption  :

*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
#include <semaphore.h>

// (Pthread1 - 1) = 0 * 2000 = 0
// (Pthread1 * 2000 - 1) = 1999

// (Pthread2 - 1) = 1 * 2000 = 2000
// (Pthread2 * 2000 - 1) = 3999

// (Pthread3 - 1) = 2 * 2000 = 4000
// (Pthread3 * 2000 - 1) = 5999

// Declaring a global array hold 6000 integers
int array[6000];
// Declaring a global variable TOTAL
int total;

void *thread(void *arg)
{
    long id = (long)arg;

    for (int i = ((id - 1) * 2000); i < (id * 2000 - 1); i++)
    {
        total += array[i];
    }
}

int main(int argc, char *argv[])
{
    // Initialized with values 1 to 6000 in the main program (array[i]=i)
    for (int i = 1; i <= 15; i++)
    {
        array[i] = i;
    }

    /*
        Create 3 threads (identified by tid values 1 to 3).
        Each thread will add value to the array in range ((tid-1)*2000) to ((tid*2000-1))
        to a global variable TOTAL
    */
    pthread_t tid1, tid2, tid3; // thread id, creating a multi threads

    // // for(int i =1;i<=3;i++){
    // pthread_create(&tid1, NULL, thread, (void *)NULL);
    // // }
    pthread_create(&tid1, NULL, thread, (void *)1);
    pthread_create(&tid2, NULL, thread, (void *)2);
    pthread_create(&tid3, NULL, thread, (void *)3);
    /*
        Each one of them will add the (values of the array) with subscripts in the
        range (tid -1)*2000 to (tid*2000-1) to a global variable TOTAL, one value at a time (do not add them up
        in temporary variable before adding to the TOTAL, i.e.
    */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    printf("Total : %d", total);
    pthread_exit(NULL);
}
