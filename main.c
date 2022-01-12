#include "defs.h"


int main(int argc, char *argv[])
{
  int numRuns;
  StatsType *stats[NUM_SCENARIOS];
  if(argc < 2){
    numRuns = NUM_RUNS;
  } else {
    sscanf(argv[1], "%d", &numRuns);
  }
  srand( (unsigned)time( NULL ) );

  for(int i = 0; i < NUM_SCENARIOS; i++){
    initStats(&(stats[i]));
  }
  for(int i = 0; i < numRuns; i++){
    executeRun(stats);
  }
  printScenarioStats(stats);
  cleanOverall(stats);
  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 

  return (int)(r * max);
}

