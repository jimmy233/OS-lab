#ifndef __PROCESS_H__                                                  
#define __PROCESS_H__                                                  

#include "common.h"                                             
#include "memory.h"                                      
#include "list.h"

#define KSTACK_SIZE 4096
#define PCB_pool_NUM 64

#define TASK_STOPPED         	0
#define TASK_RUNING			1
#define TASK_READY				2
#define TASK_INTERRUPTIBLE		3
#define TASK_UNINTERRUPTIBLE 	4

typedef	struct PCB{
		ListHead list;
		struct TrapFrame *tf;
		uint8_t kstack[KSTACK_SIZE];
		int pid;
		int state;
		uint8_t time_count;
		int sleep_time;
}PCB;

PCB *current,*pcb_of_idle;

ListHead ready,block,freeb;

PCB PCBPool[PCB_pool_NUM];

void PCBPool_init();
PCB* create_kthread(void *fun);
void TrapFrame_init(struct TrapFrame *tf);
void enter_process_userspace();
void idle_init();
//PCB *new_PCB();
void schedule();
void process_sleep(int num);
void process_exit(int flag);
void process_fork();

#endif
