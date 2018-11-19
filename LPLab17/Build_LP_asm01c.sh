#!/bin/bash
set -e
g++ -c LP_asm01c.cpp
g++ -lc LP_asm01c.o LP_asm01a.a -o LP_asm01c
