/*
 * keonOS - kernel/arch/x86_64/gdt.cpp
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


#include <kernel/arch/x86_64/gdt.h>

alignas(16) gdt_entry gdt[7]; 
gdt_ptr gp;

void gdt_set_tss(int32_t num, uint64_t base, uint32_t limit) 
{
    gdt_tss_entry* tss = (gdt_tss_entry*)&gdt[num];

    tss->limit_low = limit & 0xFFFF;
    tss->base_low  = base & 0xFFFF;
    tss->base_mid  = (base >> 16) & 0xFF;
    tss->access    = 0x89;
    tss->granularity = ((limit >> 16) & 0x0F);
    tss->base_high   = (base >> 24) & 0xFF;
    tss->base_upper  = (base >> 32) & 0xFFFFFFFF;
    tss->reserved    = 0;
}

void gdt_set_gate(int32_t num, uint64_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low      = (base & 0xFFFF);
    gdt[num].base_middle   = (base >> 16) & 0xFF;
    gdt[num].base_high     = (base >> 24) & 0xFF; 

    gdt[num].limit_low     = (limit & 0xFFFF);
    gdt[num].granularity   = (limit >> 16) & 0x0F;

    gdt[num].granularity   |= gran & 0xF0;
    gdt[num].access        = access;
}


void gdt_init()
{
    gp.limit = (sizeof(gdt) - 1);
    gp.base  = reinterpret_cast<uintptr_t>(&gdt);

    gdt_set_gate(0, 0, 0, 0, 0);

    // 0x08: Kernel Code Segment (L-bit = 1)
    gdt_set_gate(1, 0, 0, 0x9A, 0x20); 

    // 0x10: Kernel Data Segment
    gdt_set_gate(2, 0, 0, 0x92, 0x00); 

    // 0x18: User Code Segment (DPL = 3)
    gdt_set_gate(3, 0, 0, 0xFA, 0x20); 

    // 0x20: User Data Segment (DPL = 3)
    gdt_set_gate(4, 0, 0, 0xF2, 0x00); 

    gdt_flush(reinterpret_cast<uintptr_t>(&gp));	// Load the GDT
}