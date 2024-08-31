#ifndef H_UTILS
#define H_UTILS

#include <allegro.h>

//macros for bit masking
#define SET_BIT(byte, bit)       ((byte) |=  (1<<(bit)))
#define CLEAR_BIT(byte, bit)     ((byte) &= ~(1<<(bit)))
#define TOOGLE_BIT(byte, bit)    ((byte) ^=  (1<<(bit)))
#define CHECK_BIT(byte, bit)     ((byte) &   (1<<(bit)))

//function definitions
bool in_range(int value, int target, int offset);
int clamp(int value, int min, int max);
fixed norm_x(int value, int min, int max);
fixed fix_norm_x(fixed value, fixed min, fixed max);
int scale_x(fixed value, int min, int max);
fixed fix_scale_x(fixed value, fixed min, fixed max);
#endif
