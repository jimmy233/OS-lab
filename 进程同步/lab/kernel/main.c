#include "common.h"
#include "x86.h"
#include "device.h"
extern TSS tss;
void idle(void)
{
uint32_t inp=(uint32_t)(((uint8_t *)(&(rn->sp)))+sizeof(rn->sp)-8);
 asm volatile("movl %0, %%esp": :"r"(inp));
 enableInterrupt();
 while(1)
 	waitForInterrupt();
}
void init_idle(void)
{
	ProcessTable *pcb=newp();
	rn=pcb;
	uint32_t initi=1;
	pcb->timeCount=initi;
	idle_pcb=pcb;
}
void kEntry(void) { 
	initSerial();// initialize serial port
	initIdt(); // initialize idt
	initIntr(); // iniialize 8259a
	initSeg(); // initialize gdt, tss
	init_pcb();
	init_idle();
	initTimer();
	loadUMain(); // load user program, enter user space
	idle();
	//while(1);
	assert(0);
}

/*Btable_initial()
{
  initial(&ready);
  initial(&block);
  initial(&freec);
  int i=0;
 while(i<PCB_NUM)
 {
   add_forward(&freec,&(pcb[i].component));
   pcb[i].pid=i;
   i++;
 }
	
}

ProcessTable *create_thread(uint32_t entry)
{
	ProcessTable *pcb=queue_entry(freec.next,ProcessTable,component);
	delet(freec.next);
	pcb->state=TASK_READY;
	pcb->timeCount=20;
	pcb->tf=(struct TrapFrame*)(pcb->stack+MAX_STACK_SIZE)-1;
	pcb->tf->eax=0;
	pcb->tf->ebx=0;
	pcb->tf->ecx=0;
	pcb->tf->edx=0;
	pcb->tf->esi=0;
	pcb->tf->edi=0;
	pcb->tf->xxx=0;
	pcb->tf->ebp=0;
	pcb->tf->irq=0;
	pcb->tf->eip=entry;
	pcb->tf->esp=0x200000;
	TrapFrame_initial(pcb->tf);
	add_forward(&ready,&(pcb->component));
	need=1;
	return pcb;
}

void init_idle_thread()
{
  ProcessTable *pcb=queue_entry(freec.next,struct ProcessTable,component);
  delet(freec.next);
  current=pcb;
  current->state=TASK_READY;
  pcb->timeCount=100;

}
int sys_write(int judge,const void* buf,size_t count){
	if(judge == 1||judge == 2){
		uint32_t base = translate(current->tf->ds);
		char *str = (char*)buf + base;
		int i = 0;
		for(;i < count;i++){
			if((*(str + i)) == '\n'){
				pos = pos/80*80 + 80;
				continue;
			}
			unsigned int screenpos = 0xb8000 + (pos*2);
			unsigned short int content = (unsigned char)(*(str+i))|(0x0c<<8);
			asm volatile("movw %1,(%0)\n\t"::"a"(screenpos),"c"(content));
			pos++;
		}
	}
	return count;
}
void idle()
{
   enableInterrupt();
   while(1)
   {
 //      if((pcb[0].timeCount==100)&&(empty(&ready))&&(empty(&block)))
 //      {
 //       sys_write(1,".",1);        
//       }
       waitForInterrupt();
   }
}

*/
