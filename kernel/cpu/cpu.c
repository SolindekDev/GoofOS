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

#include "./cpu.h"

#include "../ports.h"
#include "../string.h"

#define INTEL_MAGIC_CODE  0x756e6547 /* magic codes for intel */
#define AMD_MAGIC_CODE    0x68747541 /* magic codes for amd */

// unsigned long long int cpu_speed() {
// 	static unsigned long long int speed = 0;
// 	if(!speed){
// 		outb(0x43,0x34);
// 		outb(0x40,0);
// 		outb(0x40,0);
// 		unsigned long long int start = rdtsc();
// 		for (volatile int i=0x10000;i>0;i--) (void)i;
// 		outb(0x43,0x04);
// 		unsigned long long int end=rdtsc();
// 		unsigned char lo=inb(0x40);
// 		unsigned char hi=inb(0x40);
// 		unsigned int ticks=(0x10000 - (hi*256+lo));
// 		speed = (end-start)*1193180 / ticks;
// 	}
// 	return speed;
// }

void cpuid(int in, unsigned long a, unsigned long b, unsigned long c, unsigned long d) {
	__asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
}

unsigned long detect_cpu_type_raw() {
    unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);

	return ebx;
}

void processor_halt()
{
    for (;;) {
        asm volatile("cli; hlt");
    }
}

char* detect_cpu_type() {
    unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);

	switch(ebx) {
		case INTEL_MAGIC_CODE:
		    return "Intel";
		break;
		case AMD_MAGIC_CODE:
            return "AMD";
		break;
		default:
		    return "Other";
		break;
	}
}

