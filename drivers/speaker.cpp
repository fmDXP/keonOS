/*
 * keonOS - drivers/speaker.cpp
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
#include <drivers/timer.h>

static void play_sound(uint32_t nFrequence) 
{
    if (nFrequence == 0) return;

    uint32_t Div = 1193180 / nFrequence;

    outb(0x43, 0xB6);
    outb(0x42, (uint8_t) (Div) );
    outb(0x42, (uint8_t) (Div >> 8));

    uint8_t tmp = inb(0x61);
    if (tmp != (tmp | 3))
        outb(0x61, tmp | 3);
}

static void nosound() 
{
    uint8_t tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

void beep(uint32_t frequency, uint32_t duration_ms) 
{
    play_sound(frequency);
    timer_sleep(duration_ms);
    nosound();
}