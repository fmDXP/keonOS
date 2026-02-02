/*
 * keonOS - kernel/arch/x86_64/idt.cpp
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

#include <kernel/arch/x86_64/idt.h>
#include <kernel/arch/x86_64/paging.h>
#include <kernel/panic.h>
#include <drivers/vga.h>
#include <stdio.h>

struct idt_entry idt_entries[256];
struct idt_ptr idt_pointer;


extern "C" void outb(uint16_t port, uint8_t value) 
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

extern "C" uint8_t inb(uint16_t port) 
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

extern "C" void outw(uint16_t port, uint16_t value) 
{
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}

extern "C" uint16_t inw(uint16_t port) 
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}


void idt_set_gate(uint8_t num, uint64_t base, uint16_t selector, uint8_t flags) 
{
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_mid = (base >> 16) & 0xFFFF;
    idt_entries[num].base_high = (base >> 32) & 0xFFFFFFFF;
    
    idt_entries[num].selector = selector;
    idt_entries[num].ist = 0;     
    idt_entries[num].flags = flags;
    idt_entries[num].reserved = 0;
}

bool idt_init() 
{
    idt_pointer.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_pointer.base = (uint64_t)&idt_entries;

    for (int i = 0; i < 256; i++)
        idt_set_gate((uint8_t)i, (uint64_t)0, (uint16_t)0, (uint8_t)0);
    
    idt_set_gate(0,  (uint64_t)isr0,  0x08, 0x8E); idt_set_gate(1,  (uint64_t)isr1,  0x08, 0x8E);
    idt_set_gate(2,  (uint64_t)isr2,  0x08, 0x8E); idt_set_gate(3,  (uint64_t)isr3,  0x08, 0x8E);
    idt_set_gate(4,  (uint64_t)isr4,  0x08, 0x8E); idt_set_gate(5,  (uint64_t)isr5,  0x08, 0x8E);
    idt_set_gate(6,  (uint64_t)isr6,  0x08, 0x8E); idt_set_gate(7,  (uint64_t)isr7,  0x08, 0x8E);
    idt_set_gate(8,  (uint64_t)isr8,  0x08, 0x8E); idt_set_gate(9,  (uint64_t)isr9,  0x08, 0x8E);
    idt_set_gate(10, (uint64_t)isr10, 0x08, 0x8E); idt_set_gate(11, (uint64_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint64_t)isr12, 0x08, 0x8E); idt_set_gate(13, (uint64_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint64_t)isr14, 0x08, 0x8E); idt_set_gate(15, (uint64_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint64_t)isr16, 0x08, 0x8E); idt_set_gate(17, (uint64_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint64_t)isr18, 0x08, 0x8E); idt_set_gate(19, (uint64_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint64_t)isr20, 0x08, 0x8E); idt_set_gate(21, (uint64_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint64_t)isr22, 0x08, 0x8E); idt_set_gate(23, (uint64_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint64_t)isr24, 0x08, 0x8E); idt_set_gate(25, (uint64_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint64_t)isr26, 0x08, 0x8E); idt_set_gate(27, (uint64_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint64_t)isr28, 0x08, 0x8E); idt_set_gate(29, (uint64_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint64_t)isr30, 0x08, 0x8E); idt_set_gate(31, (uint64_t)isr31, 0x08, 0x8E);

    idt_set_gate(32, (uint64_t)irq0,  0x08, 0x8E); idt_set_gate(33, (uint64_t)irq1,  0x08, 0x8E);
    idt_set_gate(34, (uint64_t)irq2,  0x08, 0x8E); idt_set_gate(35, (uint64_t)irq3,  0x08, 0x8E);
    idt_set_gate(36, (uint64_t)irq4,  0x08, 0x8E); idt_set_gate(37, (uint64_t)irq5,  0x08, 0x8E);
    idt_set_gate(38, (uint64_t)irq6,  0x08, 0x8E); idt_set_gate(39, (uint64_t)irq7,  0x08, 0x8E);
    idt_set_gate(40, (uint64_t)irq8,  0x08, 0x8E); idt_set_gate(41, (uint64_t)irq9,  0x08, 0x8E);
    idt_set_gate(42, (uint64_t)irq10, 0x08, 0x8E); idt_set_gate(43, (uint64_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint64_t)irq12, 0x08, 0x8E); idt_set_gate(45, (uint64_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint64_t)irq14, 0x08, 0x8E); idt_set_gate(47, (uint64_t)irq15, 0x08, 0x8E);
    
    outb(0x20, 0x11); outb(0xA0, 0x11); 
    outb(0x21, 0x20); outb(0xA1, 0x28);
    outb(0x21, 0x04); outb(0xA1, 0x02);
    outb(0x21, 0x01); outb(0xA1, 0x01);
    
    outb(0x21, 0xF8); 
    outb(0xA1, 0xFF);

    idt_flush((uintptr_t)(&idt_pointer));
    return true;
}

extern "C" void page_fault_handler(uint64_t error_code) 
{
    uint64_t faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));
    printf("\n=== PAGE FAULT (x86_64) ===\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
    
    printf("Faulting Address: 0x%lx\n", faulting_address);
    printf("Error Code: 0x%lx\n", (unsigned long)error_code);
    
    panic(KernelError::K_ERR_PAGE_FAULT, "MMU Violation", (uint32_t)error_code);
}

extern "C" void isr_exception_handler(registers_t* regs) 
{
    if (regs->int_no >= 32 && regs->int_no <= 47) 
	{
        if (regs->int_no == 32) timer_handler();
        else if (regs->int_no == 33) keyboard_handler();
        
        if (regs->int_no >= 40) outb(0xA0, 0x20);
        outb(0x20, 0x20);
        return;
    }

    if (regs->int_no == 14) 
	{
        page_fault_handler(regs->err_code);
        return;
    }

    printf("\nEXCEPTION: Int %d (Error Code: 0x%lx)\n", (int)regs->int_no, regs->err_code);
    panic(KernelError::K_ERR_UNKNOWN_ERROR, "CPU Exception", (uint32_t)regs->err_code, regs);
}