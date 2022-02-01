@REM nasm -f bin boot/mbr.asm -o boot/mbr.bin
@REM nasm -f elf boot/kernel_entry.asm -o boot/kernel_entry.o
nasm boot/bootloader.asm -f bin -o boot/bootloader.o
nasm boot/kernel_entry.asm -f elf -o boot/kernel_entry.o
nasm boot/zeroes.asm -f bin -o boot/zeroes.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/cpu.c -o kernel/cpu/cpu.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/idt.c -o kernel/cpu/idt.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/isr.c -o kernel/cpu/isr.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/cpu/timer.c -o kernel/cpu/timer.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/disk.c -o kernel/disk.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/drivers/io/keyboard.c -o kernel/drivers/io/keyboard.o      
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/drivers/speakers/pcspk.c -o kernel/drivers/speakers/pcspk.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/fs/gffs/gffs.c -o kernel/fs/gffs/gffs.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/kernel.c -o kernel/kernel.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/ports.c -o kernel/ports.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/power.c -o kernel/power.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/screen.c -o kernel/screen.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/string.c -o kernel/string.o
x86_64-elf-gcc -g -m32 -ffreestanding -c kernel/util.c -o kernel/util.o
nasm kernel/cpu/interrupt.asm -f elf -o kernel/cpu/interrupt.o
x86_64-elf-ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel/drivers/speakers/pcspk.o kernel/fs/gffs/gffs.o kernel/kernel.o kernel/ports.o kernel/power.o kernel/screen.o kernel/string.o kernel/util.o boot/kernel_entry.o kernel/cpu/cpu.o kernel/cpu/idt.o kernel/cpu/interrupt.o kernel/cpu/isr.o kernel/cpu/timer.o kernel/disk.o kernel/drivers/io/keyboard.o --oformat binary
@REM x86_64-elf-ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel2.bin--oformat binary
@REM cat boot/mbr.bin kernel.bin > os-image.bin
cat boot/bootloader.o , kernel.bin , boot/zeroes.o > os-image.bin
qemu-system-x86_64 -drive format=raw,file=os-image.bin,index=0,if=floppy, -d cpu_reset -m 2G -soundhw pcspk
rm kernel.bin