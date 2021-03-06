#!/usr/bin/env bash

mkdir build
arm-none-eabi-as src/start.s -o build/start.o
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/main.c -o build/main.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/act.c -o build/act.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/mailbox.c -o build/mailbox.o -g
arm-none-eabi-ld build/start.o build/main.o build/act.o build/mailbox.o -T ldscript -o main.elf
arm-none-eabi-objcopy main.elf -O binary kernel.img
