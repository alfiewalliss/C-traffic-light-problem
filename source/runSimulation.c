#include <runSimulation.h>
#include <runOneSimulation.h>

/* RUNSIMULATION FUNCTION AS DEFINED IN THE SPEC */
int main()
{

    /* Initialise random numbers */
    const gsl_rng_type * T;
    gsl_rng * r;
    gsl_rng_env_setup();
    T = gsl_rng_default;
    r = gsl_rng_alloc (T);
    gsl_rng_set(r,time(0));

    system("clear");

   /* Variable initialisation for inputs */
    int l_light;
    int r_light;
    float l_car;
    float r_car;

    /* Input validation for left period */
    int count;
    int temp;
    printf("Enter the traffic light period for the left:\n");
    count = scanf("%d", &l_light);
    if(l_light < 0)
    {
        count = 0;
    }
    while (count != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        {
            printf("ERROR! INCORRECT FORMAT! PLEASE TRY AGAIN:\n");
        }
        count = scanf("%d", &l_light);
        if(l_light < 0)
        {
            count = 0;
        }
    }

    /* Input validation for right period */
    printf("Enter the traffic light period for the right:\n");
    count = scanf("%d", &r_light);
    if(r_light < 0)
    {
        count = 0;
    }
    while (count != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        {
            printf("ERROR! INCORRECT FORMAT! PLEASE TRY AGAIN:\n");
        }
        count = scanf("%d", &r_light);
        if(r_light < 0)
        {
            count = 0;
        }
    }

    /* Input validation for left rate */
    printf("Enter the traffic arrival rate for the left:\n");
    count = scanf("%f", &l_car);
    if(l_car > 1 || l_car < 0)
    {
        count = 0;
    }
    while (count != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        {
            printf("ERROR! INCORRECT FORMAT! PLEASE TRY AGAIN:\n");
        }
        count = scanf("%f", &l_car);
        if(l_car > 1 || l_car < 0)
        {
            count = 0;
        }
    }

    /* Input validation for right rate */
    printf("Enter the traffic arrival rate for the right:\n");
    count = scanf("%f", &r_car);
    if(r_car > 1 || r_car < 0)
    {
        count = 0;
    }
    while (count != 1)
    {
        while((temp=getchar()) != EOF && temp != '\n');
        {
            printf("ERROR! INCORRECT FORMAT! PLEASE TRY AGAIN:\n");
        }
        count = scanf("%f", &r_car);
        if(r_car > 1 || r_car < 0)
        {
            count = 0;
        }
    }

   /* print parameters */
    printf("\nParameter values:\n   from left:\n      traffic arrival rate : %.2f\n      traffic light period : %3d\n", l_car, l_light);
    printf("   from right:\n      traffic arrival rate : %.2f\n      traffic light period : %3d\n", r_car, r_light);

    RESULT results;
    int x;

    /* left result variables */
    int l_passed = 0;
    float l_average = 0;
    int l_clear = 0;
    int l_max_time = 0;

    /* right result variables */
    int r_passed = 0;
    float r_average = 0;
    int r_clear = 0;
    int r_max_time = 0;

    /* Run 100 times */
    for(x=0; x < 100; x++)
    {
        results = runOneSimulation(l_light, r_light, l_car, r_car, r);
        l_passed += results.l_passed;
        l_average += results.l_average;
        l_clear += results.l_clear;
        l_max_time += results.l_max_time;
        r_passed += results.r_passed;
        r_average += results.r_average;
        r_clear += results.r_clear;
        r_max_time += results.r_max_time;
    }
    /* Average results */
    float fl_passed = (float) l_passed/100.0;
    float fl_average = (float) l_average/100.0;
    float fl_clear = (float) l_clear/100.0;
    float fl_max_time = (float) l_max_time/100.0;
    float fr_passed = (float) r_passed/100.0;
    float fr_average = (float) r_average/100.0;
    float fr_clear = (float) r_clear/100.0;
    float fr_max_time = (float) r_max_time/100.0;

    /* print results as per the spec */
    printf("Results (averaged over 100 runs):\n");
    printf("   from left:\n      number of vehicles: %.2f\n      average waiting time: %.2f\n      maximum waiting time: %.2f\n      clearance time: %.2f\n", fl_passed, fl_average, fl_max_time, fl_clear);
    printf("   from right:\n      number of vehicles: %.2f\n      average waiting time: %.2f\n      maximum waiting time: %.2f\n      clearance time: %.2f\n\n", fr_passed, fr_average, fr_max_time, fr_clear);
    gsl_rng_free (r);
    return 0;
}
