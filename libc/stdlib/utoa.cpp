/*
 * keonOS - libc/stdlib/utoa.cpp
 * Copyright (C) 2025-2026 fmdxp
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ADDITIONAL TERMS (Per Section 7 of the GNU GPLv3):
 * - Original author attributions must be preserved in all copies.
 * - Modified versions must be marked as different from the original.
 * - The name "keonOS" or "fmdxp" cannot be used for publicity without permission.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 */

#include <stdlib.h>

char* utoa(unsigned int value, char* str, int base) 
{
    char *rc;
    char *ptr;
    char *lowstr;
    
    rc = ptr = str;
    
    if (base < 2 || base > 36)
	{
        *str = '\0';
        return str;
    }

    do 
	{
        unsigned int res = value % base;
        *ptr++ = "0123456789abcdefghijklmnopqrstuvwxyz"[res];
        value /= base;
    } while (value);

    *ptr-- = '\0';

    lowstr = rc;
    while (lowstr < ptr) 
	{
        char tmp = *lowstr;
        *lowstr++ = *ptr;
        *ptr-- = tmp;
    }
    return rc;
}