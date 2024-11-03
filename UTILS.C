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

//function to replace unicode chars by correct char code
char replace_unicode(char character)
{
    switch (character)
    {
        case '§':
            return CHAR_NY;
        case '•':
            return CHAR_NY_CAP;
        case '®':
            return CHAR_QUESTION;
        case '≠':
            return CHAR_EXCLAMATION;
        case '†':
            return CHAR_A_ACCENT;
        case 'Ç':
            return CHAR_E_ACCENT;
        case '°':
            return CHAR_I_ACCENT;
        case '¢':
            return CHAR_O_ACCENT;
        case '£':
            return CHAR_U_ACCENT;
        case 'µ':
            return CHAR_A_ACCENT_CAP;
        case 'ê':
            return CHAR_E_ACCENT_CAP;
        case '÷':
            return CHAR_I_ACCENT_CAP;
        case '‡':
            return CHAR_O_ACCENT_CAP;
        case 'È':
            return CHAR_U_ACCENT_CAP;
        default:
            return character;
    }
}

//function to replace unicode latin char on entire string
void replace_unicode_str(char *str)
{
    for (int i = 0; i < strlen(str); i++)
        //replace unicode latin characters
        str[i] = replace_unicode(str[i]);
}

//function to replace unicode and wrap text
void replace_unicode_and_wrap(char *str, int wrapChars)
{
    int msgCharCount = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        //replace unicode latin characters
        str[i] = replace_unicode(str[i]);

        //insert new line every wrapChars on each space char
        if (msgCharCount > wrapChars)
        {
            //if char is space or new_line char
            if (str[i] == 0x20 || str[i] == 0x0A)
            {
                //replace with new_line char
                str[i] = 0x0A;
                //reset the counter
                msgCharCount = -1;
            }
        }
        msgCharCount++;
    }
}
