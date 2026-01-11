/*
 * keonOS - include/libc/stdlib.h
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

#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EOVERFLOW 	75
#define EINVAL		22
#define ENOMEM		12

extern uintptr_t __stack_chk_guard;
__attribute__((noreturn)) void __stack_chk_fail(void);

__attribute__((__noreturn__))
void abort(void);

char* itoa(int value, char* str, int base);
char* utoa(unsigned int value, char* str, int base);
unsigned long strtoul(const char* nptr, char** endptr, int base);
int atoi(const char* str);


extern int errno;

#ifdef __cplusplus
}
#endif

#endif