#include<util_queue.h>

/* create a new node from the given data and return a pointer to it */
QUEUE *newNode (int data)
{
    QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE));
    if ( q==NULL )
    {
        printf("Memory allocation error\n");
        exit(-1);
    }
    q->wait = data;
    q->next = NULL;
    return q;
}

/* add a value to the end of the queue  */
void enQueue (QUEUE **queue, int data)
{
    QUEUE *q = *queue;
    if(q==NULL){
        QUEUE *new = newNode(data);
        *queue = new;
        return;
    }
    while(q->next != NULL)
    {
        q=q->next;
    }
    QUEUE *new = newNode(data);
    q->next = new;
    return;
}

/* remove a value from the start of the queue and return the value */
int deQueue (QUEUE **queue)
{
    QUEUE   *q    = *queue;
    int     data = (-1);

    if ( q==NULL )
    {
        return data;
    }

    data = q->wait;
    *queue = q->next;
    free(q);
    return data;
}

/* check if the queue is empty and if so return 1 else return 0 */
int isEmpty (QUEUE **queue)
{
    QUEUE *q = *queue;
    if (q == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* add one to each time of the element in the car */
void addOne(QUEUE *queue)
{
    if(queue==NULL)
    {
        return;
    }
    else
    {
        queue->wait++;
        addOne(queue->next);
    }
    return;
}

