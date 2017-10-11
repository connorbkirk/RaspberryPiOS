#include "string.h"

void memcpy(char * d, char * s, int len){
        while(--len){
                *d++ = *s++;
        }
}

void    *memccpy(void * dest, const void * src, int c, size_t n){
	return 0;
}
void    *memchr(const void * str, int c, size_t n){
	return 0;
}
int      memcmp(const void * str1, const void * str2, size_t n){
	return -1;
}
//void    *memcpy(void *, const void *, size_t){}
void    *memmove(void * dest, const void * src, size_t n){
	return 0;
}
void    *memset(void * str, int c, size_t n){
	return 0;
}
char    *strcat(char * dest, const char * src){
	return 0;
}
char    *strchr(const char *str, int c){
	return 0;
}
int      strcmp(const char *str1, const char * str2){
	return 0;
}
int      strcoll(const char *str1, const char *str2){
	return -1;
}
char    *strcpy(char *dest, const char *src){
	return 0;
}
size_t   strcspn(const char *str1, const char *str2){
	return 0;
}
char    *strdup(const char * str){
	return 0;
}
char    *strerror(int errnum){
	return 0;
}
size_t   strlen(const char * str){
	return 0;
}
char    *strncat(char *str1, const char *str2, size_t n){
	return 0;
}
int      strncmp(const char *str1, const char *str2, size_t n){
	return 0;
}
char    *strncpy(char *dest, const char *src, size_t n){
	return 0;
}
char    *strpbrk(const char *str1, const char *str2){
	return 0;
}
char    *strrchr(const char *str, int c){
	return 0;
}
size_t   strspn(const char *str1, const char *str2){
	return 0;
}
char    *strstr(const char *haystack, const char *needle){
	if(!*needle){
        	return 0;
    	}
    
    	int count;
    	char * h = (char*)haystack;
    	char * n;
    
    	while(*h){
        	n = (char*)needle;
        	count = 0;
        
        	while( *n && *(h+count) && *n == *(h+count) ){
           		count++;
           		n++;
        	}
        
        	if(!*n){
            		return h-haystack;
        	}
        
        	h++;
    	}
    	return -1;
}
char    *strtok(char *str, const char *delim){
	return 0;
}
char    *strtok_r(char *str, const char *delim, char **saveptr){
	return 0;
}
size_t   strxfrm(char *dest, const char *src, size_t n){
	return 0;
}
