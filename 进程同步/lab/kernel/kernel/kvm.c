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
	 tss.ss0=KSEL(SEG_KDATA);
	 tss.esp0=0x200000;
	asm volatile("ltr %0":: "r" ((uint16_t)KSEL(SEG_TSS)));

	/*设置正确的段寄存器*/
	asm volatile("movw %%ax,%%es"::"a"(KSEL(SEG_KDATA)));
	asm volatile("movw %%ax,%%ds"::"a"(KSEL(SEG_KDATA)));
	asm volatile("movw %%ax,%%ss"::"a"(KSEL(SEG_KDATA)));
	lLdt(0);
	
}
//static PDE kpdir[NR_PDE] align_to_page;						// kernel page directory
//static PTE kptable[PHY_MEM / PAGE_SIZE] align_to_page;		// kernel page tables

//PDE* get_kpdir() { return kpdir; }

/* set up page tables for kernel */
/*void init_page(void) {
	CR0 cr0;
	CR3 cr3;
	PDE *pdir = (PDE *)va_to_pa(kpdir);
	PTE *ptable = (PTE *)va_to_pa(kptable);
	uint32_t pdir_idx;

	 make all PDEs invalid 
	memset(pdir, 0, NR_PDE * sizeof(PDE));

	 fill PDEs 
	for (pdir_idx = 0; pdir_idx < PHY_MEM / PT_SIZE; pdir_idx ++) {
		pdir[pdir_idx].val = make_pde(ptable);
		pdir[pdir_idx + KOFFSET / PT_SIZE].val = make_pde(ptable);

		ptable += NR_PTE;
	}

	 fill PTEs 

	 We use inline assembly here to fill PTEs for efficiency.
	 * If you do not understand it, refer to the C code below.
	 

	asm volatile ("std;\
	 1: stosl;\
		subl %0, %%eax;\
		jge 1b;\
		cld" : :
		"i"(PAGE_SIZE), "a"((PHY_MEM - PAGE_SIZE) | 0x7), "D"(ptable - 1));


	
		===== referenced code for the inline assembly above =====

		uint32_t pframe_addr = PHY_MEM - PAGE_SIZE;
		ptable --;

		// fill PTEs reversely
		for (; pframe_addr >= 0; pframe_addr -= PAGE_SIZE) {
			ptable->val = make_pte(pframe_addr);
			ptable --;
		}
	


	 make CR3 to be the entry of page directory 
	cr3.val = 0;
	cr3.page_directory_base = ((uint32_t)pdir) >> 12;
	write_cr3(cr3.val);

	 set PG bit in CR0 to enable paging 
	cr0.val = read_cr0();
	cr0.paging = 1;
	write_cr0(cr0.val);
}
*/
/* GDT in the kernel's memory, whose virtual memory is greater than 0xC0000000. */
/*static SegDesc gdt[NR_SEGMENTS];

static void
set_segment(SegDesc *ptr, uint32_t pl, uint32_t type) {
	ptr->limit_15_0  = 0xFFFF;
	ptr->base_15_0   = 0x0;
	ptr->base_23_16  = 0x0;
	ptr->type = type;
	ptr->segment_type = 1;
	ptr->privilege_level = pl;
	ptr->present = 1;
	ptr->limit_19_16 = 0xF;
	ptr->soft_use = 0;
	ptr->operation_size = 0;
	ptr->pad0 = 1;
	ptr->granularity = 1;
	ptr->base_31_24  = 0x0;
}

 This is similar with the one in start.S. However the previous one
 * cannot be accessed in user process, because its virtual address is
 * below 0xC0000000, and is not in the user process' address space. 
void
init_segment(void) {
	memset(gdt, 0, sizeof(gdt));
	set_segment(&gdt[SEG_KERNEL_CODE], DPL_KERNEL, SEG_EXECUTABLE | SEG_READABLE);
	set_segment(&gdt[SEG_KERNEL_DATA], DPL_KERNEL, SEG_WRITABLE );

	write_gdtr(gdt, sizeof(gdt));
}
*/
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
	           memcpy((void *)ph->vaddr+0x200000,buf+ph->off,ph->filesz);
	           memset((void *)ph->vaddr+ph->filesz+0x200000,0,ph->memsz-ph->filesz);
	       	}
	       //  ph=(void *)ph+elf->phentsize;
	             ph++;
	      }
	     // enterUserSpace(elf->entry);
             
	ProcessTable *thenew=newp();
	thenew->state=TASK_RUNNING;
	thenew->sp.ss=USEL(SEG_UDATA);
	thenew->sp.esp=0x100000;
	thenew->sp.eflags=0x00202;
	thenew->sp.cs=USEL(SEG_UCODE);
	thenew->sp.ds=USEL(SEG_UDATA);
	thenew->sp.es=USEL(SEG_UDATA);
	thenew->sp.fs=USEL(SEG_UDATA);
	thenew->sp.gs=USEL(SEG_UDATA);
	     gdt[SEG_UCODE]=SEG(STA_X|STA_R,0x200000,0xffffffff,DPL_USER);
	     gdt[SEG_UDATA]=SEG(STA_R,0x200000,0xffffffff,DPL_USER);
	     thenew->sp.eip=elf->entry;
	     insert(thenew);
	assert(run_head->sp.esp==0x100000);

}
