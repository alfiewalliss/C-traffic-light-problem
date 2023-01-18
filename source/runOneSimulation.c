#include<runOneSimulation.h>

/* RUNONESIMULATION AS DEFINED IN THE SPEC */
RESULT runOneSimulation(int l_light, int r_light, float l_car, float r_car, gsl_rng *r)
{
    /* RETURN VALUES */
    int l_passed = 0; /* number of veicles that pass through on the left */
    int l_total = 0; /* the total time all cars have waited for to calculate the average on the left */
    float l_average = 0; /* the average time all cars have waited on the left */
    int l_max_time = 0; /* the maximum of iterations a car has to wait on the left */
    int l_clear = 0; /* the number of iterations to clear the queue after the cars stop arriving on the left */
    int r_passed = 0; /* number of veicles that pass through on the right */
    int r_total = 0; /* the total time all cars have waited for to calculate the average on the right */
    float r_average = 0; /* the average time all cars have waited on the right */
    int r_max_time = 0; /* the maximum of iterations a car has to wait on the right */
    int r_clear = 0; /* the number of iterations to clear the queue after the cars stop arriving on the right */
    RESULT results;

    /*SIMULATION BEGIN*/
    QUEUE *left = NULL;
    QUEUE *right = NULL;
    int i = 0;
    char currentSide;  /* 'l' for left and 'r' for right */
    int finish = 1;
    int counter = 0;
    int limit = 0;
    int limitCounter = 0;
    int current_max;
    float random1 = gsl_rng_uniform (r);
    if (random1 < 0.5)
    {
        currentSide = 'l';
        limitCounter = l_light;
    }
    else
    {
        currentSide = 'r';
        limitCounter = r_light;
    }
    while (finish != 0)
    {
        if (counter < 500) /* for the first 500 iterations whilst cars can queue */
        {
            if (limit < limitCounter)
            {
                random1 = (float)gsl_rng_uniform (r);
                if(random1 < l_car)
                {
                    enQueue(&left, 0);
                    l_passed++;
                }
                random1 = (float)gsl_rng_uniform (r);
                if(random1 < r_car)
                {
                    enQueue(&right, 0);
                    r_passed++;
                }
                if(currentSide == 'r')
                {
                   current_max = deQueue(&right);
                   r_total = r_total + current_max;
                   if (current_max > r_max_time)
                   {
                       r_max_time = current_max;
                   }
                }
                if(currentSide == 'l')
                {
                    current_max = deQueue(&left);
                    l_total = l_total+current_max;
                    if (current_max > l_max_time)
                    {
                        l_max_time = current_max;
                    }
                }
            }
        }
        else  /* for the remaining iterations whilst cars can't queue */
        {
            if(limit < limitCounter)
            {
                if(currentSide == 'r')
                {
                    current_max = deQueue(&right);
                    r_total = r_total + current_max;
                    if (current_max > r_max_time)
                    {
                        r_max_time = current_max;
                    }
                }
                if(currentSide == 'l')
                {
                    current_max = deQueue(&left);
                    l_total = l_total + current_max;
                    if (current_max > l_max_time)
                    {
                        l_max_time = current_max;
                    }
                }
            }
            if ((isEmpty(&left) == 1) && (isEmpty(&right) == 1))
            {
                finish = 0;
            }
            if(isEmpty(&left) == 0)
            {
                l_clear++;
            }
            if(isEmpty(&right) == 0)
            {
                r_clear++;
            }
        }
        limit++;
        counter++;
        /* CHANGE LIGHTS IF NEEDED */
        if(currentSide == 'r' && limit == limitCounter)
        {
            currentSide = 'l';
            counter++;
            limit = 0;
            limitCounter = l_light;
            addOne(left);
            addOne(right);
            if (counter > 500)
            {
                if(isEmpty(&left) == 0)
                {
                    l_clear++;
                }
                if(isEmpty(&right) == 0)
                {
                     r_clear++;
                }
            }
        }
        if (currentSide == 'l' && limit == limitCounter)
        {
            currentSide = 'r';
            counter++;
            limit = 0;
            limitCounter = r_light;
            addOne(left);
            addOne(right);
            if (counter > 500)
            {
                if(isEmpty(&left) == 0)
                {
                    l_clear++;
                }
                if(isEmpty(&right) == 0)
                {
                     r_clear++;
                }
            }
         }
         /* Add one iteration to all wait times */
         addOne(left);
         addOne(right);
    }

    /* RESULT FORMATTING */
    r_average = (float) r_total / r_passed;
    l_average = (float) l_total / l_passed;
    /*printf("FOR RIGHT: \nPASSED THROUGH: %d \n AVERAGE WAITING TIME: %f \nMAXIMUM WAITING TIME: %d \nTIME TAKEN TO CLEAR %d\n\n", r_passed, r_average, r_max_time, r_clear);
 *     printf("FOR LEFT: \nPASSED THROUGH: %d \nAVERAGE WAITING TIME: %f \nMAXIMUM WAITING TIME: %d \nTIME TAKEN TO CLEAR %d\n\n", l_passed, l_average, l_max_time, l_clear);*/
    results.l_passed = l_passed;
    results.l_average = l_average;
    results.l_max_time = l_max_time;
    results.l_clear = l_clear;
    results.r_passed = r_passed;
    results.r_average = r_average;
    results.r_max_time = r_max_time;
    results.r_clear = r_clear;

    return results;
}
