/*
 * keonOS - libc/stdlib/itoa.cpp
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

char* itoa(int value, char* str, int base) 
{
    char* ptr = str;
    char* ptr1 = str;
    char tmp_char;
    int tmp_value;
    bool negative = false;

    if (value < 0 && base == 10) 
    {
        negative = true;
        value = -value;
    }

    if (value == 0) 
    {
        *ptr++ = '0';
        *ptr = '\0';
        return str;
    }
    
    while (value != 0) 
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
    }

    
    if (negative) *ptr++ = '-';
    *ptr-- = '\0';
    
    while (ptr1 < ptr) 
    {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }

    return str;
}