typedef volatile unsigned int vuint32_t;

#define READ32(addr) (*(vuint32_t*)addr)
#define WRITE32(addr, val) (*(vuint32_t*)(addr) = (vuint32_t)(val))
