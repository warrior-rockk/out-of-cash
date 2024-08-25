#ifndef H_UTILS
#define H_UTILS

//macros for bit masking
#define SET_BIT(byte, bit)       ((byte) |=  (1<<(bit)))
#define CLEAR_BIT(byte, bit)     ((byte) &= ~(1<<(bit)))
#define TOOGLE_BIT(byte, bit)    ((byte) ^=  (1<<(bit)))
#define CHECK_BIT(byte, bit)     ((byte) &   (1<<(bit)))

//function definitions
bool in_range(int value, int target, int offset);
#endif
