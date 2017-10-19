/********************
File: lab4-pthreads-sample.cpp
Course: CSCI-375 (Operating System)

Lab: 4
Purpose: Calculate the average of 1st N numbers using multi-threaded program

Author Name: Brett Harvey
Student ID: 201504204

To Compile: g++ lab4-pthreads-sample.cpp -lpthread -o <output-file-name>
To Run: ./<output-file-name> <total_thread_number>
Example:
To Compile: g++ lab4-pthreads-sample.cpp -lpthread -o lab4.out
To Run: ./lab4.out 5
        ./lab4.out 10
        ./lab4.out 20
************************/

#include <pthread.h>    /* For thread */
#include <stdio.h>      /* For printf() function */
#include <sys/time.h>   /* For calculating time */
#include <stdlib.h>     /* For using atoi(), atol() funtion */

#define ARRAYSIZE   10000000     /* Define the total numbers: N */

int NTHREADS;       /* Global variable to store total number of threads */
int ITERATIONS;     /* Global variable to store number of iteration for each thread */

double sum = 0.0, a[ARRAYSIZE]; /* Declare global sum and a[], so that these values can be accessible from any thread */
pthread_mutex_t mutex;          /* Declare mutex normal variable - not pointer (*) variable */

void *do_sum(void *tid);        /* Function prototype - do_sum */

/*------------------------
Function: main(int    , char *)
Purpose: Program starts from here, the MAIN
    Parameters (optional):
        argc = total number (int) of arguments while running
        argv[] = arguments passed while running
Returns: 0 (Zero)
--------------------------*/
int main(int argc, char *argv[]) {
    NTHREADS = atoi(argv[1]);   /* converting thread # to int which is dynamically taken from the run */
    ITERATIONS = ARRAYSIZE / NTHREADS;  /* number of iteration for each thread */

    int i;                  /* for loop counter */
    int tids[NTHREADS];     /* thread ids array */
    double avg = 0.0;       /* To store average value */
    pthread_t threads[NTHREADS];    /* Declare thread object array */
    pthread_attr_t attr;    /* Declare thread arribute */

    /* Clock variable to calculate time */
    clock_t st_clk, end_clk, diff_clk;

    printf("Total Threads: %d\n", NTHREADS);

    /* Pthreads setup: initialize mutex and explicitly create threads in a
        joinable state (for portability). Pass each thread to its loop offset */

    /* Initializes mutex with the default value */
    pthread_mutex_init(&mutex, NULL);
    /* Initializes a thread attributes object attr with the default value */
    pthread_attr_init(&attr);
    /* Set the detachstate attribute "PTHREAD_CREATE_JOINABLE" in the attr object
        i.e. all threads created with this attr will be joinable state */
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    st_clk = clock();   /* Store start time */

    /* Create Threads */
    for (i=0; i<NTHREADS; i++) {
        tids[i] = i;    /* Store thread id in tids[] array*/
        /* Create threads for 'do_sum' function passing 'tids' values with 'attr' attribute */
        // do_sum();
    }

    /* Wait for all threads to complete then print global sum */
    printf("Global Sum: %d",sum);

    for (i=0; i<NTHREADS; i++) {
        /* Join all threads */
        pthread_join(tids[i], 0);
    }

    end_clk = clock();                  /* Store end time */
    diff_clk = end_clk - st_clk;        /* Calculate the time */

    /* print total time needed to complete all threads */
    printf ("TIME (mS) = %lf \n", 1000*(double(diff_clk)/CLOCKS_PER_SEC));

    avg = sum / ARRAYSIZE;              /* Calculate average value */
    printf("Average = %.2lf\n", avg);   /* Print average value */

    /* Clean up threads and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
    pthread_exit (NULL);
    return 0;
}

/*-----------------------
Function: do_sum()
Purpose: Calculate the summation of numbers in the given range
Parameters:
    void *tid: void type pointer variable which takes here integer thread id
Returns: nothing
------------------------*/
void *do_sum(void *tid) {
    /* declaring and intializing variables */
    int i;      /* for-loop counter */
    int start;  /* starting array index */
    int end;    /* ending array index */
    int *mytid; /* thread id */
    double mysum = 0.0;   /* mysum = for storing local sum */

    /* Initialize local part of the global array and keep local sum */
    int myLocalArray[ARRAYSIZE];

    mytid = (int *) tid; /* Convert void pointer to integer pointer (because thread id is integer),
                            it will be needed to calculate the starting index */

    start = (*mytid * ITERATIONS);  /* calculating start index */
    end = start + ITERATIONS;       /* calculating end index   */

    printf ("Thread %d doing iterations %d to %d\n", *mytid, start, end-1); /* Printing thread id and other info */
    /* Calculate the summation */
    for (i = start; i <= end; i++) {
        mysum += i;
        pthread_mutex_lock(&mutex);
        sum += mysum; // Adding local sum to global sum
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);     /* Exit mutex */
}

