/*
 * keonOS - libc/stdlib/abort.cpp
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

#include <kernel/panic.h>
#include <kernel/error.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void)
{
	#if defined(__is_libk)
		panic(KernelError::K_ERR_UNKNOWN_ERROR, "Kernel called 'abort()'", 0xDEAD);
	#else
		printf("Panic: User process called abort()\n");
		while (1) asm volatile("hlt");
		// In Userspace we'd use SIGABRT
	#endif
		__builtin_unreachable();
}