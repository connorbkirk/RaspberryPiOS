#ifndef TYPES_H
#define TYPES_H

#define NULL 0

#include <stdint.h>
#include <stdbool.h>

typedef volatile unsigned int vuint32_t;
typedef uint32_t size_t;

#define READ32(addr) (*(vuint32_t*)addr)
#define WRITE32(addr, val) (*(vuint32_t*)(addr) = (vuint32_t)(val))

#endif
