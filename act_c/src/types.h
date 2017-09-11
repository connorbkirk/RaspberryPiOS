typedef volatile unsigned int vuint32_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define READ32(addr) (*(vuint32_t*)addr)
#define WRITE32(addr, val) (*(vuint32_t*)(addr) = (vuint32_t)(val))
