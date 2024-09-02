#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "time.h"

//retuns true if the value is on target +/- the offset
bool in_range(int value, int target, int offset)
{
    return ( value <= (target + offset) && value >= (target - offset) );
}

//clamp value between min and max
int clamp(int value, int min, int max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

//clamp fixed value between min and max
fixed fix_clamp(fixed value, fixed min, fixed max)
{
    if (value < min)
        return min;
    else if (value > max)
        return max;
    else
        return value;
}

//normalize a value with min max to 0..1
fixed norm_x(int value, int min, int max)
{
    return fixdiv(itofix(value - min),itofix(max - min));
}

//normalize a fixed value with min max to 0..1
fixed fix_norm_x(fixed value, fixed min, fixed max)
{
    return (value - min) / (max - min);
}

//scale a normalized value between min and max
int scale_x(fixed value, int min, int max)
{
    int ret_val = fixtoi(fixadd((fixmul(value, itofix(max)) - fixmul(value, itofix(min))), itofix(min)));
    return clamp(ret_val, min, max);
}

//scale a normalized value between min and max and return fixed
fixed fix_scale_x(fixed value, fixed min, fixed max)
{
    fixed ret_val = fixadd((fixmul(value, max) - fixmul(value, min)), min);
    return clamp(ret_val, min, max);
}

//function to copy actual date to string input parameter
void get_actual_date(char *s)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(s,"%02d/%02d/%d %02d:%02d:%02d", timeinfo->tm_mday, (timeinfo->tm_mon + 1), (1900 + timeinfo->tm_year),
                                   timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
