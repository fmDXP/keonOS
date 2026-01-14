/*
 * keonOS - include/kernel/arch/x86_64/paging.h
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

#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>


enum PAGE_FLAGS 
{
    PTE_PRESENT  = 0x001,
    PTE_RW       = 0x002,
    PTE_USER     = 0x004,
    PTE_PWT      = 0x008,
    PTE_PCD      = 0x010,
    PTE_ACCESSED = 0x020,
    PTE_DIRTY    = 0x040,
    PTE_GLOBAL   = 0x100,
    PTE_NX       = (1ULL << 63)
};

typedef uint64_t pt_entry;

struct paging_stats 
{
    uint64_t total_frames;
    uint64_t used_frames;
    uint64_t free_frames;
    uint64_t mapped_pages;
};

void pfa_init_from_multiboot2(void* mb2_structure);
void* pfa_alloc_frame();
void pfa_free_frame(void* frame);
void pfa_mark_used(uintptr_t frame_start, uint64_t frame_count);

void paging_init();
void paging_map_page(void* virt, void* phys, uint64_t flags);
void paging_unmap_page(void* virt);
void* paging_get_physical_address(void* virt);
void paging_identity_map(uintptr_t start, uintptr_t size, uint64_t flags);
void paging_get_stats(struct paging_stats* stats);

#endif      // PAGING_H