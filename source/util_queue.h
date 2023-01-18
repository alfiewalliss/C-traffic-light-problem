#ifndef __UTIL_QUEUE_H
#define __UTIL_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
/*----- structure definition -------------------------------------------------*/
struct queueStruct
{
    int                  wait;
    struct queueStruct   *next;
};
typedef struct queueStruct QUEUE;

/*----- function prototypes --------------------------------------------------*/
QUEUE *newNode    (int data);
void   enQueue    (QUEUE **, int);
int   deQueue    (QUEUE **);
int    isEmpty    (QUEUE **);
void addOne(QUEUE *);

#endif
