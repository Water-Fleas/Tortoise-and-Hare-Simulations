#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_RUNS 100
#define NUM_PIRATES 10
#define NUM_SCENARIOS 3

#define TORT_STRENGTH 5
#define TORT_ARMOUR 8
#define HARE_STRENGTH 8
#define HARE_ARMOUR 5
#define HERO_HEALTH 20
#define PIRATE_HEALTH 10
#define SWORD_STRENGTH 2

#define MINIMUM_DAMAGE 0
#define REGENERATED_HEALTH 3

#define MAX_STR 64

#define C_OK 0
#define C_NOK -1
typedef enum
{
  SUCCESS,
  FAILURE,
  PART_SUCCESS,
  RES_UNKNOWN
} ResultType;
typedef enum
{
  FRONT,
  BACK
} DirectionType;

typedef struct
{ // Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct
{ // One fighter:  Tortoise, Hare, or Pirate
  int strength;
  int armour;
  int health;
} FighterType;

typedef struct Node
{
  FighterType *data;
  struct Node *next;
} NodeType;

typedef struct
{ // Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct
{ // Specs for one scenario of one run
  DequeType *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType *stats;
} RunSpecsType;

typedef struct
{ // Specs for one fight of one scenario of one run
  FighterType *hero;
  DequeType *pirates;
  DirectionType dir;
  sem_t *dqMutex;
} FightSpecsType;

int randm(int); // Pseudo-random number generator function

void initFighter(int strength, int armour, int health, FighterType **f);
void pushTail(DequeType *d, FighterType *f);
int pollHead(DequeType *d, FighterType **dest);
int pollTail(DequeType *d, FighterType **dest);
void deepCopy(DequeType *d, DequeType *destDeque);
void initStats(StatsType **s);
void executeRun(StatsType *s[]);
void initDeque(DequeType **d);
void generateStrength(int *s);
void populateDeque(DequeType *d);
void generateArmour(int *a);
void initRunSpecs(FighterType *t, FighterType *h, DequeType *d, StatsType *s, RunSpecsType **r);
void *executeScenario(void *arg);
void cleanRun(FighterType *t[], FighterType *h[], RunSpecsType *r[], DequeType *d[]);
void initFightSpecs(FighterType *a, DequeType *d, DirectionType dr, sem_t *s, FightSpecsType **f);
void *executeFight(void *arg);
void wait(sem_t *mutex);
void post(sem_t *mutex);
int strike(FighterType *s, FighterType *r);
int fight(FighterType *h, FighterType *p);
void generateStrengthBuff(int s, int *b);
void updateStats(FighterType *t, FighterType *h, StatsType *s);
void convertHeroStats(FighterType *t, FighterType *h, ResultType* r);
void printScenarioStats(StatsType* s[]);
void cleanScenario(FightSpecsType *tort, FightSpecsType *hare, DequeType *d);
void cleanOverall(StatsType *s[]);

#endif
