#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"
//kome
void initialiseWorld(CELL current[ROWS][COLS],
		     CELL future[ROWS][COLS]){

  int i, j, randRow, randCol;

  // looping over the rows and colums
  for(i=0; i<ROWS; i++){
      // printf("looping rows\n");
    for(j=0; j<COLS; j++){
        //  printf("looping col\n");
      current[i][j].state = 'F';

      //Each cell has a "Burn time" set to a random number of days between MIN_DAYS_B_TO_X and MAX_DAYS_B_TO_X:
      current[i][j].counter_B_to_X = rand()%(MAX_DAYS_B_TO_X - MIN_DAYS_B_TO_X + 1) + MIN_DAYS_B_TO_X;

      future[i][j] = current[i][j]; //Future and current worlds should be identical at the start
      
      numF++; // Recall that numF is a global variable, initialised to zero in main()
    }
  }

  randRow = rand()%ROWS;
  randCol = rand()%COLS;

  current[randRow][randCol].state = 'B';
  future[randRow][randCol] = current[randRow][randCol];
  numF--;
  numB++;


}
