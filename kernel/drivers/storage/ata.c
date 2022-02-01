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

/*
    ATA driver

    It helped me a lot:
        - https://wiki.osdev.org/AHCI
        - https://github.com/SerenityOS/serenity/tree/33b78915d377dfb950d93f150b8470aea2c1e66f/Kernel/Storage/ATA
        - https://github.com/torvalds/linux/blob/master/drivers/ata/ahci.c
        - https://github.com/haiku/haiku/tree/master/src/add-ons/kernel/busses/scsi/ahci
        - https://github.com/rajesh5310/SBUnix/blob/master/sys/ahci.c
*/

#include "./ata.h"

#include "../../ports.h"

/* Soon */