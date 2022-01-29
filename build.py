import os

os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/ports.c -o kernel/ports.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/screen.c -o kernel/screen.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/string.c -o kernel/string.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/util.c -o kernel/util.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/keyboard.c -o kernel/keyboard.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/disk.c -o kernel/disk.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/mem.c -o kernel/mem.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/power.c -o kernel/power.o")

os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/idt.c -o kernel/cpu/idt.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/isr.c -o kernel/cpu/isr.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/timer.c -o kernel/cpu/timer.o")
os.system("x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/cpu.c -o kernel/cpu/cpu.o")

os.system("nasm kernel/cpu/interrupt.asm -felf -o kernel/cpu/interrupt.o")
os.system("nasm kernel/shutdown.asm -felf -o kernel/shutdown.o")

os.system("x86_64-elf-ld -m elf_i386 -o kernel.bin -Ttext 0x1000 boot/kernel_entry.o kernel/shutdown.o kernel/mem.o kernel/power.o kernel/kernel.o kernel/cpu/cpu.o kernel/cpu/interrupt.o kernel/disk.o kernel/cpu/idt.o kernel/cpu/isr.o kernel/cpu/timer.o kernel/ports.o kernel/screen.o kernel/keyboard.o kernel/util.o kernel/string.o --oformat binary")

os.system("cat boot/mbr.bin kernel.bin > os-image.bin")

os.system("qemu-system-x86_64 -drive format=raw,file=os-image.bin,index=0,if=floppy, -m 1G")