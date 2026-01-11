/*
 * keonOS - drivers/serial.cpp
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


#include <kernel/arch/i386/idt.h>
#include <kernel/constants.h>
#include <drivers/serial.h>


void serial_install() 
{
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x80);
    outb(COM1 + 0, 0x03);
    outb(COM1 + 1, 0x00);
    outb(COM1 + 3, 0x03);
    outb(COM1 + 2, 0xC7);
    outb(COM1 + 4, 0x0B);
}

int is_transmit_empty() 
{
    return inb(COM1 + 5) & 0x20;
}

void write_serial(char a) 
{
    while (is_transmit_empty() == 0);
    outb(COM1, a);
}

void serial_putc(char c) 
{
    if (c == '\b') 
    {
        while ((inb(COM1 + 5) & 0x20) == 0);
        outb(COM1, '\b');
        
        while ((inb(COM1 + 5) & 0x20) == 0);
        outb(COM1, ' ');
        
        while ((inb(COM1 + 5) & 0x20) == 0);
        outb(COM1, '\b');
    } 
    else 
    {
        while ((inb(COM1 + 5) & 0x20) == 0);
        outb(COM1, c);
    }
}