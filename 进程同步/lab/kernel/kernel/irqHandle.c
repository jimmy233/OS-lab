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

void time_handle()
{
                       if(rn!=NULL )
		       {
		             if(rn->timeCount>0)
					rn->timeCount=rn->timeCount-1;
					}
				struct ProcessTable *lis=block_head;
				while(lis!=NULL)
				{
					if(lis->sleepTime>0)
						lis->sleepTime=lis->sleepTime-1;
					ProcessTable *p=lis->next;
					if(lis->sleepTime==0)
					{
						delet2(lis);
						insert(lis);
						lis->state=TASK_RUNNABLE;
					}
					lis=p;
				}
				if(rn!=NULL)
				{
				   if(rn->timeCount==0)
				   {
					if(rn!=idle_pcb)
					{
					rn->timeCount=10;
					insert(rn);
					}
					rn=NULL;
				//assert(run_tail->sp.esp==0x100000);
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
	
		case 0x20:
			{
			//	assert(run_head->sp.esp==0x100000);
				time_handle();
				break;
			}
		case 0x80:
			syscallHandle(tf);
			break;
		default:break;
	}
}
void do_sleep()
{
 rn->sleepTime=rn->sp.ebx;
			rn->state=TASK_BLOCKED;
			insert2(rn);
			rn=NULL;
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
void do_exit()
{
   rn->state=TASK_DEAD;
			free_pcb(rn);
			rn=NULL;
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
		      uint32_t h=rn->timeCount/2;
			pcb->timeCount = h;
			rn->timeCount=pcb->timeCount;
			uint32_t h1=rn->sp.edi,h2=rn->sp.esi,h3=rn->sp.ebp,h4=rn->sp.xxx,h5=rn->sp.ebx,h6=rn->sp.edx,h7=rn->sp.ecx,h8=rn->sp.eax,h9=rn->sp.eip;
			uint32_t y1=rn->sp.eflags,y2=rn->sp.esp;
			pcb->sp.edi=h1;
			pcb->sp.esi=h2;
			pcb->sp.ebp=h3;
			pcb->sp.xxx=h4;
			pcb->sp.ebx=h5;
			pcb->sp.edx=h6;
			pcb->sp.ecx=h7;
			pcb->sp.eax=h8;
			pcb->sp.eip=h9;
			pcb->sp.cs=USEL(SEG_UCODE2);
			pcb->sp.eflags=y1;
			pcb->sp.esp=y2;
			pcb->sp.ss=USEL(SEG_UDATA2);
			pcb->sp.gs=USEL(SEG_UDATA2);
			pcb->sp.fs=USEL(SEG_UDATA2);
			pcb->sp.es=USEL(SEG_UDATA2);
			pcb->sp.ds=USEL(SEG_UDATA2);
			pcb->sleepTime=0;
			pcb->state=TASK_RUNNABLE;
			pcb->sp.eax=0;
			rn->sp.eax=pcb->pid;
			pcb->sem=rn->sem;
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
			row++;
		}
		else
		{
		       uint32_t number=0xb8000+160*row+2*col;
			unsigned short data = (0x0c<<8)|(*(str+i));
			unsigned short* addr = (unsigned short*)number;
			col++;
			if(col==80)
			{
				col=col-80;
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
                case 5:
		{
	         sem_init(&rn->sp.ecx,rn->sp.ebx);	  

		 break;
		}
		case 7:
		{
		Semaphore** t=(Semaphore**)(&(rn->sem));
		 P(t);
		 break;
		}
		case 8:
		{
		     V((Semaphore**)(&(rn->sem)));
		     break;
		}
		case 6:
		{
		       int i;
		       for(i=0;i<PCB_NUM;++i)
		       {
		        if(pcb[i].sem!=NULL &&(&pcb[i])!=idle_pcb)
			{
			 free_pcb(&pcb[i]);
			}

		       }
		       rn=NULL;
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
