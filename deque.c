#include "defs.h"

/*
  Function:  pushTail
  Purpose:   adds a fighter to the tail of a deque
       in:   deque to add to, fighter to add
      out:   updated deque
*/
void pushTail(DequeType *d, FighterType *f){
    NodeType *newNode = malloc(sizeof(NodeType));
    newNode->next = NULL;
    newNode->data = f;
    if(d->tail){
        d->tail->next = newNode;
    }
    d->tail = newNode;
    if(d->head == NULL){
        d->head = newNode;
    }
}

/*
  Function:  pollHead
  Purpose:   removes a fighter from the head of the deque
       in:   destination of the fighter, deque to remove fighter from
      out:   updated deque, success flag
    Return:  C_OK if the fighter was successfully removed, C_NOK otherwise
*/
int pollHead(DequeType *d, FighterType **dest){
    if(d->head == NULL){
        return C_NOK;
    }
    *dest = d->head->data;
    NodeType *firstNode = d->head;
    if(d->head->next){
        d->head = d->head->next;
    }
    else{
        d->head = NULL;
        d->tail = NULL;
    }
    free(firstNode);
    return C_OK;
}

/*
  Function:  pollTail
  Purpose:   removes a fighter from the head of the deque
       in:   destination of the fighter, deque to remove fighter from
      out:   updated deque, success flag
    Return:  C_OK if the fighter was successfully removed, C_NOK otherwise
*/
int pollTail(DequeType *d, FighterType **dest){
    if(d->tail == NULL){
        return C_NOK;
    }
    *dest = d->tail->data;
    if(d->head == d->tail){
        d->head = NULL;
        free(d->tail);
        d->tail = NULL;
        return C_OK;
    }
    NodeType *currNode = d->head;
    while(currNode != NULL){
        if(currNode->next == d->tail){
            free(d->tail);
            currNode->next = NULL;
            d->tail = currNode;
        }
        currNode = currNode->next;
    }
    free(currNode);
    return C_OK;
}

/*
  Function:  deepCopy
  Purpose:   performs a deep copy of a deque onto another deque
       in:   deque to copy, deque to add to
      out:   updated deque
*/
void deepCopy(DequeType *d, DequeType *destDeque){
    NodeType *currNode = d->head;
    FighterType *tempFighter;
    while(currNode != NULL){
        initFighter(currNode->data->strength, currNode->data->armour, currNode->data->health, &tempFighter);
        pushTail(destDeque, tempFighter);
        currNode = currNode->next;
    }
    free(currNode);
    tempFighter = NULL;
    free(tempFighter);
}
