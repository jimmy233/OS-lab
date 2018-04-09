#include "x86.h"
#include "device.h"
#include <string.h>
SegDesc gdt[NR_SEGMENTS];
TSS tss;

#define SECTSIZE 512

void waitDisk(void) {
	while((inByte(0x1F7) & 0xC0) != 0x40); 
}

void readSect(void *dst, int offset) {
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

void initSeg() {
	gdt[SEG_KCODE] = SEG(STA_X | STA_R, 0,       0xffffffff, DPL_KERN);
	gdt[SEG_KDATA] = SEG(STA_W,         0,       0xffffffff, DPL_KERN);
	gdt[SEG_UCODE] = SEG(STA_X | STA_R, 0,       0xffffffff, DPL_USER);
	gdt[SEG_UDATA] = SEG(STA_W,         0,       0xffffffff, DPL_USER);
	gdt[SEG_TSS] = SEG16(STS_T32A,      &tss, sizeof(TSS)-1, DPL_KERN);
	gdt[SEG_TSS].s = 0;
	setGdt(gdt, sizeof(gdt));

	/*
	 * 初始化TSS
	 */
	 tss.ss0=0x10;
	 tss.esp0=(128<<10);
	asm volatile("ltr %%ax":: "a" (KSEL(SEG_TSS)));

	/*设置正确的段寄存器*/

	lLdt(0);
	
}

void enterUserSpace(uint32_t entry) {
	/*
	 * Before enter user space 
	 * you should set the right segment registers here
	 * and use 'iret' to jump to ring3
	 */
   	uint32_t eflags=0x2;
	uint16_t cs=8;
	asm volatile("pushl %0"::"m"(eflags));
	asm volatile("pushw %0"::"m"(cs));
	asm volatile("pushl %0"::"m"(entry));
       
	asm volatile("movw %%ax,%%es":: "a" (USEL(SEG_UDATA)));
	asm volatile("movw %%ax,%%ds":: "a" (USEL(SEG_UDATA)));
	asm volatile("iret");
}

void loadUMain(void) {

	/*加载用户程序至内存*/
	unsigned char buf[10240];
       for(int i=0; i<20;i++)
         readSect(buf+i*SECTSIZE,i+201);
      struct ELFHeader *elf=(void*)buf;
      struct ProgramHeader *ph=(void *)elf + elf->phoff;
           int count=elf->phnum;
             while(count--)
              {
	        if(ph->type==1)
		{
	           memcpy((void *)ph->vaddr,buf+ph->off,ph->filesz);
	           memset((void *)ph->vaddr+ph->filesz,0,ph->memsz-ph->filesz);
	       	}
	       //  ph=(void *)ph+elf->phentsize;
	             ph++;
	      }
	      enterUserSpace(elf->entry);

}
