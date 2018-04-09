#include "x86.h"

extern ProcessTable *run_head,*run_tail;
Semaphore st[SE_NUM];
extern TSS tss;
void enqueue(ProcessTable** list,ProcessTable* process)
{
	process->next=NULL;
	if(*(list)==NULL)
		*(list)=process;
	else
	{
	 ProcessTable* head=*(list);
	 while(head->next!=NULL)
	 head=head->next;
	 head->next=process;
	}
}

ProcessTable* dequeue(ProcessTable** list)
{
      if(*(list)==NULL)
      return NULL;
      else
      {
      	ProcessTable *re=*(list);
	*(list)=(*(list))->next;
	re->next=NULL;
	return re;
      }
}

void sem_init(uint32_t *sem,uint32_t value)
{
      
      
     // sem_free=0;
      st[*sem].value=value;
      rn->sem=(struct Semaphore*)(&(st[(*sem)++]));
      
}
void P(Semaphore** sem)
{
	(*sem)->value=(*sem)->value-1;
	if((*sem)->value<0)
	{
             enqueue(&((*sem)->block),rn);
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
}
void V(Semaphore** sem)
{
  (*sem)->value=(*sem)->value+1;
  if((*sem)->value<=0)
  {
  	ProcessTable* re=dequeue(&((*sem)->block));
        if(run_head==NULL)
	 {
	 run_head=re;
	 run_tail=re;
	 run_head->next=NULL;
	 run_tail->next=NULL;
	 }
	 else
	 {
	 run_tail->next=re;
	 run_tail=re;
	 } 
  }
}
