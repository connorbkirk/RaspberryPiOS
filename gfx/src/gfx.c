#include "types.h"
#include "mailbox.h"
#include "Font8x16.h"
#include "gfx.h"

typedef struct ConsoleData_t{
	int32_t x;		//cursor column
	int32_t y;		//cursor row
	FrameBuffer fb;
} ConsoleData_t;

ConsoleData_t console; 

void memcpy(uint8_t * d, uint8_t * s, uint32_t len){
	while(--len){
		*d++ = *s++;
	}
}

void write_char_32(FrameBuffer * fb, uint32_t x1, uint32_t y1, uint8_t ch){
	RGBA * __attribute__((aligned(4))) video_wr_ptr = (RGBA*)(uintptr_t)(fb->buffer + y1*fb->width*4 + x1*4);
	int y;
	int i;
	for(y = 0; y < 4; y++){
		uint32_t b = BitFont[ 4*ch + y ];
		for(i = 0; i < 32; i++){
			RGBA col = fb->bgColor;
			
			int xoffs = i % 8;
			if((b & 0x80000000) != 0){
				col = fb->fontColor;
			}
			
			video_wr_ptr[xoffs] = col;

			b <<= 1;
			if(xoffs == 7){
				video_wr_ptr += fb->width;
			}
		}
	}
}

bool allocFrameBuffer(int32_t width, int32_t height, int32_t depth, FrameBuffer * fb){
	uint32_t __attribute__((aligned(16))) message[22];
	if(!fb){
		return false;
	}

	fb->width = width;
	fb->height = height;
	fb->depth = depth;
	fb->clipMinX = 0;
	fb->clipMaxX = width;
	fb->clipMinY = 0;
	fb->clipMaxY = height;
	fb->fontColor = (RGBA){ .R = 0xFF, .G = 0xFF, .B = 0xFF, .A = 0xFF };
	fb->bgColor = (RGBA){ .R = 0x00, .G = 0x00, .B = 0x00, .A = 0x00 };

	message[0] = sizeof(message);
	message[1] = 0;					//request
	message[2] = MB_TAG_SET_PHYSICAL_WIDTH_HEIGHT;	//set phys size
	message[3] = 8;					//value buffer size in bytes
	message[4] = 8;					//request + value length in bytes
	message[5] = width;				//
	message[6] = height;				//
	message[7] = MB_TAG_SET_VIRTUAL_WIDTH_HEIGHT;	//set virtual size
	message[8] = 8;					//value buffer size in bytes
	message[9] = 8;					//request + value length in bytes
	message[10] = width;				//
	message[11] = height;				//
	message[12] = MB_TAG_SET_COLOUR_DEPTH;		//set depth
	message[13] = 4;				//value buffer size in bytes
	message[14] = 4;				//request + value length in bytes
	message[15] = depth;				//
	message[16] = MB_TAG_ALLOCATE_FRAMEBUFFER;	//allocate frame buffer
	message[17] = 8;				//value buffer size in bytes
	message[18] = 4;				//request + value length in bytes
	message[19] = 16;				//alignment = 16
	message[20] = 0;				//response
	message[21] = 0;				//end

	mailbox_write(message, MB_CH_TAGS);
	mailbox_read(MB_CH_TAGS);
	
	if((message[1] != 0x80000000) || (message[18] != 0x80000008)){
		return false;
	}

	fb->buffer = (message[19] & ~(0xC0000000));
	fb->size = message[20];
	
	fb->bitfont = (uintptr_t)&BitFont[0];
	fb->fontWth = 8;
	fb->fontHt = 16;

	fb->write_char = write_char_32;

	return true;
}

bool console_init(){
	uint32_t __attribute__((aligned(16))) message[8];
	uint32_t width, height, depth;

	message[0] = sizeof(message);
	message[1] = 0;
	message[2] = MB_TAG_GET_PHYSICAL_WIDTH_HEIGHT;
	message[3] = 8;
	message[4] = 0;
	message[5] = 0;
	message[6] = 0;
	message[7] = 0;

	mailbox_write(message, MB_CH_TAGS);
	mailbox_read(MB_CH_TAGS);

	width = message[5];
	height = message[6];	
	
	if(height == 0 || width == 0){
		height = 1024;
		width = 640;
	}

	depth = 32;
	
	if( !allocFrameBuffer(width, height, depth, &console.fb) ){
		return false;
	}

	console.x = 0;
	console.y = 0;

	return true;
}

void console_write(char ch){
	switch(ch){
		case '\r':{
			console.x = 0;
			break;
		}

		case '\n':{
			console.x = 0;
			console.y++;
			break;
		}
	
		default:{
			int x = console.x * console.fb.fontWth;
			int y = console.y * console.fb.fontHt;
			console.fb.write_char(&console.fb, x, y, ch);
			console.x++;
			break;
		}
	}
}

void console_test(){
	int i;
	for(i = 0; i < console.fb.size; i+=4){
		*(vuint32_t *)(console.fb.buffer + i) = 0xFFFF;
	}
}

