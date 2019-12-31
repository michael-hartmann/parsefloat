#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#include "strtodouble.h"

double strtodouble(const char *str, int *success)
{
    double intpart = 0, fracpart = 0, exponent = 0;
    int sign = +1, len = 0, conversion = 0;

    // skip whitespace
    while(isspace(*str))
        str++;

    // check for sign (optional; either + or -)
    if(*str == '-')
    {
        sign = -1;
        str++;
    }
    else if(*str == '+')
        str++;

    // check for nan and inf
    if(tolower(str[0]) == 'n' && tolower(str[1]) == 'a' && tolower(str[2]) == 'n')
    {
        if(success != NULL)
            *success = 1;
        return NAN;
    }
    if(tolower(str[0]) == 'i' && tolower(str[1]) == 'n' && tolower(str[2]) == 'f')
    {
        if(success != NULL)
            *success = 1;
        return sign*INFINITY;
    }

    // find number of digits before decimal point
    const char *p = str;
    len = 0;
    while(isdigit(*p))
    {
        p++;
        len++;
    }

    if(len)
        conversion = 1;

    // convert intpart part of decimal point to a float
    {
        double f = 1;
        for(int i = 0; i < len; i++)
        {
            int v = str[len-1-i] - '0';
            intpart += v*f;
            f *= 10;
        }
        str = p;
    }

    // check for decimal point (optional)
    if(*str == '.')
    {
        p = ++str;

        // find number of digits after decimal point
        len = 0;
        while(isdigit(*p))
        {
            p++;
            len++;
        }

        if(len)
            conversion = 1;

        // convert fracpart part of decimal point to a float
        double f = 0.1;
        for(int i = 0; i < len; i++)
        {
            int v = str[i] - '0';
            fracpart += v*f;
            f *= 0.1;
        }

        str = p;
    }

    if(conversion && (*str == 'e' || *str == 'E'))
    {
        int expsign = +1;
        p = ++str;

        if(*p == '+')
            p++;
        else if(*p == '-')
        {
            expsign = -1;
            p++;
        }

        str = p;
        len = 0;
        while(isdigit(*p))
        {
            len++;
            p++;
        }

        int f = 1;
        for(int i = 0; i < len; i++)
        {
            int v = str[len-1-i]-'0';
            exponent += v*f;
            f *= 10;
        }

        exponent *= expsign;
    }

    if(!conversion)
    {
        if(success != NULL)
            *success = 0;
        return NAN;
    }

    if(success != NULL)
        *success = 1;

    return sign*(intpart+fracpart)*pow(10, exponent);
}
