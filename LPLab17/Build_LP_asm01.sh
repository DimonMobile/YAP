#!/bin/bash

set -e
as --gstabs LP_asm01.s -o LP_asm01.o
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc LP_asm01.o -o LP_asm01
./LP_asm01