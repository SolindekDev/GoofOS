//
//     Copyright 2022 SolindekDev
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "./detect.h"

#include "../utils/ports.h"
#include "./cpuid.h"

#define INTEL_MAGIC_CODE  0x756e6547
#define AMD_MAGIC_CODE    0x68747541

int detect_cpu_type() {
    unsigned long ebx, unused;
	CPUID(0, unused, ebx, unused, unused);

	switch(ebx) {
		case INTEL_MAGIC_CODE:
		    return INTEL;
		break;
		case AMD_MAGIC_CODE:
            return AMD;
		break;
		default:
		    return OTHER;
		break;
	}
}