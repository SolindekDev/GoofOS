##########################################################################
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
##########################################################################

# require 'rbconfig'

# $os = "Other"

# def os()
#   @os ||= (
#     host_os = RbConfig::CONFIG['host_os']
#     case host_os
#     when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
#         $os = "Win"
#     when /darwin|mac os/
#         $os = "MacOS"
#     when /linux/
#         $os = "Linux"
#     when /solaris|bsd/
#         $os = "Unix"
#     else
#         $os = "Other"
#     end
#   )
# end

# os()

# class String
#     def black;          "\033[30m#{self}\033[0m" end
#     def red;            "\033[31m#{self}\033[0m" end
#     def green;          "\033[32m#{self}\033[0m" end
#     def brown;          "\033[33m#{self}\033[0m" end
#     def blue;           "\033[34m#{self}\033[0m" end
#     def magenta;        "\033[35m#{self}\033[0m" end
#     def cyan;           "\033[36m#{self}\033[0m" end
#     def gray;           "\033[37m#{self}\033[0m" end
# end

# asm = "nasm"
# gcc = "x86_64-elf-gcc"
# ld = "x86_64-elf-ld"
# cat = "cat"
# qemu = "qemu-system-x86_64"

# gcc_flags = "-ffreestanding -m32 -g -c"
# ld_flags_start = "-m elf_i386 -o kernel.bin -Ttext 0x1000"
# ld_flags_end = "--oformat binary"
# asm_flags_elf = "-f elf"
# asm_flags_bin = "-f bin"
# qemu_flags = "-drive format=raw,file=os.bin -d cpu_reset -monitor stdio -m 1G"

# bootloader_dir = './src/bootloader/'
# kernel_dir = './src/kernel/'

# builder_goof = "Builder Goof"
# builder_goof_builder_boot = "Builder Goof Bootloader"
# builder_goof_builder_kernel = "Builder Goof Kernel"
# builder_goof_builder_ld = "Builder Goof Linked"

# files_asm = Dir.glob(File.join(bootloader_dir, '**', '*.asm')).select{|file| File.file?(file)}
# files_kernel_c = Dir.glob(File.join(kernel_dir, '**', '*.c')).select{|file| File.file?(file)}
# files_kernel_asm = Dir.glob(File.join(kernel_dir, '**', '*.asm')).select{|file| File.file?(file)}

# puts " "
# puts " #{"Goof OS Builder - Written in Ruby".magenta}"
# puts " "

# puts "----------------------------------------------------------"
# puts "[#{builder_goof.magenta}] Compiling bootloader (.asm)..."

# files_asm.each do |f|
#     if f == "./src/bootloader/entering/kernel_entry.asm"
#         system "#{asm} ./src/bootloader/entering/kernel_entry.asm #{asm_flags_elf} -o ./src/bootloader/entering/kernel_entry.o"
#         puts "[#{builder_goof_builder_boot.magenta}] Compiled #{f}"
#     else
#         system "#{asm} #{f} #{asm_flags_bin} -o #{f.gsub(".asm", ".o")}"
#         puts "[#{builder_goof_builder_boot.magenta}] Compiled #{f}"
#     end
# end

# puts "----------------------------------------------------------"

# puts "[#{builder_goof.magenta}] Compiling kernel c files (.c)..."

# files_kernel_c.each do |f|
#     system "#{gcc} #{gcc_flags} #{f} -o #{f.gsub(".c", ".o")}"
#     puts "[#{builder_goof_builder_kernel.magenta}] Compiled #{f}"
# end
# puts "----------------------------------------------------------"
# puts "[#{builder_goof.magenta}] Compiling kernel assembler files (.asm)..."

# files_kernel_asm.each do |f|
#     system "#{asm} #{f} #{asm_flags_elf} -o #{f.gsub(".asm", ".o")}"
#     puts "[#{builder_goof_builder_kernel.magenta}] Compiled #{f}"
# end
# puts "----------------------------------------------------------"
# puts "[#{builder_goof.magenta}] Linking o files (.o)..."

# files = ""

# files_kernel_c.each do |f|
#     files += f.gsub(".c", ".o") + " "
# end
# files_kernel_asm.each do |f|
#     files += f.gsub(".asm", ".o") + " "
# end

# system "#{ld} #{ld_flags_start} ./src/bootloader/entering/kernel_entry.o #{files} #{ld_flags_end}"
# system "#{cat} ./src/bootloader/bootloader.o kernel.bin ./src/bootloader/entering/times.o > os.bin"
# puts "[#{builder_goof_builder_ld.magenta}] Linked kernel. Output in os.bin!"
# puts "----------------------------------------------------------"

# def emulator_is()
#     print "[#{"Builder Goof".magenta}] Do you want to emulate the OS? (Y/N): "
#     y = gets().chomp
#     if y.downcase() == "y" || y.downcase() == "yes"
#         system "qemu-system-x86_64 -drive format=raw,file=os.bin -d cpu_reset -monitor stdio -m 1G"
#         if $os == "Win"
#             system "cls"
#         else
#             system "clear"
#         end
#         puts "----------------------------------------------------------"
#         puts " "
#         puts "                  #{"Stop emulate the OS...".magenta}"
#         puts " "
#         puts "----------------------------------------------------------"
#     elsif y.downcase() == "n" || y.downcase() == "no"
#         puts "[#{"Exit".red}] You don't want to emulate the OS so builder exit.\n"
#         exit 1
#     else
#         puts "[#{"Error".red}] Unknown value. expected (Y/N)"
#         emulator_is()
#     end
# end 

# emulator_is()