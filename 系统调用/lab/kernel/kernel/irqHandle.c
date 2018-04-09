#include "x86.h"
#include "device.h"
#include <sys/syscall.h>
#include <malloc.h>

#define NR_HARD_INTR 16
#define NR_IRQ_HANDLE 32
static uint32_t pos = 0;
uint32_t cur_brk=0;
uint32_t max_brk=0;
struct IRQ_t
{
	void (*routine)(void);
	struct IRQ_t *next;
};

static struct IRQ_t handle_pool[NR_IRQ_HANDLE];
static struct IRQ_t *handles[NR_HARD_INTR];
static int handle_count=0;
uint32_t mm_brk(uint32_t new_brk);
int fs_ioctl(int fd,uint32_t request, void *p);
void syscallHandle(struct TrapFrame *tf);

void GProtectFaultHandle(struct TrapFrame *tf);

static void sys_brk(struct TrapFrame *tf)
{
	tf->eax=mm_brk(tf->ebx);
}
static void sys_ioctl(struct TrapFrame *tf)
{
	tf->eax=fs_ioctl(tf->ebx,tf->ecx,(void *)tf->edx);
}
void add_irq_handle(int irq,void (*func)(void))
{
	assert(irq<NR_HARD_INTR);
	assert(handle_count <= NR_IRQ_HANDLE);

	struct IRQ_t *ptr;
	ptr= &handle_pool[handle_count++];
	ptr->routine=func;
	ptr->next=handles[irq];
	handles[irq]=ptr;
}
void irqHandle(struct TrapFrame *tf) {
	/*
	 * 中断处理程序
	 */
	/* Reassign segment register */

	switch(tf->irq) {
		case -1:
			break;
		case 0xd:
			GProtectFaultHandle(tf);
			break;
		case 0x80:
			syscallHandle(tf);
			break;
		default:assert(0);
	}
}
void syscallHandle(struct TrapFrame *tf) {
	/* 实现系统调用*/
	if(tf->eax==0)
	{
	  	enableInterrupt();
		add_irq_handle(tf->ebx, (void *)tf->ecx);
		disableInterrupt();
	}
	 else if(tf->eax== SYS_brk)
	 {
	 sys_brk(tf);
	 }
	 else if (tf->eax==SYS_ioctl)
	 {
	 sys_ioctl(tf);
	 }
	else if(tf->eax== 4)
	  {
	    
	 	  char *str = (char*)((void *)tf->ecx);
	          int i = 0;
	                   for(;i < tf->edx;i++){
	                             if((*(str + i)) == '\n')
	                              {
	                                       pos = (pos/80+1)*80;
	                                        continue;
	                                 }
		          unsigned int position = 0xb8000 + (pos*2);
		           unsigned int  print= (unsigned char)(*(str+i))+0x0c00;
		            asm volatile("movw %1,(%0)\n\t"::"a"(position),"c"(print));
		                             pos++;
		                             }
		    tf->eax=tf->edx;					
	}
	else
	{
	assert(0);
	}

}

void GProtectFaultHandle(struct TrapFrame *tf){
	assert(0);
	return;
}

uint32_t mm_brk(uint32_t new_brk)
{
	if(new_brk !=0)
	{
		if(new_brk > max_brk)
		 {
		//  malloc(max_brk,new_brk-max_brk);
		  max_brk=new_brk;
		 }
		cur_brk=new_brk;
	}
	return cur_brk;
}
int fs_ioctl(int fd,uint32_t request, void *p)
{
	return (fd>=0 && fd<=2 ? 0 : -1);
}
