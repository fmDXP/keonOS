/*
 * keonOS - include/mm/vmm.h
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

#ifndef VMM_H
#define VMM_H

#include <stdint.h>
#include <stddef.h>

class VMM
{
public:
	static void* allocate(size_t pages, uint32_t flags);
	static void free(void* virt_addr, size_t pages);
	static void* sbrk(size_t increment_bytes);
	static size_t get_total_allocated();
	static uintptr_t kernel_dynamic_break;
	static void* map_physical_region(uintptr_t phys_addr, size_t pages, uint32_t flags);
};


#endif		// VMM_H