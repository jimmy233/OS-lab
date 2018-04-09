.code32

.global irqEmpty
irqEmpty:
//	pushl $0 // push dummy error code
	pushl $-1 // push interrupt vector into kernel
	jmp asmDoIrq

.global vec14
vec14:
          pushl $14
          jmp asmDoIrq

.global irqGProtectFault
irqGProtectFault:
	pushl $0xd
	jmp asmDoIrq

.global irq0
irq0:
	pushl $0x20
	jmp asmDoIrq

.global irq14
irq14:
	pushl $0x2e
	jmp asmDoIrq

.global irqSyscall
irqSyscall:
	pushl $0x80 // push interrupt vector into kernel stack
	jmp asmDoIrq

.global asmDoIrq
.extern irqHandle
.extern rn
asmDoIrq:
	pushal // push process state into kernel stack
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	movl $0x200000,%esp
	//pushl %esp
	nop
	call irqHandle
	movl $rn,%eax
	movl (%eax),%esp

	nop
	popl %gs
	popl %fs
	popl %es
	popl %ds
	popal
	nop
	addl $4, %esp //interrupt vector is on top of kernel stack
//	addl $4, %esp //error code is on top of kernel stack
	iret
