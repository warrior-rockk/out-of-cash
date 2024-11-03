#ifndef H_UTILS
#define H_UTILS

#include <allegro.h>

//macros for bit masking
#define SET_BIT(byte, bit)       ((byte) |=  (1<<(bit)))
#define CLEAR_BIT(byte, bit)     ((byte) &= ~(1<<(bit)))
#define TOOGLE_BIT(byte, bit)    ((byte) ^=  (1<<(bit)))
#define CHECK_BIT(byte, bit)     ((byte) &   (1<<(bit)))

//Unicode Latin 1 chars
#define CHAR_QUESTION       '\xBF'
#define CHAR_NY             '\xF1'
#define CHAR_NY_CAP         '\xD1'
#define CHAR_A_ACCENT       '\xE1'
#define CHAR_E_ACCENT       '\xE9'
#define CHAR_I_ACCENT       '\xED'
#define CHAR_O_ACCENT       '\xF3'
#define CHAR_U_ACCENT       '\xFA'
#define CHAR_A_ACCENT_CAP   '\xC1'
#define CHAR_E_ACCENT_CAP   '\xC9'
#define CHAR_I_ACCENT_CAP   '\xCD'
#define CHAR_O_ACCENT_CAP   '\xD3'
#define CHAR_U_ACCENT_CAP   '\xDA'
#define CHAR_EXCLAMATION    '\xA1'

//function definitions
bool in_range(int value, int target, int offset);

int clamp(int value, int min, int max);
fixed fix_clamp(fixed value, fixed min, fixed max);
fixed norm_x(int value, int min, int max);
fixed fix_norm_x(fixed value, fixed min, fixed max);

int scale_x(fixed value, int min, int max);
fixed fix_scale_x(fixed value, fixed min, fixed max);

void get_actual_date(char *s);

char replace_unicode(char character);
void replace_unicode_str(char *str);
void replace_unicode_and_wrap(char *str, int wrapChars);
#endif
