/*
 * keonOS - kernel/panic.cpp
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
#include <kernel/arch/x86_64/idt.h>
#include <drivers/vga.h>
#include <stdio.h>
#include <string.h>

/*
 * panic: Handles unrecoverable kernel errors.
 * Displays system state, CPU registers, and a memory dump before halting.
*/

void panic(KernelError error, const char* message, uint32_t error_code, struct registers_t* regs)
{
    // 1. Safety first: Disable interrupts to prevent context switching during panic
    asm volatile("cli");   
    
    // Clear screen and set a high-visibility alert color (White on Red)
    terminal_clear();
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));
    
    printf("\n");
    printf("========================================\n");
    printf("   KERNEL PANIC - SYSTEM HALTED\n");
    printf("========================================\n");
    printf("\n");
    
    // Display the specific error type categorized by the kernel
    terminal_setcolor(vga_color_t(VGA_COLOR_YELLOW, VGA_COLOR_RED));
    printf("Error type: ");
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));
    printf("%s", kerror_to_str(error));
    printf("\n");
    
    // If a custom developer message was provided, show it
    if (message)
    {
        terminal_setcolor(vga_color_t(VGA_COLOR_YELLOW, VGA_COLOR_RED));
        printf("Message: ");
        terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));
        printf("%s", message);
    }
    
    // Display raw error code (useful for Page Faults or Exception codes)
    if (error_code || error_code == 0UL)
    {
        terminal_setcolor(vga_color_t(VGA_COLOR_YELLOW, VGA_COLOR_RED));
        printf("\nError Code: 0x");
        terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));
        
        char buffer[32];
        itoa(static_cast<int>(error_code), buffer, 16);
        printf("%s", buffer);
    }

    // 2. CPU Snapshot: Use provided registers or capture current ones
    uint64_t rax, rbx, rcx, rdx, rsp, rbp, rsi, rdi;
    uint64_t cr0, cr2, cr3, rip = 0, cs = 0, rflags = 0;
    
    if (regs)
    {
        rax = regs->rax; rbx = regs->rbx; rcx = regs->rcx; rdx = regs->rdx;
        rsi = regs->rsi; rdi = regs->rdi; rbp = regs->rbp; rsp = regs->rsp;
        rip = regs->rip; cs = regs->cs; rflags = regs->rflags;
    }
    else
    {
        asm volatile("mov %%rax, %0" : "=r"(rax));
        asm volatile("mov %%rbx, %0" : "=r"(rbx));
        asm volatile("mov %%rcx, %0" : "=r"(rcx));
        asm volatile("mov %%rdx, %0" : "=r"(rdx));
        asm volatile("mov %%rsi, %0" : "=r"(rsi));
        asm volatile("mov %%rdi, %0" : "=r"(rdi));
        asm volatile("mov %%rbp, %0" : "=r"(rbp));
        asm volatile("mov %%rsp, %0" : "=r"(rsp));
    }

    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    asm volatile("mov %%cr2, %0" : "=r"(cr2));
    asm volatile("mov %%cr3, %0" : "=r"(cr3));


    printf("\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_YELLOW, VGA_COLOR_RED));
    printf("Registers (x64):\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));

    printf("RAX: %16llx RBX: %16llx\n", rax, rbx);
    printf("RCX: %16llx RDX: %16llx\n", rcx, rdx);
    printf("RSI: %16llx RDI: %16llx\n", rsi, rdi);
    printf("RBP: %16llx RSP: %16llx\n", rbp, rsp); 
    if (regs) printf("RIP: %16llx CS:  %16llx RFLG: %16llx\n", rip, cs, rflags);
    printf("CR0: %16llx CR2: %16llx CR3: %16llx\n", cr0, cr2, cr3);


    // 3. Memory Dump: Show a hex/ASCII preview of the stack
    // This allows the developer to see local variables and return addresses
    printf("\n\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_YELLOW, VGA_COLOR_RED));
    printf("Stack Trace Dump:\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_WHITE, VGA_COLOR_RED));

    uint8_t* ptr = (uint8_t*)rsp;
    for (int i = 0; i < 64; i += 16) 
    {
        printf("0x%16llx: ", (uintptr_t)(ptr + i));

        for (int j = 0; j < 16; j++) 
        {
            if (ptr[i+j] < 0x10) printf("0");
            char buf[10];
            itoa(ptr[i+j], buf, 16);
            printf("%s ", buf);
        }

        printf(" | ");

        // ASCII sidebar: Shows printable characters, hides control characters with '.'
        for (int j = 0; j < 16; j++) 
        {
            char c = ptr[i+j];
            if (c >= 32 && c <= 126) printf("%c", c);
            else printf(".");
        }
        printf("\n");
    }

    printf("\n");
    terminal_setcolor(vga_color_t(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_RED));
    printf("System: %s\n", OS_VERSION_STRING);

    // Final Halt: Put the CPU in a low-power state and wait for a hard reset
    while (1) { asm volatile ("hlt"); }
}