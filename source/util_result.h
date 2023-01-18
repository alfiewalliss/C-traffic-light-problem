#ifndef __UTIL_RESULT_H
#define __UTIL_RESULT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*----- structure definition -------------------------------------------------*/
struct resultStruct
{
    int l_passed;
    float l_average;
    int l_max_time;
    int l_clear;
    int r_passed;
    float r_average;
    int r_max_time;
    int r_clear;
};
typedef struct resultStruct RESULT;

#endif
