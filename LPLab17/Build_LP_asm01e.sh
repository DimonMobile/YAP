#!/bin/bash

set -e
as -gstabs LP_asm01e.s -o LP_asm01e.o
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc LP_asm01e.o LP_asm01d.a -o LP_asm01e
