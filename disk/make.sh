#!/usr/bin/env bash

mkdir build
arm-none-eabi-as src/start.s -o build/start.o
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/main.c -o build/main.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/act.c -o build/act.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/mailbox.c -o build/mailbox.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/gfx.c -o build/gfx.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/time.c -o build/time.o -g
arm-none-eabi-gcc -Wall -Werror -nostdlib -nostartfiles -ffreestanding -c src/lib/string.c -o build/string.o -g
arm-none-eabi-ld build/start.o build/main.o build/act.o build/mailbox.o build/gfx.o build/time.o build/string.o -T ldscript -o main.elf
arm-none-eabi-objcopy main.elf -O binary kernel.img
