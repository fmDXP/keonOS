/*
 * keonOS - libc/stdio/getchar.cpp
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

#if defined(__is_libk)
#include <drivers/keyboard.h>
#endif
#include <sys/syscall.h>

int getchar(void) 
{
    uint16_t cs;
    asm volatile("mov %%cs, %0" : "=r"(cs));
    if ((cs & 3) == 3) 
    {
        char c;
        if (syscall(SYS_READ, 0, (uint64_t)&c, 1, 0, 0, 0) == 1) return (int)c;
        return -1;
    }

#if defined(__is_libk)
	return (int) keyboard_getchar();
#else
	char c;
	size_t bytes_read = syscall(SYS_READ, 0, (uint64_t)&c, 1, 0, 0, 0);
	if (bytes_read == 1) return (int) c;
	return -1;
#endif
}
