/*
 * keonOS - libc/stdlib/strtoul.cpp
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
#include <ctype.h>

unsigned long strtoul(const char* nptr, char** endptr, int base) 
{
    const char* s = nptr;
    unsigned long acc = 0;
    int c;
    bool any = false;

    while (isspace((unsigned char)*s)) s++;

    if (base == 0) 
	{
        if (*s == '0') 
		{
            s++;

            if (*s == 'x' || *s == 'X') 
			{
                s++;
                base = 16;
            } 
			else base = 8;
            
        } 
		else base = 10;
        
    } 

	else if (base == 16) 
        if (*s == '0' && (s[1] == 'x' || s[1] == 'X'))
			 s += 2;
    

    for (;; s++) 
	{
        c = (unsigned char)*s;

        if (isdigit(c))
			c -= '0';

        else if (isalpha(c))
			c = toupper(c) - 'A' + 10;

        else break;

        if (c >= base) break;
        acc = acc * base + c;
        any = true;
    }

    if (endptr != nullptr)
        *endptr = (char*)(any ? s : nptr);

    return acc;
}