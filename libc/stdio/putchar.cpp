/*
 * keonOS - libc/stdio/putchar.cpp
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
#include <sys/syscall.h>
#include <stdint.h>

#if defined(__is_libk)
#include <drivers/vga.h>
#include <drivers/serial.h>
#endif

int putchar(int ic) 
{
    uint16_t cs;
    asm volatile("mov %%cs, %0" : "=r"(cs));
    if ((cs & 3) == 3) 
    {
        char c = (char) ic;
        syscall(SYS_WRITE, 1, (uintptr_t)&c, 1, 0, 0, 0);
        return ic;
    }

#if defined(__is_libk)
	char c = (char) ic;
	serial_putc(c);
	terminal_write(&c, sizeof(c));
#else
	char c = (char) ic;
	syscall(SYS_WRITE, 1, (uintptr_t)&c, 1, 0, 0, 0);
#endif
	return ic;
}