; #########################################################################
;
;  Copyright 2021 SolindekDev
;
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
;  Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.
; 
; ########################################################################

; Shutdown not works...

global sht
; sht:
;     cli
;     sti
;     mov ax, 0x1000
;     mov ax, ss
;     mov sp, 0xf000
;     mov ax, 0x5307
;     mov bx, 0x0001
;     mov cx, 0x0003
;     int 0x15
sht:
  cli
  mov ax, 5301h             ; Connect to the APM
  xor bx, bx
  int 15h
  je near continue_connection       ; Pass if connected
  cmp ah, 2
  je near continue_connection       ; Pass if already connected
  ret               ; Bail if fail

continue_connection:
  mov ax, 530Eh             ; Check APM Version
  xor bx, bx
  mov cx, 0102h             ; v1.2 Required
  int 15h
  ret      