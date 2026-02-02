/*
 * keonOS - kernel/syscalls/sys_vga.cpp
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

#include <kernel/syscalls/syscalls.h>
#include <drivers/vga.h>
#include <stdint.h>

uint64_t sys_vga(uint64_t cmd, uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5) 
{
    (void)a3; (void)a4; (void)a5;
    
    switch (cmd) 
    {
        case 0: // clear
            terminal_clear();
            return 0;
        
        case 1: // set color
            terminal_setcolor(vga_color_t((uint8_t)a1, (uint8_t)a2));
            return 0;
        
        case 2: // set cursor
            update_cursor((size_t)a1, (size_t)a2);
            return 0;
            
        default:
            return -1;
    }
}
