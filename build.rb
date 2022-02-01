# #########################################################################
#
#   Copyright 2021 SolindekDev
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ########################################################################

require 'rbconfig'

$os = "Other"

def os()
  @os ||= (
    host_os = RbConfig::CONFIG['host_os']
    case host_os
    when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
        $os = "Win"
    when /darwin|mac os/
        $os = "MacOS"
    when /linux/
        $os = "Linux"
    when /solaris|bsd/
        $os = "Unix"
    else
        $os = "Other"
    end
  )
end

os()

class String
    def black;          "\033[30m#{self}\033[0m" end
    def red;            "\033[31m#{self}\033[0m" end
    def green;          "\033[32m#{self}\033[0m" end
    def brown;          "\033[33m#{self}\033[0m" end
    def blue;           "\033[34m#{self}\033[0m" end
    def magenta;        "\033[35m#{self}\033[0m" end
    def cyan;           "\033[36m#{self}\033[0m" end
    def gray;           "\033[37m#{self}\033[0m" end
end

$script = ""

def add(string_add)
    $script += string_add + "\n"
end

asm = "nasm"
gcc = "x86_64-elf-gcc"
ld = "x86_64-elf-ld"

gcc_flags = "-g -m32 -ffreestanding -c"
ld_flags_start = "-m elf_i386 -o kernel.bin -Ttext 0x1000"
ld_flags_end = "--oformat binary"

bootloader_dir = 'boot/'
kernel_dir = 'kernel/'

["boot/mbr.asm", "boot/kernel_entry.asm"].each do |file|
    if file == "boot/kernel_entry.asm"
        add "nasm -f elf boot/kernel_entry.asm -o boot/kernel_entry.o"
    else
        add "nasm -f bin boot/mbr.asm -o boot/mbr.bin"
    end
end

Dir.glob(File.join(kernel_dir, '**', '*.c')).select{|file| File.file?(file)}.each do |file|
    add "#{gcc} #{gcc_flags} #{file} -o #{file.gsub(".c", ".o")}"
end

Dir.glob(File.join(kernel_dir, '**', '*.asm')).select{|file| File.file?(file)}.each do |file|
    add "#{asm} #{file} -f elf -o #{file.gsub(".asm", ".o")}"
end

add "#{ld} #{ld_flags_start} #{Dir.glob(File.join(kernel_dir, '**', '*.o')).select{|file| File.file?(file)}.join(" ")} boot/kernel_entry.o #{ld_flags_end}"

add "cat boot/mbr.bin kernel.bin > os-image.bin"
add "qemu-system-x86_64 -drive format=raw,file=os-image.bin,index=0,if=floppy, -d cpu_reset -m 2G -soundhw pcspk"

puts $script

# if $os == "Win"
#     File.open("scripts/run.bat", "w") do |line|
#         line.puts $script
#     end
#     system "./scripts/run.bat"
# else
#     File.open("scripts/run.sh", "w") do |line|
#         line.puts $script
#     end
#     system "./scripts/run.sh"
# end

