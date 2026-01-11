/*
 * keonOS - fs/ramfs_vfs.cpp
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
#include <fs/ramfs_vfs.h>
#include <fs/vfs_node.h>
#include <fs/ramfs.h>
#include <stdio.h>

KeonFS_File::KeonFS_File(const char* n, uint32_t s, void* ptr) 
{
    strncpy(this->name, n, 127);
    this->name[127] = '\0';
    this->size = s;
    this->data_ptr = ptr;
    this->type = VFS_FILE;
}

void KeonFS_MountNode::add_child(VFSNode* node) 
{
    if (children_count >= 128) 
        panic(KernelError::K_ERR_GENERAL_PROTECTION, "Too many files in ramfs");
    children[children_count] = node;

    printf("[DEBUG] Added child: %s, type=%d\n", node->name, node->type);
    if (node->type == VFS_FILE)
        printf("[DEBUG]   size=%d, data_ptr=%x\n", ((KeonFS_File*)node)->size, ((KeonFS_File*)node)->data_ptr);

    children_count++;
}


uint32_t KeonFS_File::read(uint32_t offset, uint32_t size, uint8_t* buffer) 
{
    if (offset >= this->size) 
        return 0;
    
    uint32_t to_read = (offset + size > this->size) ? (this->size - offset) : size;
    memcpy(buffer, (uint8_t*)data_ptr + offset, to_read);
    return to_read;
}


VFSNode* KeonFS_MountNode::finddir(const char* name) 
{
    for (uint32_t i = 0; i < children_count; i++) 
    {
        if (strcmp(children[i]->name, name) == 0)
            return children[i];
    }
    return nullptr;
}

void KeonFS_File::open() {}
void KeonFS_File::close() {}

vfs_dirent* KeonFS_MountNode::readdir(uint32_t index) 
{
    if (index >= children_count) return nullptr;
    static vfs_dirent de;
    strcpy(de.name, children[index]->name);
    de.inode = index;
    return &de;
}

uint32_t KeonFS_MountNode::read(uint32_t, uint32_t, uint8_t*) 
{ 
    return 0;
}