# #########################################################################
#
#  Copyright 2021 SolindekDev
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
# 
# ########################################################################

x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/ports.c -o kernel/ports.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/screen.c -o kernel/screen.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/string.c -o kernel/string.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/util.c -o kernel/util.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/keyboard.c -o kernel/keyboard.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/disk.c -o kernel/disk.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/mem.c -o kernel/mem.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/power.c -o kernel/power.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/fs/gffs/gffs.c -o kernel/fs/gffs/gffs.o

x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/idt.c -o kernel/cpu/idt.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/isr.c -o kernel/cpu/isr.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/timer.c -o kernel/cpu/timer.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/cpu.c -o kernel/cpu/cpu.o

nasm kernel/cpu/interrupt.asm -felf -o kernel/cpu/interrupt.o
nasm kernel/shutdown.asm -felf -o kernel/shutdown.o

x86_64-elf-ld -m elf_i386 -o kernel.bin -Ttext 0x1000 boot/kernel_entry.o kernel/shutdown.o kernel/fs/gffs/gffs.o kernel/mem.o kernel/power.o kernel/kernel.o kernel/cpu/cpu.o kernel/cpu/interrupt.o kernel/disk.o kernel/cpu/idt.o kernel/cpu/isr.o kernel/cpu/timer.o kernel/ports.o kernel/screen.o kernel/keyboard.o kernel/util.o kernel/string.o --oformat binary

cat boot/mbr.bin kernel.bin > os-image.bin

qemu-system-x86_64 -drive format=raw,file=os-image.bin,index=0,if=floppy, -m 1G