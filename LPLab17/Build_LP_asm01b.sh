#!/bin/bash
set -e
as -gstabs LP_asm01b.s -o LP_asm01b.o
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 -lc LP_asm01b.o LP_asm01a.a -o LP_asm01b
