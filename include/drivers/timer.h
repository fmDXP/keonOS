/*
 * keonOS - include/drivers/timer.h
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


#ifndef TIMER_H
#define TIMER_H

#include <kernel/constants.h>
#include <stdint.h>


bool timer_init(uint32_t frequency);
extern "C" void timer_handler();  
uint32_t timer_get_ticks();
void timer_sleep(uint32_t milliseconds);

#endif		// TIMER_H