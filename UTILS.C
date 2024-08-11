#include <stdbool.h>

//retuns true if the value is on target +/- the offset
bool in_range(int value, int target, int offset)
{
    return ( value <= (target + offset) && value >= (target - offset) );
}
