#ifndef _MISC_H
#define _MISC_H

#define true 1
#define false 0
typedef unsigned char uint8_t;

char *my_ftoa(float value, char *result)
{
    uint8_t precision = 6;
    char *out_ptr = result;
    const int bufferSize = 10;
    char buffer[bufferSize+1];
// получили цифры
    int exp10 = ftoaEngine(value, buffer, precision);
// если там inf или nan - выводим как есть.
    if(exp10 == 0xff)
    {
        uint8_t digits = strlen(buffer);
        uint_fast8_t i = 0;
        if(buffer[0] == '+')
            i = 1;

        for(; i < digits; i++)
            *out_ptr++ = buffer[i];
        *out_ptr = 0;
        return result;
    }
// если был перенос старшей цифры при округлении
    char *str_begin = &buffer[2];
    if(buffer[1] != '0')
    {
        exp10++;
        str_begin--;
    }
// количество значащих цифр <= precision
    uint_fast8_t digits = strlen(str_begin);

    uint_fast8_t intDigits=0, leadingZeros = 0;
    if(abs(exp10) >= precision)
    {
        intDigits = 1;
    }else if(exp10 >= 0)
    {
        intDigits = exp10+1;
        exp10 = 0;
    }else
    {
        intDigits = 0;
        leadingZeros = -exp10 - 1;
        exp10 = 0;
    }
    uint_fast8_t fractDigits = digits > intDigits ? digits - intDigits : 0;
// целая часть
    if(intDigits)
    {
        uint_fast8_t count = intDigits > digits ? digits : intDigits;
        while(count--)
            *out_ptr++ = *str_begin++;
        int_fast8_t tralingZeros = intDigits - digits;
        while(tralingZeros-- > 0)
            *out_ptr++ ='0';
    }
    else
        *out_ptr++ = '0';
// дробная часть
    if(fractDigits)
    {
        *out_ptr++ = '.';
        while(leadingZeros--)
            *out_ptr++ = '0';
        while(fractDigits--)
            *out_ptr++ = *str_begin++;
    }
// десятичная экспонента
    if(exp10 != 0)
    {
        *out_ptr++ = 'e';
        uint_fast8_t upow10;
        if(exp10 < 0)
        {
            *out_ptr++ = '-';
            upow10 = -exp10;
        }
        else
        {
            *out_ptr++ = '+';
            upow10 = exp10;
        }
        char *powPtr = utoa_fast_div(upow10, buffer + bufferSize);
        while(powPtr < buffer + bufferSize)
        {
            *out_ptr++ = *powPtr++;
        }
    }
    *out_ptr = 0;
    return result;
}

#endif