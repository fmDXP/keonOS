/*
 * keonOS - kernel/arch/i386/constructor.cpp
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

#include <kernel/arch/i386/constructor.h>
#include <stdio.h>

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void initialize_constructors()
{
	for (constructor* i = &start_ctors; i < &end_ctors; i++)
		(*i)();
}

extern "C" 
{
	int __cxa_guard_acquire(long *g) { return !*(char *)(g); }
	void __cxa_guard_release(long *g) { *(char *)(g) = 1; }
	void __cxa_guard_abort(long *g) { (void)g; }

	void* __dso_handle = nullptr;
	int __cxa_atexit(void (*f)(void *), void *p, void *d) 
	{
		(void)f; (void)p; (void)d;
		return 0;
	}
}