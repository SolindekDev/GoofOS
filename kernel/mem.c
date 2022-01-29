// #########################################################################
//
//  Copyright 2021 SolindekDev
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
// 
// ########################################################################

#include "mem.h"

unsigned int free_mem_addr = 0x10000;

unsigned int malloc(unsigned int size, int align, unsigned int *phys_addr) {
    if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }

    if (phys_addr) *phys_addr = free_mem_addr;

    unsigned int ret = free_mem_addr;
    free_mem_addr += size; 
    return ret;
}