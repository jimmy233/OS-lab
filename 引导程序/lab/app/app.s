.code32

.global start
start:
movl $400, %ecx
addl %ecx,%ebx
shl $1,%ebx
movl %ebx, %edi                #在第5行第0列打印
movb $0x0c, %ah                         #黑底红字
movb $0x48, %al                           #42为H的ASCII码
movw %ax, %gs:(%edi)                    #写显存

addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x65, %al                           
movw %ax, %gs:(%edi) 

addl $2,%ebx
movl %ebx, %edi
movb $0x0c, %ah
movb $0x6c, %al
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x6c, %al                          
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi
movb $0x0c, %ah
movb $0x6f, %al
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi
movb $0x0c, %ah
movb $0x2c, %al
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x20, %al                          
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x57, %al                          
movw %ax, %gs:(%edi)

addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x6f, %al                          
movw %ax, %gs:(%edi)

Addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x72, %al                          
movw %ax, %gs:(%edi)

Addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x6c, %al                          
movw %ax, %gs:(%edi)

Addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x64, %al                          
movw %ax, %gs:(%edi)

Addl $2,%ebx
movl %ebx, %edi                
movb $0x0c, %ah                        
movb $0x21, %al                          
movw %ax, %gs:(%edi)
.loop:
	jmp .loop
