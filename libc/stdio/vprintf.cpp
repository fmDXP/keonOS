/*
 * keonOS - libc/stdio/vprintf.cpp
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

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <drivers/serial.h>

static void print(const char* data, size_t data_length) 
{
    for (size_t i = 0; i < data_length; i++)
    {
        putchar((int) ((const unsigned char*) data)[i]);
    }
}


int vprintf(const char* format, va_list arg) 
{
    int written = 0;

    while (*format != '\0') 
    {
        if (format[0] != '%' || format[1] == '%') 
        {
            if (format[0] == '%') format++;
            size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
        
            print(format, amount);
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        bool align_left = false;
        if (*format == '-') 
        {
            align_left = true;
            format++;
        }

        int width = 0;
        while (*format >= '0' && *format <= '9') 
        {
            width = width * 10 + (*format - '0');
            format++;
        }

        int length_mod = 0;
        while (*format == 'l') 
        {
            length_mod++;
            format++;
        }

        if (*format == 'c') 
        {
            format++;
            char c = (char) va_arg(arg, int);
            print(&c, sizeof(c));
            written++;
        } 

        else if (*format == 's') 
        {
            format++;
            const char* s = va_arg(arg, const char*);
            if (!s) s = "(null)";
            size_t len = strlen(s);

            if (!align_left && (int)len < width) 
                for (int p = 0; p < (width - (int)len); p++) 
                {
                    char space = ' ';
                    print(&space, 1);
                    written++;
                }
            

            print(s, len);
            written += len;

            if (align_left && (int)len < width) 
                for (int p = 0; p < (width - (int)len); p++) 
                {
                    char space = ' ';
                    print(&space, 1);
                    written++;
                }
            
        } 

        else if (*format == 'd' || *format == 'i' || *format == 'u' || *format == 'x' || *format == 'p') 
        {
            char type = *format;
            format++;
            char buffer[64];
            int total_len = 0;

            if (type == 'd' || type == 'i')
            {
                long long val = (length_mod >= 2) ? va_arg(arg, long long) : (length_mod == 1) ? va_arg(arg, long) : va_arg(arg, int);
                itoa(val, buffer, 10);
            } 

            else if (type == 'u') 
            {
                unsigned long long val = (length_mod >= 2) ? va_arg(arg, unsigned long long) : (length_mod == 1) ? va_arg(arg, unsigned long) : va_arg(arg, unsigned int);
                ulltoa(val, buffer, 10);
            } 

            else 
            {
                unsigned long long val = (type == 'p') ? (uintptr_t)va_arg(arg, void*) : (length_mod >= 2) ? va_arg(arg, unsigned long long) : (length_mod == 1) ? va_arg(arg, unsigned long) : va_arg(arg, unsigned int);
                ulltoa(val, buffer, 16);
            }

            size_t len = strlen(buffer);
            total_len = len;

            if (type == 'p') total_len = (len < 16) ? 16 + 2 : len + 2; 


            if (!align_left && total_len < width) 
            {
                for (int p = 0; p < (width - total_len); p++)
                {
                    char space = ' '; print(&space, 1); written++;
                }
            }

            if (type == 'p') 
            {
                print("0x", 2);
                written += 2;
                if (len < 16) 
                {
                    for (size_t i = 0; i < (16 - len); i++)
                    {
                        char zero = '0'; print(&zero, 1); written++;
                    }
                }
            }

            print(buffer, len);
            written += len;

            if (align_left && total_len < width) 
            {
                for (int p = 0; p < (width - total_len); p++)
                {
                    char space = ' '; print(&space, 1); written++;
                }
            }
        }

        else 
        {
            size_t len = format - format_begun_at;
            print(format_begun_at, len);
            written += len;
        }
    }
    return written;
}