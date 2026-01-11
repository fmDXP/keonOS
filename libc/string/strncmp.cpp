/*
 * keonOS - libc/string/strncmp.cpp
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


#include <string.h>

int strncmp(const char* s1, const char* s2, size_t n) 
{
    while (n > 0) 
    {
        if (*s1 != *s2) 
        {
            return *(unsigned char*)s1 - *(unsigned char*)s2;
        }
        if (*s1 == '\0') 
        {
            return 0;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}