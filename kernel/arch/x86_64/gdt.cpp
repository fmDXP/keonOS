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
#include <string.h>

alignas(16) gdt_entry gdt[10]; 
gdt_ptr gp;
tss_entry kernel_tss;

void gdt_set_tss(int32_t num, uint64_t base, uint32_t limit) 
{
    gdt_tss_descriptor* tss_desc = (gdt_tss_descriptor*)&gdt[num];

    tss_desc->limit_low     = limit & 0xFFFF;
    tss_desc->base_low      = base & 0xFFFF;
    tss_desc->base_mid      = (base >> 16) & 0xFF;
    tss_desc->access        = 0x89;
    tss_desc->granularity   = ((limit >> 16) & 0x0F);
    tss_desc->base_high     = (base >> 24) & 0xFF;
    tss_desc->base_upper    = (base >> 32) & 0xFFFFFFFF;
    tss_desc->reserved      = 0;
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


void tss_set_stack(uintptr_t stack) 
{
    kernel_tss.rsp0 = stack & ~0xFULL;
}


void gdt_init()
{
    memset(gdt, 0, sizeof(gdt));

    gdt_set_gate(0, 0, 0, 0, 0);                
    gdt_set_gate(1, 0, 0, 0x9A, 0x20);          
    gdt_set_gate(2, 0, 0, 0x92, 0x00);          
    gdt_set_gate(3, 0, 0, 0xF2, 0x00); // UData (Indice 3)
    gdt_set_gate(4, 0, 0, 0xFA, 0x20); // UCode (Indice 4)

    kernel_tss.iopb_offset = sizeof(tss_entry);

    gdt_set_tss(5, (uintptr_t)&kernel_tss, sizeof(tss_entry) - 1);

    gp.limit = (8 * 7) - 1; 
    gp.base  = (uintptr_t)&gdt;

    gdt_flush((uintptr_t)&gp);
    tss_load();
}