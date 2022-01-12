#include "defs.h"

/*
  Function:  initDeque
  Purpose:   initialize a DequeType
       in:   memory location of new Deque
      out:   new allocated Deque location
*/
void initDeque(DequeType **d){
    *d = malloc(sizeof(DequeType));
    (*d)->head = NULL;
    (*d)->tail = NULL;
}

/*
  Function:  initStats
  Purpose:   initialize a StatsType
       in:   memory location of new stats
      out:   new allocated stats location
*/
void initStats(StatsType **s){
    *s = malloc(sizeof(StatsType));
    (*s)->numFailure = 0;
    (*s)->numPartSuccess = 0;
    (*s)->numSuccess = 0;
}

/*
  Function:  initFighter
  Purpose:   initialize a FighterType
       in:   memory location of new fighter, fighter stats
      out:   new allocated fighter location
*/
void initFighter(int strength, int armour, int health, FighterType **f){
    *f = malloc(sizeof(FighterType));
    (*f)->armour = armour;
    (*f)->health = health;
    (*f)->strength = strength;
}

/*
  Function:  initRunSpecs
  Purpose:   initialize a RunSpecsType
       in:   memory location of new RunSpecs, both heroes, a deque of pirates, and the memory location of the overall stats
      out:   new allocated RunSpecs location
*/
void initRunSpecs(FighterType *t, FighterType *h, DequeType *d, StatsType *s, RunSpecsType **r){
    *r = malloc(sizeof(RunSpecsType));
    (*r)->tort = t;
    (*r)->hare = h;
    (*r)->pirates = d;
    (*r)->stats = s;
}

/*
  Function:  initFightSpecs
  Purpose:   initialize a FightSpecsType
       in:   memory location of new FIghtSpecs, one hero, the deque of pirates, the direction of the hero, and a mutex to prevent
             two threads from accessing the same information at the same time
      out:   new allocated FightSpecs location
*/
void initFightSpecs(FighterType *a, DequeType *d, DirectionType dr, sem_t *s, FightSpecsType **f){
    *f = malloc(sizeof(FightSpecsType));
    (*f)->hero = a;
    (*f)->pirates = d;
    (*f)->dir = dr;
    (*f)->dqMutex = s;
}