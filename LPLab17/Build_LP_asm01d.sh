#!/bin/bash

set -e
g++ -c LP_asm01d.cpp
ar -rcs LP_asm01d.a LP_asm01d.o
