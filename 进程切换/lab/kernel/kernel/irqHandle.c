#include "x86.h"
#include "device.h"
#include <sys/syscall.h>
#include <malloc.h>

#define NR_HARD_INTR 16
#define NR_IRQ_HANDLE 32
static uint32_t pos = 0;
static int row=0;
static int col=0;
void syscallHandle(struct TrapFrame *tf);
void schedule();
void idle(void);
extern TSS tss;
extern SegDesc gdt[NR_SEGMENTS];

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
int fs_ioctl(int fd,const void* buf, size_t count);
static void sys_brk(struct TrapFrame *tf)
{
	tf->eax=mm_brk(tf->ebx);
}
//static void sys_ioctl(struct TrapFrame *tf)
//{
//	tf->eax=fs_ioctl(tf->ebx,tf->ecx,(void *)tf->edx);
//}
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
int fs_ioctl(int fd,const void* buf,size_t count)
{
	uint32_t base=0;
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
	return (fd>=0 && fd<=2 ? 0 : -1);
}
/*void schedule()
{
 if(need!=1)
 return ;
   if(!empty(&ready))
   {
   	Queue *temp=ready.next;
	rn=queue_entry(temp,struct ProcessTable,component);
	rn->timeCount=20;
	tss.esp0=(uint32_t)rn->stack+MAX_STACK_SIZE -1;
	need=0;
   }
   else
   {
     rn=&pcb[0];
   }
}

void time_handle()
{
	assert(0);
    rn->timeCount--;
    if(rn->timeCount==0)
    {
       	if(rn!=&pcb[0])
	{
	 delet(&(rn->component));
	 add_forward(&ready,&(rn->component));
	 rn->timeCount=20;
	 need=1;
//	 assert(0);
	 }
	 else
	 rn->timeCount=100;
    }
    Queue *temp=block.next;
    while(temp!=&block)
    {
     	ProcessTable *temp_pcb=queue_entry(temp,struct ProcessTable,component);
	temp_pcb->sleepTime--;
	if(temp_pcb->sleepTime==0)
	{
	   Queue *temp_pass= temp;
	   temp=temp->next;
	   delet(temp_pass);
	   add_forward(&ready,temp_pass);
	   temp_pcb->timeCount=20;
	   need=1;
	}
	else
	temp=temp->next;
    }
}*sys_sleep(int time)
{
	rn->sleepTime=time;
	delet(&(rn->component));
	add_forward(&block,&(rn->component));
	need=1;
}
void sys_exit()
{
  delet(&(rn->component));
  add_forward(&freec,&(rn->component));
  need=1;

}

void sys_fork()
{
 	ProcessTable *pcb=queue_entry(freec.next,ProcessTable,component);
	delet(freec.next);
	pcb->state=TASK_READY;
	pcb->timeCount=20;
	pcb->tf=(struct TrapFrame*)(pcb->stack+MAX_STACK_SIZE - (rn->stack+MAX_STACK_SIZE-(uint32_t)rn->tf));
        int i;
	for(i=0;i<MAX_STACK_SIZE;i++)
	pcb->stack[i]=rn->stack[i];
pcb->tf->ds=USEL(SEG_CUDATA);
pcb->tf->es=USEL(SEG_CUDATA);
pcb->tf->ss=USEL(SEG_CUDATA);
pcb->tf->cs=USEL(SEG_CUCODE);
pcb->tf->eax=0;
rn->tf->eax=4;
unsigned char *child=(unsigned char*)0x400000;
unsigned char *parent=(unsigned char*)0x200000;
for(i=0;i<0x200000;i++)
child[i]=parent[i];

add_down(&ready,&(pcb->component));
need=1;

}*static void sys_brk(struct TrapFrame *tf)
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
									*/
//void GProtectFaultHandle(struct TrapFrame *tf);

void time_handle()
{
  if(rn!=NULL && rn->timeCount>0)
					rn->timeCount--;
				struct ProcessTable *lis=block_head;
				while(lis!=NULL)
				{
					if(lis->sleepTime>0)
						--lis->sleepTime;
					ProcessTable *p=lis->next;
					if(lis->sleepTime==0)
					{
						delet2(lis);
						insert(lis);
						lis->state=TASK_RUNNABLE;
					}
					lis=p;
				}
				if(rn!=NULL && rn->timeCount==0)
				{
					if(rn!=idle_pcb)
					{
					rn->timeCount=10;
					insert(rn);
					}
					rn=NULL;
					//assert(run_tail->sp.esp==0x100000);
					schedule();
				}
}
int base(uint16_t ds)
{
       //	int index=rn->sp.ds>>3;

	int index = ds>>3;
		return gdt[index].base_15_0 + (((uint32_t)gdt[index].base_23_16)<<16);
}
void irqHandle(struct TrapFrame *tf) {
	/*
	 * 中断处理程序
	 */
	/* Reassign segment register */
	asm volatile("movw %%cx,%%ds"::"c"(KSEL(SEG_KDATA)));
	asm volatile("movw %%cx,%%es"::"c"(KSEL(SEG_KDATA))); 
	asm volatile("movw %%cx,%%fs"::"c"(KSEL(SEG_KDATA))); 
	asm volatile("movw %%cx,%%gs"::"c"(KSEL(SEG_KDATA))); 
	switch(rn->sp.irq) {
	
		case 0x2e:
			break;
		case 0x20:
			{
			//	assert(run_head->sp.esp==0x100000);
			   //	assert(0);
			/*	if(rn!=NULL && rn->timeCount>0)
					rn->timeCount--;
				struct ProcessTable *lis=block_head;
				while(lis!=NULL)
				{
					if(lis->sleepTime>0)
						--lis->sleepTime;
					ProcessTable *p=lis->next;
					if(lis->sleepTime==0)
					{
						block_delet(lis);
						insert(lis);
						lis->state=TASK_RUNNABLE;
					}
					lis=p;
				}
				if(rn!=NULL && rn->timeCount==0)
				{
					if(rn!=idle_pcb)
					{
					rn->timeCount=10;
					insert(rn);
					}
					rn=NULL;
					//assert(run_tail->sp.esp==0x100000);
					schedule();
				}*/
				time_handle();
				break;
			}
		case 0x80:
			syscallHandle(tf);
			break;
		default:assert(0);
	}
}
void do_sleep()
{
 rn->sleepTime=rn->sp.ebx;
			rn->state=TASK_BLOCKED;
			insert2(rn);
			rn=NULL;
			schedule();	
}
void do_exit()
{
   rn->state=TASK_DEAD;
			free_pcb(rn);
			rn=NULL;
			schedule();	
}
void do_fork()
{
	gdt[SEG_UCODE2] = SEG(STA_X|STA_R,0x400000,0xffffffff,DPL_USER);
			gdt[SEG_UDATA2] = SEG(STA_W,0x400000,0xffffffff,DPL_USER);
			setGdt(gdt,sizeof(gdt));
			uint8_t* father=(uint8_t*)0x200000;
			uint8_t* child=(uint8_t*)0x400000;
			int i;
			for(i=0;i<0x200000;++i)
				child[i]=father[i];
			ProcessTable* pcb = newp();
			if(pcb==NULL)
			{
				rn->sp.eax=-1;
			}
			else
		{
			pcb->timeCount = rn->timeCount/2;
			rn->timeCount=rn->timeCount/2;
			pcb->sp.edi=rn->sp.edi;
			pcb->sp.esi=rn->sp.esi;
			pcb->sp.ebp=rn->sp.ebp;
			pcb->sp.xxx=rn->sp.xxx;
			pcb->sp.ebx=rn->sp.ebx;
			pcb->sp.edx=rn->sp.edx;
			pcb->sp.ecx=rn->sp.ecx;
			pcb->sp.eax=rn->sp.eax;
			pcb->sp.eip=rn->sp.eip;
			pcb->sp.cs=USEL(SEG_UCODE2);
			pcb->sp.eflags=rn->sp.eflags;
			pcb->sp.esp=rn->sp.esp;
			pcb->sp.ss=USEL(SEG_UDATA2);
			pcb->sp.gs=USEL(SEG_UDATA2);
			pcb->sp.fs=USEL(SEG_UDATA2);
			pcb->sp.es=USEL(SEG_UDATA2);
			pcb->sp.ds=USEL(SEG_UDATA2);
			pcb->sleepTime=0;
			pcb->state=TASK_RUNNABLE;
			pcb->sp.eax=0;
			rn->sp.eax=pcb->pid;
			insert(pcb);	
		}
}
void syscallHandle(struct TrapFrame *tf) {
	/* 实现系统调用*/
			switch(rn->sp.eax)
				{
			case 0:
				{
						enableInterrupt();
		add_irq_handle(tf->ebx, (void *)tf->ecx);
		disableInterrupt();
				break;
				}
			case SYS_brk:sys_brk(tf);break;
			case SYS_ioctl:break;
				case SYS_write:
				{
	 	 /* char *str = (char*)((void *)tf->ecx)+getbase();
	          int i = 0;
	                   for(;i < tf->edx;i++){
	                             putChar(str[i]);
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
		    tf->eax=tf->edx;*/
		   char *str=(char *)rn->sp.ecx+base(rn->sp.ds);
	int len=rn->sp.edx;
        int i ;
	for(i=0;i<len;++i)
	{
		if(str[i]=='\n')
		{
			col=0;
			++row;
		}
		else
		{
			unsigned short data = (0x0c<<8)|(*(str+i));
			unsigned short* addr = (unsigned short*)(0xb8000+160*row + 2*col);
			col++;
			if(col>=80)
			{
				col=0;
				row++;
			}
			*addr=data;
		}
	}
	rn->sp.eax=len;
		    break;
		    		}


                  case 162:
		{

 			do_sleep();
			break;
		}
		case 1:
		{

			do_exit();
			break;
		}
		case 2:
		{
		
			do_fork();
			break;
		}

		default:assert(0);

}

}
void schedule(void)
{
//   	assert(0);
	if(rn!=NULL) 
		return;
	if(run_head!=NULL)
	{
		rn=run_head;
		run_head=run_head->next;
		rn->next=NULL;
		rn->state=TASK_RUNNING;
		tss.esp0=(uint32_t)(((uint8_t*)(&(rn->sp)))+sizeof(rn->sp));
	}
	else 
	{
		rn=idle_pcb;
	}
}
