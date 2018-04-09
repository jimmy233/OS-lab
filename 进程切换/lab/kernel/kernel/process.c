#include "common.h"
#include "x86/process.h"
#include "x86/list.h"
#include "x86/memory.h"
#include "string.h"
//#include "x86/printk.h"
//#include "x86.h"


/*#define SECTORS_SIZE 512
#define USTACKTOP 0xbffff000
#define ELF_MAGIC 0x464C457FU
#define ELF_PROG_LOAD 1
#define PT_LOAD 1
*/
//此函数可用于测试

//static int pid=0;
extern TSS tss;

void PCBPool_init()
{
	list_init(&freeb);
	list_init(&ready);
	list_init(&block);
	int i;
	for(i=0;i<PCB_pool_NUM;i++)
		list_add_after(&freeb,&(PCBPool[i].list));
}

/*void idle_init(){
//		current = (PCB *)free.next;
//		list_del(free.next);
//		current->time_count = 1;
//		Need_schedule = 1;
		pcb_of_idle->pid = 0;
		pcb_of_idle->time_count = 0;
}

void enter_process_userspace(){
	int i = 0;
	for(;i<PCB_pool_NUM;i++)
			PCBPool[i].pid = i;
	PCB *pcb = (PCB *)free.next;
	list_del(free.next);
	pcb->time_count = 20;
	pcb->state = TASK_READY;	
	list_add_before(&ready, &(pcb->list));
	pcb->tf =(struct TrapFrame *) (pcb->kstack + 4096 - sizeof(struct TrapFrame));
	TrapFrame_init(pcb->tf);
	pcb->tf->edi = 0;
	pcb->tf->esi = 0;
	pcb->tf->ebp = 0;
	pcb->tf->xxx = 0;
	pcb->tf->ebx = 0;
	pcb->tf->edx = 0;
	pcb->tf->ecx = 0;
	pcb->tf->eax = 0;
	pcb->tf->irq = 0;
	pcb->tf->eip = 0;
	pcb->tf->esp = 0x200000;
//	printk("%x elf\n",elf->entry);
//	need_schedule = 1;
//	printk("process.h 60\n");
}

//删除ready中的pcb时应该先确认不是idle的pcb

//创建一个进程
void process_fork()
{
	//int32_t generation;
//	printk("process_fork %d is now working!\n",__LINE__);
	TrapFrame *tf;
	*new_pcb=new_PCB();
	if(*new_pcb==NULL)
		return -1;
	pcb->pid=(pid++);
	(*new_pcb)->tf=tf;
	list_add_before(ready.prev,&((*new_pcb)->list));//加入到ready队列的队尾（实际上是idle的前面，倒数第二个）

	
	PCB *pcb = list_entry(free.next,PCB,list);
	if(pcb!=NULL)	list_del(&(pcb->list));
	pcb->time_count = 20; 
	pcb->state = TASK_READY; 
	pcb->tf = (struct TrapFrame*)(pcb->kstack+KSTACK_SIZE - (current->kstack    +KSTACK_SIZE-(uint32_t)current->tf));  
	int i;
	for(i = 0;i < KSTACK_SIZE;i++) 
			pcb->kstack[i] = current->kstack[i];
	pcb->tf->eax = 0;
	current->tf->eax = pcb->pid;
	pcb->tf->ds = USEL(SEG_UDATA_2);
	pcb->tf->es = USEL(SEG_UDATA_2);
	pcb->tf->ss = USEL(SEG_UDATA_2);
	pcb->tf->cs = USEL(SEG_UCODE_2);
	unsigned char *child = (unsigned char*)0x500000; 
	unsigned char *parent = (unsigned char*)0x200000;
	for(i = 0;i < 0x200000;i++)
			child[i] = parent[i];
	list_add_after(&ready,&(pcb->list)); 
}

PCB *create_kthread(void *fun){
	PCB *new_pcb = list_entry(free.next,PCB,list);
	if(new_pcb!=NULL)	list_del(&(new_pcb->list));
	TrapFrame *tf;
	tf=(void *)(&((new_pcb->kstack)[KSTACK_SIZE-sizeof(TrapFrame)-1]));
	tf->eip=(uint32_t)(fun);
	if(new_pcb==NULL)
		return NULL;
	new_pcb->pid=(pid++);
	new_pcb->tf=tf;
	TrapFrame_init(tf);
	asm volatile("movl %%cr3,%%eax"::);
	asm volatile("addl $0xc0000000,%%eax"::);
//	asm volatile("movl %%eax,%0"::"m"(new_pcb->pgdir));
	new_pcb->time_count=0;
	list_add_before(ready.prev,&(new_pcb->list));//加入到ready队列的队尾（实际上是idle的前面，倒数第二个）
	return new_pcb;
}

void TrapFrame_init(struct TrapFrame *tf){
		 tf -> ds = USEL(SEG_UDATA);
		 tf -> es = USEL(SEG_UDATA);
		 tf -> cs = USEL(SEG_UCODE);
		 tf -> ss = USEL(SEG_UDATA);
//		 tf->esp=(uint32_t)(&(((new_pcb)->kstack)[KSTACK_SIZE-1]));
		tf->eflags = 0x00000202;
}

//从内核空间到用户空间的返回
void pcb_pop_tf(TrapFrame *tf)
{	
	//printk("pcb_pop_tf here is working! %s %d\n",__FILE__,__LINE__);
	print_stack(tf);


	//printk("pcb_pop_tf here is working! %s %d\n",__FILE__,__LINE__);
	asm volatile("movl %0,%%esp": :"g"(tf):"memory");
	asm volatile("popal");
	asm volatile("popl %%gs"::);
	asm volatile("popl %%fs"::);
	asm volatile("popl %%es"::);
	asm volatile("popl %%ds"::);
	asm volatile("addl $0x8,%%esp"::);
	asm volatile("iret");

	
	printk("pcb_pop_tf failed! %s %d\n",__FILE__,__LINE__);
	panic("iret failed!\n");

}
*/
//让用户进程执行
/*void process_exec(PCB *pcb)
{
	
	//   让用户程序运行起来，核心是加载相应的页目录和进入ring3环境
	 
//	printk("pcb->pgdir=0x%x\n",(uint32_t)(pcb->pgdir));
	printk("process_exec is here working %s %d",__FILE__,__LINE__);
	set_cr3((void *)va_to_pa(pcb->pgdir));
	printk("process_exec is here working %s %d",__FILE__,__LINE__);
	pcb_pop_tf((TrapFrame *)(pcb->tf));
	printk("process_exec is here working %s %d",__FILE__,__LINE__);
}*/

//Alloc len bytes from the address va
//从虚拟地址va开始分配len字节长度的空间
/*static void segment_alloc(PCB *pcb,void *va , size_t len)
{
	int i;
	Page *page;

	va =(void *)(PGROUNDDOWN(((long)(va))));
	printk("segment_alloc is here working!va = 0x%x %s %d\n",va,\
			__FILE__,__LINE__);
	for(i = 0;i < PGROUNDUP(len)/PG_SIZE;i++)
	{
		if(page_alloc(&page,GFP_USER) != 0)
		{
			printk("Segment_alloc page_alloc failed! %S %d\n",\
					__FILE__,__LINE__);
			return;
		}

		printk("segment_alloc page_alloc here working! %s %d\n",\
			__FILE__,__LINE__);
		if(page_insert(pcb->pgdir,page,va + i*PG_SIZE,PTE_U | PTE_W) != 0)
		{
			printk("Segment_alloc page_insert failed! %S %d\n",\
					__FILE__,__LINE__);
			return;
		}
		printk("segment_alloc page_insert here working! %s %d\n",\
			__FILE__,__LINE__);
	}

	printk("segment_alloc is here working! %s %d\n",__FILE__,__LINE__);
	return;
}
*/
//在内核空间创建一个用户进程，并从此跳转到用户空间执行此进程
/*int enter_process_userspace()
{
	PCB *pcb;
	int res;

//	printk("enter_process_userspace is working %s %d\n",\
			__FILE__,__LINE__);
	res = process_fork(&pcb);
//	printk("res=%d",res);
	if(res < 0)
		return -1;
//	printk("enter_process_userspace process_fork is working %s %d \n",\
			__FILE__,__LINE__);
    
	process_load(pcb);
//	printk("enter_process_userspace process_load is working %s %d\n",\
			__FILE__,__LINE__);

	process_exec(pcb);
//	printk("enter_process_userspace process_exec is working %s %d\n",\
			__FILE__,__LINE__);

//	printk("enter_process_userspace is working %s %d \n",__FILE__,\
			__LINE__);
    
	return 0;
}*/


/*void process_sleep(int num){
	TrapFrame *tf=(TrapFrame *)(current->tf);
	asm volatile("movl %%eax,%0" : : "m"(tf->eax));
	asm volatile("movl %%ecx,%0" : : :m"(tf->ecx));

	list_del(&(current->list));
	list_add_before(&block,&(current->list));
	current->sleep_time = num;
//	asm volatile("int $0x14");
	schedule();
}

void wakeup(PCB *p){
	int id=p->pid;
	ListHead *node=block.next;
	PCB *current_pcb;
	while(node!=&block){
	    current_pcb=list_entry(node,PCB,list);
		if(current_pcb->pid==id)
		{
			list_del(node);
	        list_add_before(ready.prev,node);//加入到ready队列的队尾（实际上是idle的前面，倒数第二个）
			break;
		}
		node=node->next;
	}
}


void schedule(){
	if(list_empty(&ready)!=1)
			current=list_entry(ready.next,PCB,list);
	else
			current = pcb_of_idle;
	current->time_count=20;
 	tss.esp0 = (uint32_t)(current->kstack+KSTACK_SIZE);
	if(ready.next != &ready){
			current = (PCB *)ready.next;
			tss.esp0 = (uint32_t)(current->kstack+KSTACK_SIZE);
	}
	else
			current = &PCBPool[PCB_pool_NUM-1];

}

void process_exit(int flag){
		if(flag == 1){
				current->state = TASK_STOPPED;
				list_del(&(current->list));
				list_add_before(&free,&current->list);
		}
		printk("exit\n");
		schedule();
}

int sys_fork(){
	PCB *new_pcb;
//	printf("sys_fork %d is now working!\n",__LINE__);
	TrapFrame *new_tf;
	TrapFrame *old_tf=(TrapFrame *)current->tf;
	new_pcb=new_PCB();
	if(new_pcb==NULL)
		return -1;
	new_pcb->pid=(pid++);
	new_pcb->pgdir=current->pgdir;
	new_tf=(void *)(&(new_pcb->kstack)[KSTACK_SIZE-sizeof(TrapFrame)-1]);
	memcpy(new_tf,old_tf,sizeof(TrapFrame));
	new_tf->eax=0;//子进程的eax设置为0
	new_pcb->tf=new_tf;
	list_add_before(ready.prev,&(new_pcb->list));//加入到ready队列的队尾（实际上是idle的前面，倒数第二个）
	//=======生成pcb和完成返回陷阱帧
	if(fork_setup_vm(new_pcb)<0)
		return -1;
	return new_pcb->pid;
}
*/
