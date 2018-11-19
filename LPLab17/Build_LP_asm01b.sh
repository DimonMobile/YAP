#!/bin/bash
set -e

as --gstabs LP_asm01b.s -o LP_asm01b.o
ld LP_asm01b.o LP_asm01a.a -o LP_asm01b
