/*
 * keonOS - kernel/syscalls/sys_file.cpp
 * Copyright (C) 2025-2026 fmdxp
 */

#include <kernel/syscalls/syscalls.h>
#include <kernel/arch/x86_64/thread.h>
#include <drivers/keyboard.h>
#include <mm/heap.h>
#include <fs/vfs.h>
#include <stdio.h>
#include <drivers/serial.h>

uint64_t sys_read(uint64_t fd, uint64_t buf, uint64_t size, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a4; (void)a5; (void)a6;
    if (fd == STDIN) 
    {
        char kbuf[256];
        if (size > sizeof(kbuf)) size = sizeof(kbuf);
        size_t bytes_read = 0;
        
        while (bytes_read < size)
        {
            char c = 0;
            if (keyboard_has_input()) c = keyboard_getchar();
            else if (serial_received()) c = serial_getc();
            
            if (c == 0) 
            {
                if (bytes_read > 0) break; // Return what we have
                
                // If we have nothing, block and wait
                thread_get_current()->state = THREAD_BLOCKED;
                yield();
                continue;
            }
            
            kbuf[bytes_read++] = c;
            if (c == '\n') break;
        }

        if (bytes_read > 0)
        {
            if (!copy_to_user((void*)buf, kbuf, bytes_read)) return -1;
        }
        
        return bytes_read;
    }

    thread_t* current = thread_get_current();
    if (fd >= 16 || !current->fd_table[fd]) return -1;

    uint8_t* kbuf = (uint8_t*)kmalloc(size);
    if (!kbuf) return -1;

    uint32_t bytes_read = vfs_read(current->fd_table[fd], current->fd_offset[fd], size, kbuf);
    if (bytes_read > 0) 
    {
        if (!copy_to_user((void*)buf, kbuf, bytes_read)) 
        {
            kfree(kbuf);
            return -1;
        }
        current->fd_offset[fd] += bytes_read;
    }
    kfree(kbuf);
    return bytes_read;
}

uint64_t sys_write(uint64_t fd, uint64_t buf, uint64_t size, uint64_t a4, uint64_t a5, uint64_t a6) 
{    
    (void)a4; (void)a5; (void)a6;
    if (fd == STDOUT || fd == STDERR) 
    {
        char kbuf[256];
        if (size > sizeof(kbuf)) size = sizeof(kbuf);
        if (!copy_from_user(kbuf, (const void*)buf, size)) return -1;

        for (size_t i = 0; i < size; i++) putchar(kbuf[i]);
        return size;
    }

    thread_t* current = thread_get_current();
    if (fd >= 16 || !current->fd_table[fd]) return -1;

    uint8_t* kbuf = (uint8_t*)kmalloc(size);
    if (!kbuf) return -1;

    if (!copy_from_user(kbuf, (const void*)buf, size)) 
    {
        kfree(kbuf);
        return -1;
    }

    uint32_t bytes_written = vfs_write(current->fd_table[fd], current->fd_offset[fd], size, kbuf);
    current->fd_offset[fd] += bytes_written;
    kfree(kbuf);
    return bytes_written;
}

uint64_t sys_open(uint64_t path_ptr, uint64_t flags, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a3; (void)a4; (void)a5; (void)a6;
    char path[256];
    if (!copy_from_user(path, (const void*)path_ptr, 255)) return -1;
    path[255] = '\0';

    VFSNode* node = vfs_open(path);
    if (!node && (flags & 1)) // 1 = O_CREAT (simulated)
        node = vfs_create(path, flags);

    if (!node) return -1;

    thread_t* current = thread_get_current();
    for (int i = 3; i < 16; i++) 
    {
        if (current->fd_table[i] == nullptr) 
        {
            current->fd_table[i] = node;
            current->fd_offset[i] = 0;
            return i;
        }
    }
    vfs_close(node);
    return -1;
}

uint64_t sys_close(uint64_t fd, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    thread_t* current = thread_get_current();
    if (fd < 3 || fd >= 16 || !current->fd_table[fd]) return -1;

    vfs_close(current->fd_table[fd]);
    current->fd_table[fd] = nullptr;
    current->fd_offset[fd] = 0;
    return 0;
}

uint64_t sys_mkdir(uint64_t path_ptr, uint64_t mode, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a3; (void)a4; (void)a5; (void)a6;
    char path[256];
    if (!copy_from_user(path, (const void*)path_ptr, 255)) return -1;
    path[255] = '\0';

    return vfs_mkdir(path, (uint32_t)mode);
}

uint64_t sys_readdir(uint64_t fd, uint64_t index, uint64_t dirent_ptr, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a4; (void)a5; (void)a6;
    thread_t* current = thread_get_current();
    if (fd >= 16 || !current->fd_table[fd]) return -1;

    vfs_dirent* de = vfs_readdir(current->fd_table[fd], (uint32_t)index);
    if (!de) return 0;

    if (!copy_to_user((void*)dirent_ptr, de, sizeof(vfs_dirent))) return -1;
    return 1;
}

uint64_t sys_unlink(uint64_t path_ptr, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5, uint64_t a6) 
{
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    char path[256];
    if (!copy_from_user(path, (const void*)path_ptr, 255)) return -1;
    path[255] = '\0';

    return vfs_unlink(path) ? 0 : -1;
}