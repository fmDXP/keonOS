/*
 * keonOS - fs/vfs.cpp
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


#include <fs/vfs_node.h>
#include <fs/vfs.h>
#include <mm/heap.h>
#include <stdio.h>

static uint8_t rootfs_buffer[sizeof(RootFS)]; 
VFSNode* vfs_root = nullptr;

static const char* skip_slashes(const char* path) 
{
    while (*path == '/') path++;
    return path;
}

void vfs_init() 
{
    vfs_root = new (rootfs_buffer) RootFS();
}

void vfs_mount(VFSNode* node) 
{
    if (!vfs_root || !node) return;

    printf("[DEBUG] vfs_root addr: %x\n", vfs_root);
    printf("[DEBUG] vfs_root vptr: %x\n", *(uint32_t*)vfs_root);

    ((RootFS*)vfs_root)->register_node(node);
}

VFSNode* vfs_open(const char* path) 
{
    if (!vfs_root || !path || path[0] != '/') return nullptr;

    VFSNode* current = vfs_root;
    const char* p = skip_slashes(path);

    if (*p == '\0') return vfs_root;

    char component[128];
    while (*p != '\0') 
	{
        uint32_t i = 0;
        while (*p != '/' && *p != '\0' && i < 127) component[i++] = *p++;
        component[i] = '\0';

        VFSNode* next = current->finddir(component);
        if (!next) return nullptr;
        
        current = next;
        p = skip_slashes(p);
    }

    current->open();
    return current;
}

uint32_t vfs_read(VFSNode* node, uint32_t offset, uint32_t size, uint8_t* buffer) 
{
    return (node) ? node->read(offset, size, buffer) : 0;
}

uint32_t vfs_write(VFSNode* node, uint32_t offset, uint32_t size, uint8_t* buffer) 
{
    return (node) ? node->write(offset, size, buffer) : 0;
}

vfs_dirent* vfs_readdir(VFSNode* node, uint32_t index) 
{
    return (node) ? node->readdir(index) : nullptr;
}

void vfs_close(VFSNode* node) 
{
    if (node) node->close();
}