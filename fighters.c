#include "defs.h"

/*
  Function:  generateStrength
  Purpose:   generates a random strength value for a pirate
       in:   pointer to where the strength value will be stored
      out:   random strength value
*/
void generateStrength(int *s)
{
    *s = randm(5) + 5;
}

/*
  Function:  populateDeque
  Purpose:   populate a deque with NUM_PIRATES amount of pirates
       in:   deque to be filled
*/
void populateDeque(DequeType *d)
{
    int strength;
    int armour;
    FighterType *pirate;
    for (int i = 0; i < NUM_PIRATES; i++)
    {
        generateArmour(&armour);
        generateStrength(&strength);
        initFighter(strength, armour, PIRATE_HEALTH, &pirate);
        pushTail(d, pirate);
    }
}

/*
  Function:  generateArmour
  Purpose:   generate a random armour value for a pirate
       in:   pointer to where the armour value will be stored
      out:   random armour value
*/
void generateArmour(int *a)
{
    *a = randm(4) + 1;
}

/*
  Function:  strike
  Purpose:   evaluate the effects of a fighter's strike against another
       in:   pointers to the fighting fighters
      out:   updated health indicators
   return:   C_NOK in case of a killing blow and C_OK otherwise
*/
int strike(FighterType *s, FighterType *r)
{
    if (s->strength > MAX_STR)
    {
        s->strength = MAX_STR;
    }
    int damage = s->strength - r->armour;
    if (damage < MINIMUM_DAMAGE)
    {
        damage = MINIMUM_DAMAGE;
    }
    r->health -= damage;
    if (r->health <= 0)
    {
        return C_NOK;
    }
    return C_OK;
}

/*
  Function:  fight
  Purpose:   evaluate the effects of a fight
       in:   pointers to the fighting fighters
      out:   fight result, updated health indicators
   return:   C_NOK in case of a pirate victory and C_OK in case of a hero victory
*/
int fight(FighterType *h, FighterType *p)
{
    int tempStrengthBuff;
    while (1)
    {
        if (strike(h, p) == C_NOK)
        {
            h->health += REGENERATED_HEALTH;
            if (h->health > HERO_HEALTH)
            {
                h->health = HERO_HEALTH;
            }
            free(p);
            return C_OK;
        }
        generateStrengthBuff(p->strength, &tempStrengthBuff);
        p->strength += tempStrengthBuff;
        if (strike(p, h) == C_NOK)
        {
            free(p);
            return C_NOK;
        }
        p->strength -= tempStrengthBuff;
    }
}

/*
  Function:  generateStrengthBuff
  Purpose:   generate a random temporary strength bonus for a pirate who loves to fight
       in:   strength value of the pirate and output pointer
      out:   random temporary strength bonus
*/
void generateStrengthBuff(int s, int *b)
{
    *b = randm(s - 1);
}