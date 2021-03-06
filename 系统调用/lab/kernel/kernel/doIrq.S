.code32

.global irqEmpty
irqEmpty:
	pushl $0 // push dummy error code
	pushl $-1 // push interrupt vector into kernel
	jmp asmDoIrq
/*.global vec0
vec0:
	pushl $0
	pushl $0
	jmp asmDoIrq

.global vec1
vec1:
	pushl $0
	pushl $1
	jmp asmDoIrq
.global vec2
vec2:
	pushl $0
	pushl $2
	jmp asmDoIrq

.global vec3
vec3:
         pushl $0
         pushl $3
         jmp asmDoIrq

.global vec4
vec4:
         pushl $0
         pushl $4
         jmp asmDoIrq

.global vec5
vec5:
         pushl $0
         pushl $5
         jmp asmDoIrq

.global vec6
vec6:
	 pushl $0
         pushl $6
         jmp asmDoIrq

.global vec7
vec7:
         pushl $0
         pushl $7
         jmp asmDoIrq

.global vec8
vec8:
         pushl $8
         jmp asmDoIrq

.global vec9
vec9:
         pushl $0
         pushl $9
         jmp asmDoIrq

.global vec10
vec10:
          pushl $10
          jmp asmDoIrq

.global vec11
vec11:
          pushl $11
          jmp asmDoIrq

.global vec12
vec12:
          pushl $12
          jmp asmDoIrq

.global vec14
vec14:
          pushl $14
          jmp asmDoIrq
*/
.global irqGProtectFault
irqGProtectFault:
	pushl $0xd
	jmp asmDoIrq

/*.global irq0
irq0:
	pushl $0
	pushl $1000
	jmp asmDoIrq

.global irq1
irq1:
	pushl $0
	pushl $1001
	jmp asmDoIrq

.global irq14
irq14:
	pushl $0
	pushl $1014
	jmp asmDoIrq
*/
.global irqSyscall
irqSyscall:
	pushl $0 // push dummy error code
	pushl $0x80 // push interrupt vector into kernel stack
	jmp asmDoIrq

.global asmDoIrq
asmDoIrq:
	pushal // push process state into kernel stack
	pushl %esp
	call irqHandle
	addl $4, %esp
	popal
	addl $4, %esp //interrupt vector is on top of kernel stack
	addl $4, %esp //error code is on top of kernel stack
	iret
