#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"
#include "vars_defs_functions.h"
//kome
//Global Variables

//The quantity of F, B, O, X cz
unsigned long int numF; //unsigned means positive number
unsigned long int numB;
unsigned long int numO;
unsigned long int numX;




int main(){
  

  
  double start, finish, elapsed;

  GET_TIME(start);




  // Initial values for #F, #B, #O, #X have to be zero
  numF = 0;
  numB = 0;
  numO = 0;
  numX = 0;
  
  


  CELL current[ROWS][COLS]; // 2-Dim array for current world
  CELL future[ROWS][COLS]; // 2-Dim array for future world
  







  int day = 0; //Current day
  int i, j;
  int row, col;
  int num_Burning_Neighbours;








  // Generate random seed
  srand((unsigned int)time(NULL));

  // Create the initial world and give each cell a state
  initialiseWorld(current, future);


  // Output the day, #F, #B, #O, #X to file
  //outputDayFBOX(fp_DayFBOX, day);

  // Output the day and the 2-dim array of the current world
  //outputWorld(day, current);
  


  #if DEBUG_LEVEL > 0
    //printf("numF = %ld, numB = %ld\n\n", numF, numB);
  #endif

 



 printf("total days to loop..%d", TOTAL_DAYS);



for(day=1; day <= TOTAL_DAYS; day++){ // main day loop

        printf("loop a new day\n");


        

  for(row=0; row<ROWS; row++){
          for(col=0; col<COLS; col++){
                          // what is the current cell
                          switch(current[row][col].state){
                            
                          case 'F':
                            //num_Burning_Neighbours = countBurningNeighbours(row, col, current);
                            num_Burning_Neighbours = countBurningNeighbours_ClosedBoundaries(row, col, current);
                            
                            decide_F_to_B(row, col, num_Burning_Neighbours, future);
                            break;

                            
                            case 'B':
                                  
                            
                          
                            decide_B_to_X_VaryingDays(row, col, current, future);

                            break;
	  
	                        }//switch
                        
          } //for
  } //for









          
            //Overwrite the current world with the future world
            for(i=0; i<ROWS; i++){
              for(j=0; j<COLS; j++) {
                current[i][j] = future[i][j];
              }
            }




            //
            // Main loop for printing out the current state data for
            // the current daty.
            for(i=0; i<ROWS; i++){ 
                  for(j=0; j<COLS; j++){

                      printf("%c ", current[i][j].state);
                  }//for

            
                 printf("\n"); // breaking onto the next line
        
            


           }// for




  }// day loop
  
 

 




  
  GET_TIME(finish);
  elapsed = finish - start;
  printf("Elapsed time = %lf\n\n", elapsed);

  return 0;
}
