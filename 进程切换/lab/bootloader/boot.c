#include "boot.h"
#include <string.h>
#define SECTSIZE 512
#define SIZE 102400
void bootMain(void) {
	/* 加载内核至内存，并跳转执行 */
	void (*a_nel)(void);
	unsigned char buf[SIZE];
	for(int i=0; i<200;i++)
		readSect(buf+i*SECTSIZE,i+1);
	struct ELFHeader *elf=(void*)buf;
	struct ProgramHeader *ph=(void *)elf + elf->phoff;
     int count=elf->phnum;
     while(count--)
     {     	
         memcpy((void *)ph->vaddr,buf+ph->off,ph->filesz);
	 memset((void *)ph->vaddr+ph->filesz,0,ph->memsz-ph->filesz);
     //	 ph=(void *)ph+elf->phentsize;
	ph++;	
     }
     a_nel=(void *)elf->entry;
     a_nel();
}

void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
