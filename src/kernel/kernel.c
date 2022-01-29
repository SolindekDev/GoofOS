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

#include "./kernel.h"

#include "./screen/video.h"
#include "./cpu/detect.h"
#include "./cpu/cpuid.h"
#include "./utils/ports.h"
#include "./utils/string.h"

void KERNEL_ENTRY() {
    // clear_screen();
	kprint("Hello, world!");
    return;
}