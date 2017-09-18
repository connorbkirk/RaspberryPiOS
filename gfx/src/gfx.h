/**********************************************************
 FRAME BUFFER
 *********************************************************/
typedef struct __attribute__((__packed__, aligned(1))) RGBA {
        uint8_t B;
        uint8_t G;
        uint8_t R;
        uint8_t A;
} RGBA;

typedef struct FrameBuffer{
        uint32_t        buffer;         //frame buffer address
        int32_t         width;          //phys width
        int32_t         height;         //phys height
        int32_t         depth;          //color depth
        uintptr_t       bitfont;        //bitmap font
        int32_t         fontWth;        //font width
        int32_t         fontHt;         //font height
        RGBA            fontColor;      //font color
        RGBA            bgColor;        //background color
        int32_t         clipMinX;
        int32_t         clipMaxX;
        int32_t         clipMinY;
        int32_t         clipMaxY;

        void(*write_char) (struct FrameBuffer * self, uint32_t x1, uint32_t y1, uint8_t ch);
} FrameBuffer;

bool console_init();
void console_write(char ch);
