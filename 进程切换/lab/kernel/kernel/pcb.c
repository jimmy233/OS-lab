#include "x86.h"
#include "common.h"
//#include<stdio.h>  
//#include<stdlib.h>  
//#include<string.h>  
//#include<stdint.h>  
//#include<signal.h>  
//#include<pthread.h>  
//#include<semaphore.h>  
//#include<unistd.h>  
/*typedef int pri_spin_t;  
pri_spin_t spin_flag = 1;  
#define MAX_READ_ENTRY 10  
typedef struct _listp  
{  
    struct _listp *next;  
    struct _listp *prev;  
    int data;  
}LISTP;  
  
void pri_spin_lock(pri_spin_t *flag)  
{  
    while(1)  
    {  
        if(*flag)  
        {  
            *flag = 0;  
            return;  
        }  
    }  
      
}  
  
void pri_spin_unlock(pri_spin_t *flag)  
{  
    *flag = 1;  
}  
  
  
  
void init_list_head(LISTP *listp)  
{  
    listp->next = listp;  
    listp->prev = listp;  
}  
  
void list_add(LISTP *list_head, LISTP *listp)  
{  
  
    list_head->next->prev = listp;  
    listp->next = list_head->next;  
    listp->prev = list_head;  
    list_head->next = listp;  
}  
void list_add_tail(LISTP *list_head, LISTP *listp)  
{  
    list_head->prev->next = listp;  
    listp->prev = list_head->prev;  
    listp->next=list_head;  
    list_head->prev = listp;  
  
}  
  
int list_is_empty(LISTP *list_head)  
{  
    return (list_head->next == list_head);  
}  
  
void list_del(LISTP *listp)  
{  
    LISTP *prev;  
    LISTP *next;  
    prev = listp->prev;  
    next = listp->next;  
    prev->next = next;  
    next->prev = prev;  
      
    listp->next = listp;  
    listp->prev = listp;  
}  
void free_list(LISTP *list_head)  
{  
    LISTP *pos = NULL;  
    pos = list_head->next;  
    while(pos != list_head)  
    {  
        list_del(pos);  
            free(pos);  
        pos = list_head->next;     
        printf("free\n");  
    }  
      
    if((list_head->next == list_head->prev)&&(list_head->next == list_head))  
    {  
        printf("list empty\n");  
    }  
    list_head->next = NULL;  
    list_head->prev = NULL;  
  
    free(list_head);  
}  
int add_data(int data, LISTP *list_head)  
{  
    LISTP *listp = NULL;  
  
    listp = (LISTP *)malloc(sizeof(LISTP));  
    if(listp == NULL)  
    {  
        printf("%s:Can not get memory\n", __FUNCTION__);  
        return -1;  
    }  
  
    listp->data = data;  
    list_add(list_head, listp);  
      
}  
int add_data_tail(int data, LISTP *list_head)  
{  
    LISTP *listp = NULL;  
  
    listp = (LISTP *)malloc(sizeof(LISTP));  
    if(listp == NULL)  
    {  
        printf("%s:Can not get memory\n", __FUNCTION__);  
        return -1;  
    }  
  
    listp->data = data;  
    list_add_tail(list_head, listp);  
      
}  
void print_data(LISTP *list_head)  
{     
    int data;  
    LISTP *pos;  
  
    if(list_is_empty(list_head))  
    {  
        printf("list head is empty\n");  
        return;  
    }  
    for(pos = list_head->next; pos != list_head;pos = pos->next)  
    {  
        if(pos)  
        {  
            if(pos->next == list_head)  
                printf("%d\n", pos->data);  
            else  
                printf("%d\t", pos->data);  
        }  
    }     
}  
void read_data(LISTP *list_head, int num)  
{  
    int data;  
    LISTP *entry;  
  
    if(list_is_empty(list_head))  
    {  
        printf("list head is empty\n");  
        return;  
    }  
      
    if(num > MAX_READ_ENTRY)  
    {  
        num = MAX_READ_ENTRY;  
    }  
    printf("READ MESSAGE IS:\n");  
    for(entry = list_head->next; (entry != list_head)&&(num > 0); entry = list_head->next)  
    {  
        printf("%d\t", entry->data);  
        list_del(entry);  
        entry->next = NULL;  
        entry->prev = NULL;  
        free(entry);  
        num--;  
      
    printf("\n");     
}  
  
void *send_message_pth1(void *arg)  
{  
    int i = 0;  
    while(1)  
    {  
        pri_spin_lock(&spin_flag);    
        add_data_tail(i, (LISTP *)arg);  
        printf("-----IN SEND_MESSAGE_PTHREAD 1-----\n");  
        pri_spin_unlock(&spin_flag);  
        i++;  
        sleep(2);     
    }  
}  
void *send_message_pth2(void *arg)  
{  
    int i = 0;  
    while(1)  
    {  
        pri_spin_lock(&spin_flag);    
        add_data_tail(i, (LISTP *)arg);  
                printf("-----IN SEND_MESSAGE_PTHREAD 2-----\n");  
                pri_spin_unlock(&spin_flag);  
        i++;  
        sleep(2);     
    }  
}  
void *print_message_pth(void *arg)  
{  
    while(1)  
    {  
  
                pri_spin_lock(&spin_flag);  
                printf("-----IN PRINT_MESSAGE_PTHREAD-----\n");  
        print_data((LISTP *)arg);  
        pri_spin_unlock(&spin_flag);  
        sleep(2);  
    }  
}     
  
void *read_message_pth(void *arg)  
{  
    int num = 5;  
      
    while(1)  
    {  
        pri_spin_lock(&spin_flag);  
        printf("-----IN READ_MESSAGE_PTH-----\n");  
        read_data((LISTP *)arg, num);  
        pri_spin_unlock(&spin_flag);  
        sleep(6);  
    }  
      
} */ 
ProcessTable pcb[PCB_NUM];
ProcessTable *block_head,*block_tail;
ProcessTable *run_head,*run_tail;
ProcessTable *freec;
ProcessTable *rn;
ProcessTable *idle_pcb;

/*void schedule(){
	if(listIsEmpty(&ready_queue))
		current_pcb = &pcb_table[0];
	
	else{
		List *temp = ready_queue.next;
		current_pcb = list_entry(temp,struct PCB,member);
		current_pcb->time_count = 20;
		tss.esp0 = (uint32_t)current_pcb->kstack + KSTACK_SIZE - 1;
		need_schedule = 0;
	}
}

void do_time(){
	current_pcb->time_count--;
	if(current_pcb->time_count == 0){
		if(current_pcb == &pcb_table[0])
			current_pcb->time_count = 100;
		
		else{
			delList(&(current_pcb->member));
			addPreList(&ready_queue,&(current_pcb->member));
			current_pcb->time_count = 20;
			need_schedule = 1;
		}
	}
	List *block_temp = block_queue.next;
	while(block_temp != &block_queue){
		PCB *temp_pcb = list_entry(block_temp, struct PCB, member);
		temp_pcb->sleep_time--;
		if(temp_pcb->sleep_time == 0){
			temp_pcb->time_count = 20;
			List *old_pcb = block_temp;
			block_temp = block_temp->next;
			delList(old_pcb);
			addPreList(&ready_queue,old_pcb);
			need_schedule = 1;
		}
		else
			block_temp = block_temp->next;
	}
}*/
void init_pcb()
{
	int i=0;
	while(i!=PCB_NUM-1)
	{
	pcb[i].next=&pcb[i+1];
	pcb[i].pid=i+1;
	pcb[i].state=TASK_NEW;
	pcb[i].timeCount=0;
	pcb[i].sleepTime=0;
	i++;
	}

	pcb[PCB_NUM-1].next=NULL;
	pcb[PCB_NUM-1].pid=PCB_NUM;
	pcb[PCB_NUM-1].state=TASK_NEW;
	pcb[PCB_NUM-1].timeCount=0;
	pcb[PCB_NUM-1].sleepTime=0;
	block_head=NULL;
	block_tail=NULL;
	run_head=NULL;
	run_tail=NULL;
	rn=NULL;
	idle_pcb=NULL;
	freec=&pcb[0];

}

ProcessTable *newp()
{
if(freec==NULL)
	return NULL;
else
{
	ProcessTable *new=freec;
	freec=freec->next;
	new->timeCount=10;
	new->sleepTime=0;
	new->next=NULL;
	return new;
}
}

void insert2(ProcessTable *pcb)
{
	pcb->next=NULL;
	if(block_head==NULL)
	block_head=block_tail=pcb;
	else
	{
		block_tail->next=pcb;
		block_tail=pcb;
	}
}


void insert(ProcessTable *pcb)
{
	
	 if(run_head==NULL)
	 {
	 run_head=pcb;
	 run_tail=pcb;
	 run_head->next=NULL;
	 run_tail->next=NULL;
	 }
	 else
	 {
	 run_tail->next=pcb;
	 run_tail=pcb;
	 }

}

void delet2(ProcessTable *pcb)
{
  if(block_head==NULL)
  return ;
  if(pcb==block_head)
  {
  	block_head=block_head->next;
	return ;
  }
  ProcessTable *head=block_head;
  while(1)
  {
  if(head->next==pcb)break;
  head=head->next;
	}
  ProcessTable *del=head->next;
  if(del==block_tail)
  	block_tail=head;
  head->next=del->next;
  del->next=NULL;
  return ;

}

void delet(ProcessTable *pcb)
{
	if(run_head==NULL)
		return ;
	if(pcb==run_head)
	{
		run_head=run_head->next;
		return ;
	}

	ProcessTable *head=run_head;

while(1)
{
	if(head->next==pcb)break;
	head=head->next;
	}
ProcessTable *del=head->next;
if(del==run_tail)
	run_tail=head;
head->next=del->next;
del->next=NULL;
return ;
}


void free_pcb(ProcessTable *pcb)
{
pcb->state=TASK_NEW;
pcb->next=freec;
freec=pcb;
}

/*void PCBPool_init()
{
	list_init(&free);
	list_init(&ready);
	list_init(&block);
	int i;
	for(i=0;i<PCB_pool_NUM;i++)
		list_add_after(&free,&(PCBPool[i].list));
}

void idle_init(){
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

//鍒犻櫎ready涓殑pcb鏃跺簲璇ュ厛纭涓嶆槸idle鐨刾cb

//鍒涘缓涓€涓繘绋?
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
	list_add_before(ready.prev,&((*new_pcb)->list));//鍔犲叆鍒皉eady闃熷垪鐨勯槦灏撅紙瀹為檯涓婃槸idle鐨勫墠闈紝鍊掓暟绗簩涓級

	
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
	list_add_before(ready.prev,&(new_pcb->list));//鍔犲叆鍒皉eady闃熷垪鐨勯槦灏撅紙瀹為檯涓婃槸idle鐨勫墠闈紝鍊掓暟绗簩涓級
	return new_pcb;
}

void TrapFrame_init(struct TrapFrame *tf){
		 tf -> ds = USEL(SEG_UDATA);
		 tf -> es = USEL(SEG_UDATA);
		 tf -> cs = USEL(SEG_UCODE);
		 tf -> ss = USEL(SEG_UDATA);
//		 tf->esp=(uint32_t)(&(((new_pcb)->kstack)[KSTACK_SIZE-1]));
		tf->eflags = 0x00000202;
}*/
