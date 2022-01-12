#include "defs.h"

/*
  Function:  executeRun
  Purpose:   evaluate the effects of a single run of the simulation
       in:   overall simulation stats
      out:   updated simulation stats
*/
void executeRun(StatsType *s[])
{
    DequeType *deques[NUM_SCENARIOS];
    for(int i = 0; i < NUM_SCENARIOS; i++){
        initDeque(&deques[i]);
    }
    populateDeque(deques[0]);
    for(int i = 1; i < NUM_SCENARIOS; i++){
        deepCopy(deques[0], deques[i]);
    }

    FighterType *tortoises[NUM_SCENARIOS];
    for(int i = 0; i < NUM_SCENARIOS; i++){
        initFighter(TORT_STRENGTH, TORT_ARMOUR, HERO_HEALTH, tortoises+i);
    }

    FighterType *hares[NUM_SCENARIOS];
    for(int i = 0; i < NUM_SCENARIOS; i++){
        initFighter(HARE_STRENGTH, HARE_ARMOUR, HERO_HEALTH, hares+i);
    }
    if(tortoises[0]){
        tortoises[0]->strength+=SWORD_STRENGTH;
    }
    if(hares[1]){
        hares[1]->strength+=SWORD_STRENGTH;
    }

    RunSpecsType *scenarioSpecs[NUM_SCENARIOS];
    for(int i = 0; i < NUM_SCENARIOS; i++){
        initRunSpecs(tortoises[i], hares[i], deques[i], s[i], scenarioSpecs+i);
    }

    pthread_t scenarios[NUM_SCENARIOS];
    for(int i = 0; i < NUM_SCENARIOS; i++){
        pthread_create(&scenarios[i], NULL, executeScenario, scenarioSpecs[i]);
    }
    for(int i = 0; i < NUM_SCENARIOS; i++){
        pthread_join(scenarios[i], NULL);
    }
    cleanRun(tortoises, hares, scenarioSpecs, deques);
}

/*
  Function:  executeScenario
  Purpose:   simulate a given scenario
       in:   specs of a given scenario
      out:   updated simulation stats
   return:   0
*/
void *executeScenario(void *arg){
    sem_t mutex;
    RunSpecsType specs = *((RunSpecsType *) arg);
    if (sem_init(&mutex, 0, 1) < 0) {
        printf("semaphore initialization error\n");
        exit(1);
    }
    FightSpecsType *tortoiseFight;
    initFightSpecs((&specs)->tort, (&specs)->pirates, FRONT, &mutex, &tortoiseFight);
    FightSpecsType *hareFight;
    initFightSpecs((&specs)->hare, (&specs)->pirates, BACK, &mutex, &hareFight);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, executeFight, tortoiseFight);
    pthread_create(&t2, NULL, executeFight, hareFight);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    updateStats(specs.tort, specs.hare, specs.stats);
    cleanScenario(tortoiseFight, hareFight, specs.pirates);
    return 0;
}

/*
  Function:  executeFight
  Purpose:   evaluate the results of the heroes' fight against the pirates in one scenario
       in:   fight specs
      out:   updated health indicators, updated pirate deque
   return:   0
*/
void *executeFight(void *arg){
    FightSpecsType specs = *((FightSpecsType *) arg);
    FighterType *enemy;
    while(1){
        wait(specs.dqMutex);
        if(specs.dir == FRONT){
            if(pollHead(specs.pirates, &enemy) == C_NOK){
                post(specs.dqMutex);
                break;
            }
            post(specs.dqMutex);
            if(fight(specs.hero, enemy) == C_NOK){
                break;
            }
            usleep(1000);
        }
        else{
            if(pollTail(specs.pirates, &enemy) == C_NOK){
                post(specs.dqMutex);
                break;
            }
            post(specs.dqMutex);
            if(fight(specs.hero, enemy) == C_NOK){
                break;
            }
            usleep(1000);
        }
    }
    return 0;
}

