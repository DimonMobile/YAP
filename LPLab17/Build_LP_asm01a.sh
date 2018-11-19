#!/bin/bash
set -e
as  LP_asm01a.s -o LP_asm01a.o
ar -rcs LP_asm01a.a LP_asm01a.o
