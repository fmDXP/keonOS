/*
 * keonOS - include/kernel/arch/i386/gdt.h
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

#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>

extern "C" 
{
	struct gdt_entry
	{
		uint16_t limit_low;
		uint16_t base_low;
		uint8_t base_middle;
		uint8_t access;
		uint8_t granularity;
		uint8_t base_high;
	} __attribute__((packed));

	struct gdt_ptr
	{
		uint16_t limit;
		uint32_t base;
	} __attribute__((packed));

	void gdt_init();
	void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

	extern "C" void gdt_flush(uint32_t);
}

#endif		// _KERNEL_GDT_H