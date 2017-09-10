#!/usr/bin/env bash

arm-none-eabi-as start.s -o start.o
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c main.c -o main.o -g
arm-none-eabi-ld start.o main.o -T ldscript -o main.elf
arm-none-eabi-objcopy main.elf -O binary kernel.img
