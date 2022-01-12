#include "defs.h"

/*
  Function:  wait
  Purpose:   lock a thread until the mutex unlocks
       in:   pointer to the mutex
      out:   in case of a semaphore wait error, a detailed message describing the error
*/
void wait(sem_t *mutex){
    if(sem_wait(mutex) < 0){
        printf("semaphore wait error\n");
        exit(1);
    }
}

/*
  Function:  post
  Purpose:   unlock a thread using the mutex
       in:   pointer to the mutex
      out:   in case of a semaphore post error, a detailed message describing the error
*/
void post(sem_t *mutex){
    if (sem_post(mutex) < 0) {
      printf("semaphore post error\n");
      exit(1);
    }
}

/*
  Function:  updateStats
  Purpose:   update the overall simulation stats with new results
       in:   pointers to the heroes who fought
      out:   updated simulation stats
*/
void updateStats(FighterType *t, FighterType *h, StatsType *s){
    ResultType result;
    convertHeroStats(t, h, &result);
    switch (result)
    {
    case SUCCESS:
        s->numSuccess++;
        return;
    
    case PART_SUCCESS:
        s->numPartSuccess++;
        return;
    
    case FAILURE:
        s->numFailure++;
        return;

    default:
        break;
    }
}

/*
  Function:  convertHeroStats
  Purpose:   uses the heroes' health indicators to determine the result of the fight
       in:   pointers to both heroes, output pointer to store the resultType
      out:   resultType that depends on the result of the fight
*/
void convertHeroStats(FighterType *t, FighterType *h, ResultType* r){
    int deadHeroes = 0;
    if(t->health <= 0){
        deadHeroes++;
    }
    if(h->health <= 0){
        deadHeroes++;
    }
    switch (deadHeroes)
    {
    case 0:
        *r = SUCCESS;
        return;
    
    case 1:
        *r = PART_SUCCESS;
        return;

    case 2:
        *r = FAILURE;
        return;

    default:
        break;
    }
}

/*
  Function:  printScenarioStats
  Purpose:   print the cumulative stats of the whole simulation
       in:   stats at the end of the simulation
      out:   printed message showing the results of the whole simulation
*/
void printScenarioStats(StatsType* s[]){
    char scenarioNames[NUM_SCENARIOS][MAX_STR] = 
    {
        "Tortoise",
        "Hare",
        "None"
    };
    int numRuns = s[0]->numSuccess + s[0]->numPartSuccess + s[0]->numFailure;
    printf("\n+-----------------------------------------------------------+\n");
    printf("| Hero with sword |  %% success  |  %% partial  |  %% failure  |\n");
    printf("+-----------------------------------------------------------+\n");
    for(int i = 0; i < NUM_SCENARIOS; i++){
        printf("|   %-13s |    %3d      |    %3d      |    %3d      |\n", scenarioNames[i], 
        (int)round(100*((double)(s[i]->numSuccess)/numRuns)), 
        (int)round(100*((double)(s[i]->numPartSuccess)/numRuns)), 
        (int)round(100*((double)(s[i]->numFailure))/numRuns));
        printf("+-----------------------------------------------------------+\n");
    }
    printf("\nTotal Runs: %d\n", numRuns);
}

/*
  Function:  cleanRun
  Purpose:   frees the memory allocated to initialize a run
       in:   arrays of pointers to the heroes, run specs, and deques
*/
void cleanRun(FighterType *t[], FighterType *h[], RunSpecsType *r[], DequeType *d[]){
    for(int i = 0; i < NUM_SCENARIOS; i++){
        free(t[i]);
        free(h[i]);
        free(r[i]);
    }
    for(int i = 0; i< NUM_SCENARIOS; i++){
        free(d[i]);
    }
}

/*
  Function:  cleanScenario
  Purpose:   frees the memory allocated to initialize a scenario
       in:   arrays of pointers to the heroes, fight specs, and deques
*/
void cleanScenario(FightSpecsType *tort, FightSpecsType *hare, DequeType *d){
    NodeType *currNode;
    while(d->head != NULL){
        currNode = d->head;
        d->head = d->head->next;
        free(currNode->data);
        free(currNode);
    }
    free(tort);
    free(hare);
}

/*
  Function:  cleanOverall
  Purpose:   frees the memory allocated to initialize the stats
       in:   arrays of pointers to the overall stats
*/
void cleanOverall(StatsType *s[]){
    for(int i = 0; i < NUM_SCENARIOS; i++){
        free(s[i]);
    }
}