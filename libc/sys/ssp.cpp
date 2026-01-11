/*
 * keonOS - libc/sys/ssp.cpp
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

#include <stdint.h>
#include <stdlib.h>
#include <kernel/panic.h>
#include <kernel/error.h>

#if UINTPTR_MAX == UINT32_MAX
	#define STACK_CHK_GUARD 0xe2dee396
#else
	#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

extern "C" 
{
	uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

	__attribute__((noreturn))
	void __stack_chk_fail(void)
	{
		panic(KernelError::K_ERR_STACK_SMASHED, "STACK SMASHING DETECTED: The kernel was protected from a buffer overflow.", 0xDEADBEEF);
		while (1) asm("cli; hlt");
	}

}