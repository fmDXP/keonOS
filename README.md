# keonOS 🚀

A monolithic 32-bit x86 operating system built from scratch in C++ and Assembly.

---

## 🏗️ Architecture & Core Features

### 🧠 Advanced Memory Management
- **Higher Half Kernel:** The kernel sits now at `0xC0000000`, neatly separating the kernel addresses with the user ones (for future development).
- **Boot-time Paging:** Implemented a log of bootstrapping in Assembly to map critical pages before going to the Higher Half.
- **Custom VMM & PFA:** Advance management of physical frames and of virtual addressed with support of recorsive mapping.
- **Kernel Heap:** Fully functional dynamic memory management with support for `kmalloc`, `kfree`, and C++ `new`/`delete` operators.

### 🎭 Multitasking & Scheduling
- **Cooperative Multitasking:** Round-robin scheduler handling multiple kernel threads.
- **Process Control:** Built-in support for process listing (`ps`) and thread termination (`pkill`).
- **Post-Mortem Debugging:** Advanced **Kernel Panic** system that captures CPU registers and performs a full stack hex-dump upon failure.

### 💻 Interactive Shell
- **User Interface:** A custom shell with advanced features:
  - **Command History:** Navigate previous commands with Up/Down arrows.
  - **Tab-Completion:** Quick command execution.
  - **System Diagnostics:** Real-time stats for paging, heap, and uptime.

### 🔌 Hardware Drivers
- **VGA:** Text mode driver with custom color schemas.
- **Keyboard:** Interrupt-based driver with scancode-to-ASCII mapping.
- **PIT & CMOS:** Programmable Interval Timer for system ticks and timing.
- **PC Speaker:** Frequency-based audio feedback.

### 📂 Virtual File System (VFS) & Storage
- **Unified VFS Layer:** An abstract interface that allows the system to interact with different file systems via standard operations like `vfs_open`, `vfs_read`, and `vfs_readdir`.
- **KeonFS (Ramdisk):** A custom RAM-based file system loaded as a Multiboot module. It supports packed file headers and linear scanning for fast resource access during boot.
- **Mount System:** Support for mounting multiple file systems under a virtual root (`/`), enabling structured access to system resources (e.g., `/initrd`).

### 📚 Standard Library (LibC)
- **File I/O:** Implementation of standard C functions such as `fopen`, `fread`, `fclose`, and `fseek` to bridge the gap between user-level logic and the VFS.
- **String Manipulation:** A growing suite of memory and string functions (`memcpy`, `memset`, `strcmp`, `strcpy`) optimized for kernel performance.

---

## 🛠️ Build & Development

### Prerequisites
You will need an `i686-elf` cross-compiler toolchain, `nasm`, and `qemu`.

### Tooling
- **Ramdisk Packer:** Includes a custom Python script (`scripts/pack_keonfs.py`) that automatically bundles assets into a KeonFS image during the build process.

### Compilation
```bash
make        # Compiles the kernel
make iso    # Creates the ISO
make run    # Boots the OS in QEMU
```

All-in-one command:
```bash
make && make iso && make run
```

There's also 
```bash
make clean  # Cleans all the object files, the ISO and the logs (qemu.log)
```

## 📝 License

**keonOS** is licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)** license.

Copyright (c) 2024-2026 fmDXP/fmdxp (keonOS Developer)

You are free to:

- **Share** - copy and redistribute the material in any medium or format.
- **Adapt** - remix, transform, and build upon the material.

Under the following terms:

1. **Attribution** - You must give appropriate credit, provide a link to the original repository, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
2. **NonCommercial** - You may not use the material for commercial purposes or business ventures.
3. **ShareAlike** - If you remix, transform, or build upon the material, you must distribute your contributions under the same license.
4. **No Rebranding for Distribution** - You may not rebrand KeonOS or distribute it under a different name for purposes other than personal educational research.

The software is provided "AS IS", without warranty of any kind.
For full license text, visit: [CC BY-NC-SA 4.0](http://creativecommons.org/licenses/by-nc-sa/4.0/)
