/*
 * keonOS - include/kernel/arch/i386/idt.h
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

#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

#include <stdint.h>
#include <kernel/constants.h>

struct idt_entry
{
	uint16_t 	base_low;
	uint16_t 	selector;
	uint8_t 	zero;
	uint8_t 	flags;
	uint16_t 	base_high;
} __attribute__((packed));

struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

struct registers_t
{
	uint32_t ds;
	uint32_t edi, esi, ebp, esp_ptr, ebx, edx, ecx, eax;
	uint32_t int_no, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
};


extern "C" void outb(uint16_t port, uint8_t value);
extern "C" uint8_t inb(uint16_t port);
extern "C" void outw(uint16_t port, uint16_t value);
extern "C" uint16_t inw(uint16_t port);

bool idt_init();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);


extern "C" void idt_flush(uint32_t);

extern "C" void timer_handler();
extern "C" void keyboard_handler();

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr14(); 
extern "C" void irq0(); 
extern "C" void irq1(); 

#endif		// _KERNEL_IDT_H