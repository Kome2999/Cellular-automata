#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "header.h"

//kome

// "Child" Thread Function

void *basicThread(void *param)
{

  // use this to get thread number from parameter

    long thread = (long)param;
    printf("in a thread %ld \n", thread);


//initialises row to 0 and column to 0
    int row = 0;
    int col = 0;


//segment each thread divide work amongsts threads
    int segment_each_thread = ROWS / NUMTHREADS;
    //each thread starts at specific point 
    int start = thread * segment_each_thread;
    //each thread ends at specific points also makes sure thread is on last  thread
    int end = (thread + 1) * segment_each_thread;
    //make sure its an actual thread
    end = end - 1;

    printf("-------------\n");
    printf("start %i \n", start);
    printf("end %i \n", end);
    printf("-------------\n");

    for (int day = 1; day <= TOTAL_DAYS; day++)
    { // main day loop
        printf("looping new day %d...\n", day);

        // setting start and end positions in array
        for (row = start; row <= end; row++)
        {
            for (col = 0; col < COLS; col++)
            {
                // what is the current cell
                switch (current[row][col].state)
                {
                case 'F':
                    int num_Burning_Neighbours = countBurningNeighbours_ClosedBoundaries(row, col);
                    decide_F_to_B(row, col, num_Burning_Neighbours);
                    break;

                case 'B':
                    decide_B_to_X_VaryingDays(row, col);
                    break;
                }
            } // for
        }     // for

        int i = 0;
        int j = 0;

        //lock critical section only one thread can go in at a time and then wait for the others
        pthread_mutex_lock(&mutex);

        // Overwrite the current world with the future world
        printf("saving future to current..\n");
        for (i = start; i <= end; i++)
        {
            for (j = 0; j < COLS; j++)
            {
                current[i][j] = future[i][j];
            }
        }
//unlock critical section once threads have executed
        pthread_mutex_unlock(&mutex);

        // Print the state of the world after each day
        if (thread == 0)
        {
            printf("World state after day %d:\n", day);
            for (i = 0; i < ROWS; i++)
            {
                for (j = 0; j < COLS; j++)
                {
                    printf(" %c ", current[i][j].state);
                }
                printf("\n");
            }
        }

    } // for

    return 0;
}
