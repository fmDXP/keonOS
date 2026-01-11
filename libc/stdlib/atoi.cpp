/*
 * keonOS - libc/stdlib/atoi.cpp
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

int atoi(const char* str) 
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') 
	{
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i) 
	{
        if (str[i] < '0' || str[i] > '9') break;
        res = res * 10 + str[i] - '0';
    }

    return sign * res;
}