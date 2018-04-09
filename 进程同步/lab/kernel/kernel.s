
kMain.elf:     file format elf32-i386


Disassembly of section .text:

00100000 <kEntry>:
  100000:	55                   	push   %ebp
  100001:	89 e5                	mov    %esp,%ebp
  100003:	83 ec 08             	sub    $0x8,%esp
  100006:	e8 19 00 00 00       	call   100024 <initSerial>
  10000b:	e8 74 03 00 00       	call   100384 <initIdt>
  100010:	e8 6b 00 00 00       	call   100080 <initIntr>
  100015:	e8 4a 01 00 00       	call   100164 <initSeg>
  10001a:	e8 a1 02 00 00       	call   1002c0 <loadUMain>
  10001f:	eb fe                	jmp    10001f <kEntry+0x1f>
  100021:	66 90                	xchg   %ax,%ax
  100023:	90                   	nop

00100024 <initSerial>:
  100024:	55                   	push   %ebp
  100025:	89 e5                	mov    %esp,%ebp
  100027:	ba f9 03 00 00       	mov    $0x3f9,%edx
  10002c:	31 c0                	xor    %eax,%eax
  10002e:	ee                   	out    %al,(%dx)
  10002f:	ba fb 03 00 00       	mov    $0x3fb,%edx
  100034:	b0 80                	mov    $0x80,%al
  100036:	ee                   	out    %al,(%dx)
  100037:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10003c:	b0 01                	mov    $0x1,%al
  10003e:	ee                   	out    %al,(%dx)
  10003f:	ba f9 03 00 00       	mov    $0x3f9,%edx
  100044:	31 c0                	xor    %eax,%eax
  100046:	ee                   	out    %al,(%dx)
  100047:	ba fb 03 00 00       	mov    $0x3fb,%edx
  10004c:	b0 03                	mov    $0x3,%al
  10004e:	ee                   	out    %al,(%dx)
  10004f:	ba fa 03 00 00       	mov    $0x3fa,%edx
  100054:	b0 c7                	mov    $0xc7,%al
  100056:	ee                   	out    %al,(%dx)
  100057:	ba fc 03 00 00       	mov    $0x3fc,%edx
  10005c:	b0 0b                	mov    $0xb,%al
  10005e:	ee                   	out    %al,(%dx)
  10005f:	5d                   	pop    %ebp
  100060:	c3                   	ret    
  100061:	8d 76 00             	lea    0x0(%esi),%esi

00100064 <putChar>:
  100064:	55                   	push   %ebp
  100065:	89 e5                	mov    %esp,%ebp
  100067:	8b 4d 08             	mov    0x8(%ebp),%ecx
  10006a:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10006f:	90                   	nop
  100070:	ec                   	in     (%dx),%al
  100071:	a8 20                	test   $0x20,%al
  100073:	74 fb                	je     100070 <putChar+0xc>
  100075:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10007a:	88 c8                	mov    %cl,%al
  10007c:	ee                   	out    %al,(%dx)
  10007d:	5d                   	pop    %ebp
  10007e:	c3                   	ret    
  10007f:	90                   	nop

00100080 <initIntr>:
  100080:	55                   	push   %ebp
  100081:	89 e5                	mov    %esp,%ebp
  100083:	ba 21 00 00 00       	mov    $0x21,%edx
  100088:	b0 ff                	mov    $0xff,%al
  10008a:	ee                   	out    %al,(%dx)
  10008b:	ba a1 00 00 00       	mov    $0xa1,%edx
  100090:	ee                   	out    %al,(%dx)
  100091:	ba 20 00 00 00       	mov    $0x20,%edx
  100096:	b0 11                	mov    $0x11,%al
  100098:	ee                   	out    %al,(%dx)
  100099:	ba 21 00 00 00       	mov    $0x21,%edx
  10009e:	b0 20                	mov    $0x20,%al
  1000a0:	ee                   	out    %al,(%dx)
  1000a1:	b0 04                	mov    $0x4,%al
  1000a3:	ee                   	out    %al,(%dx)
  1000a4:	b0 03                	mov    $0x3,%al
  1000a6:	ee                   	out    %al,(%dx)
  1000a7:	ba a0 00 00 00       	mov    $0xa0,%edx
  1000ac:	b0 11                	mov    $0x11,%al
  1000ae:	ee                   	out    %al,(%dx)
  1000af:	ba a1 00 00 00       	mov    $0xa1,%edx
  1000b4:	b0 28                	mov    $0x28,%al
  1000b6:	ee                   	out    %al,(%dx)
  1000b7:	b0 02                	mov    $0x2,%al
  1000b9:	ee                   	out    %al,(%dx)
  1000ba:	b0 03                	mov    $0x3,%al
  1000bc:	ee                   	out    %al,(%dx)
  1000bd:	ba 20 00 00 00       	mov    $0x20,%edx
  1000c2:	b0 68                	mov    $0x68,%al
  1000c4:	ee                   	out    %al,(%dx)
  1000c5:	b0 0a                	mov    $0xa,%al
  1000c7:	ee                   	out    %al,(%dx)
  1000c8:	ba a0 00 00 00       	mov    $0xa0,%edx
  1000cd:	b0 68                	mov    $0x68,%al
  1000cf:	ee                   	out    %al,(%dx)
  1000d0:	b0 0a                	mov    $0xa,%al
  1000d2:	ee                   	out    %al,(%dx)
  1000d3:	5d                   	pop    %ebp
  1000d4:	c3                   	ret    
  1000d5:	66 90                	xchg   %ax,%ax
  1000d7:	90                   	nop

001000d8 <waitDisk>:
  1000d8:	55                   	push   %ebp
  1000d9:	89 e5                	mov    %esp,%ebp
  1000db:	ba f7 01 00 00       	mov    $0x1f7,%edx
  1000e0:	ec                   	in     (%dx),%al
  1000e1:	83 e0 c0             	and    $0xffffffc0,%eax
  1000e4:	3c 40                	cmp    $0x40,%al
  1000e6:	75 f8                	jne    1000e0 <waitDisk+0x8>
  1000e8:	5d                   	pop    %ebp
  1000e9:	c3                   	ret    
  1000ea:	66 90                	xchg   %ax,%ax

001000ec <readSect>:
  1000ec:	55                   	push   %ebp
  1000ed:	89 e5                	mov    %esp,%ebp
  1000ef:	53                   	push   %ebx
  1000f0:	8b 4d 0c             	mov    0xc(%ebp),%ecx
  1000f3:	ba f7 01 00 00       	mov    $0x1f7,%edx
  1000f8:	ec                   	in     (%dx),%al
  1000f9:	83 e0 c0             	and    $0xffffffc0,%eax
  1000fc:	3c 40                	cmp    $0x40,%al
  1000fe:	75 f8                	jne    1000f8 <readSect+0xc>
  100100:	ba f2 01 00 00       	mov    $0x1f2,%edx
  100105:	b0 01                	mov    $0x1,%al
  100107:	ee                   	out    %al,(%dx)
  100108:	ba f3 01 00 00       	mov    $0x1f3,%edx
  10010d:	88 c8                	mov    %cl,%al
  10010f:	ee                   	out    %al,(%dx)
  100110:	89 c8                	mov    %ecx,%eax
  100112:	c1 f8 08             	sar    $0x8,%eax
  100115:	ba f4 01 00 00       	mov    $0x1f4,%edx
  10011a:	ee                   	out    %al,(%dx)
  10011b:	89 c8                	mov    %ecx,%eax
  10011d:	c1 f8 10             	sar    $0x10,%eax
  100120:	ba f5 01 00 00       	mov    $0x1f5,%edx
  100125:	ee                   	out    %al,(%dx)
  100126:	89 c8                	mov    %ecx,%eax
  100128:	c1 f8 18             	sar    $0x18,%eax
  10012b:	83 c8 e0             	or     $0xffffffe0,%eax
  10012e:	ba f6 01 00 00       	mov    $0x1f6,%edx
  100133:	ee                   	out    %al,(%dx)
  100134:	ba f7 01 00 00       	mov    $0x1f7,%edx
  100139:	b0 20                	mov    $0x20,%al
  10013b:	ee                   	out    %al,(%dx)
  10013c:	ec                   	in     (%dx),%al
  10013d:	83 e0 c0             	and    $0xffffffc0,%eax
  100140:	3c 40                	cmp    $0x40,%al
  100142:	75 f8                	jne    10013c <readSect+0x50>
  100144:	8b 4d 08             	mov    0x8(%ebp),%ecx
  100147:	8d 99 00 02 00 00    	lea    0x200(%ecx),%ebx
  10014d:	ba f0 01 00 00       	mov    $0x1f0,%edx
  100152:	66 90                	xchg   %ax,%ax
  100154:	ed                   	in     (%dx),%eax
  100155:	89 01                	mov    %eax,(%ecx)
  100157:	83 c1 04             	add    $0x4,%ecx
  10015a:	39 d9                	cmp    %ebx,%ecx
  10015c:	75 f6                	jne    100154 <readSect+0x68>
  10015e:	5b                   	pop    %ebx
  10015f:	5d                   	pop    %ebp
  100160:	c3                   	ret    
  100161:	8d 76 00             	lea    0x0(%esi),%esi

00100164 <initSeg>:
  100164:	55                   	push   %ebp
  100165:	89 e5                	mov    %esp,%ebp
  100167:	ba a0 12 10 00       	mov    $0x1012a0,%edx
  10016c:	66 c7 05 a8 12 10 00 	movw   $0xffff,0x1012a8
  100173:	ff ff 
  100175:	66 c7 05 aa 12 10 00 	movw   $0x0,0x1012aa
  10017c:	00 00 
  10017e:	c6 05 ac 12 10 00 00 	movb   $0x0,0x1012ac
  100185:	c6 05 ad 12 10 00 9a 	movb   $0x9a,0x1012ad
  10018c:	c6 05 ae 12 10 00 cf 	movb   $0xcf,0x1012ae
  100193:	c6 05 af 12 10 00 00 	movb   $0x0,0x1012af
  10019a:	66 c7 05 b0 12 10 00 	movw   $0xffff,0x1012b0
  1001a1:	ff ff 
  1001a3:	66 c7 05 b2 12 10 00 	movw   $0x0,0x1012b2
  1001aa:	00 00 
  1001ac:	c6 05 b4 12 10 00 00 	movb   $0x0,0x1012b4
  1001b3:	c6 05 b5 12 10 00 92 	movb   $0x92,0x1012b5
  1001ba:	c6 05 b6 12 10 00 cf 	movb   $0xcf,0x1012b6
  1001c1:	c6 05 b7 12 10 00 00 	movb   $0x0,0x1012b7
  1001c8:	66 c7 05 b8 12 10 00 	movw   $0xffff,0x1012b8
  1001cf:	ff ff 
  1001d1:	66 c7 05 ba 12 10 00 	movw   $0x0,0x1012ba
  1001d8:	00 00 
  1001da:	c6 05 bc 12 10 00 00 	movb   $0x0,0x1012bc
  1001e1:	c6 05 bd 12 10 00 fa 	movb   $0xfa,0x1012bd
  1001e8:	c6 05 be 12 10 00 cf 	movb   $0xcf,0x1012be
  1001ef:	c6 05 bf 12 10 00 00 	movb   $0x0,0x1012bf
  1001f6:	66 c7 05 c0 12 10 00 	movw   $0xffff,0x1012c0
  1001fd:	ff ff 
  1001ff:	66 c7 05 c2 12 10 00 	movw   $0x0,0x1012c2
  100206:	00 00 
  100208:	c6 05 c4 12 10 00 00 	movb   $0x0,0x1012c4
  10020f:	c6 05 c5 12 10 00 f2 	movb   $0xf2,0x1012c5
  100216:	c6 05 c6 12 10 00 cf 	movb   $0xcf,0x1012c6
  10021d:	c6 05 c7 12 10 00 00 	movb   $0x0,0x1012c7
  100224:	66 c7 05 c8 12 10 00 	movw   $0x63,0x1012c8
  10022b:	63 00 
  10022d:	b8 e0 12 10 00       	mov    $0x1012e0,%eax
  100232:	66 a3 ca 12 10 00    	mov    %ax,0x1012ca
  100238:	89 c1                	mov    %eax,%ecx
  10023a:	c1 e9 10             	shr    $0x10,%ecx
  10023d:	88 0d cc 12 10 00    	mov    %cl,0x1012cc
  100243:	c6 05 cd 12 10 00 89 	movb   $0x89,0x1012cd
  10024a:	c6 05 ce 12 10 00 40 	movb   $0x40,0x1012ce
  100251:	c1 e8 18             	shr    $0x18,%eax
  100254:	a2 cf 12 10 00       	mov    %al,0x1012cf
  100259:	66 c7 05 00 11 10 00 	movw   $0x37,0x101100
  100260:	37 00 
  100262:	66 89 15 02 11 10 00 	mov    %dx,0x101102
  100269:	c1 ea 10             	shr    $0x10,%edx
  10026c:	66 89 15 04 11 10 00 	mov    %dx,0x101104
  100273:	b8 00 11 10 00       	mov    $0x101100,%eax
  100278:	0f 01 10             	lgdtl  (%eax)
  10027b:	c7 05 e8 12 10 00 10 	movl   $0x10,0x1012e8
  100282:	00 00 00 
  100285:	c7 05 e4 12 10 00 00 	movl   $0x20000,0x1012e4
  10028c:	00 02 00 
  10028f:	b8 28 00 00 00       	mov    $0x28,%eax
  100294:	0f 00 d8             	ltr    %ax
  100297:	31 c0                	xor    %eax,%eax
  100299:	0f 00 d0             	lldt   %ax
  10029c:	5d                   	pop    %ebp
  10029d:	c3                   	ret    
  10029e:	66 90                	xchg   %ax,%ax

001002a0 <enterUserSpace>:
  1002a0:	55                   	push   %ebp
  1002a1:	89 e5                	mov    %esp,%ebp
  1002a3:	83 ec 10             	sub    $0x10,%esp
  1002a6:	c7 45 fc 02 00 00 00 	movl   $0x2,-0x4(%ebp)
  1002ad:	66 c7 45 fa 08 00    	movw   $0x8,-0x6(%ebp)
  1002b3:	ff 75 fc             	pushl  -0x4(%ebp)
  1002b6:	66 ff 75 fa          	pushw  -0x6(%ebp)
  1002ba:	ff 75 08             	pushl  0x8(%ebp)
  1002bd:	cf                   	iret   
  1002be:	c9                   	leave  
  1002bf:	c3                   	ret    

001002c0 <loadUMain>:
  1002c0:	55                   	push   %ebp
  1002c1:	89 e5                	mov    %esp,%ebp
  1002c3:	57                   	push   %edi
  1002c4:	56                   	push   %esi
  1002c5:	53                   	push   %ebx
  1002c6:	81 ec 10 28 00 00    	sub    $0x2810,%esp
  1002cc:	8d 9d f4 d7 ff ff    	lea    -0x280c(%ebp),%ebx
  1002d2:	8d 7d f4             	lea    -0xc(%ebp),%edi
  1002d5:	be c9 00 00 00       	mov    $0xc9,%esi
  1002da:	66 90                	xchg   %ax,%ax
  1002dc:	56                   	push   %esi
  1002dd:	53                   	push   %ebx
  1002de:	e8 09 fe ff ff       	call   1000ec <readSect>
  1002e3:	81 c3 00 02 00 00    	add    $0x200,%ebx
  1002e9:	46                   	inc    %esi
  1002ea:	58                   	pop    %eax
  1002eb:	5a                   	pop    %edx
  1002ec:	39 fb                	cmp    %edi,%ebx
  1002ee:	75 ec                	jne    1002dc <loadUMain+0x1c>
  1002f0:	8d 95 f4 d7 ff ff    	lea    -0x280c(%ebp),%edx
  1002f6:	03 95 10 d8 ff ff    	add    -0x27f0(%ebp),%edx
  1002fc:	0f b7 8d 20 d8 ff ff 	movzwl -0x27e0(%ebp),%ecx
  100303:	8d 59 ff             	lea    -0x1(%ecx),%ebx
  100306:	31 c0                	xor    %eax,%eax
  100308:	85 c9                	test   %ecx,%ecx
  10030a:	75 0d                	jne    100319 <loadUMain+0x59>
  10030c:	eb 39                	jmp    100347 <loadUMain+0x87>
  10030e:	66 90                	xchg   %ax,%ax
  100310:	83 c2 20             	add    $0x20,%edx
  100313:	4b                   	dec    %ebx
  100314:	83 fb ff             	cmp    $0xffffffff,%ebx
  100317:	74 2e                	je     100347 <loadUMain+0x87>
  100319:	83 3a 01             	cmpl   $0x1,(%edx)
  10031c:	75 f2                	jne    100310 <loadUMain+0x50>
  10031e:	8d b5 f4 d7 ff ff    	lea    -0x280c(%ebp),%esi
  100324:	03 72 04             	add    0x4(%edx),%esi
  100327:	8b 4a 10             	mov    0x10(%edx),%ecx
  10032a:	8b 7a 08             	mov    0x8(%edx),%edi
  10032d:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
  10032f:	8b 72 10             	mov    0x10(%edx),%esi
  100332:	8b 4a 14             	mov    0x14(%edx),%ecx
  100335:	29 f1                	sub    %esi,%ecx
  100337:	03 72 08             	add    0x8(%edx),%esi
  10033a:	89 f7                	mov    %esi,%edi
  10033c:	f3 aa                	rep stos %al,%es:(%edi)
  10033e:	83 c2 20             	add    $0x20,%edx
  100341:	4b                   	dec    %ebx
  100342:	83 fb ff             	cmp    $0xffffffff,%ebx
  100345:	75 d2                	jne    100319 <loadUMain+0x59>
  100347:	8b 85 0c d8 ff ff    	mov    -0x27f4(%ebp),%eax
  10034d:	89 85 ec d7 ff ff    	mov    %eax,-0x2814(%ebp)
  100353:	c7 85 f0 d7 ff ff 02 	movl   $0x2,-0x2810(%ebp)
  10035a:	00 00 00 
  10035d:	66 c7 85 ea d7 ff ff 	movw   $0x8,-0x2816(%ebp)
  100364:	08 00 
  100366:	ff b5 f0 d7 ff ff    	pushl  -0x2810(%ebp)
  10036c:	66 ff b5 ea d7 ff ff 	pushw  -0x2816(%ebp)
  100373:	ff b5 ec d7 ff ff    	pushl  -0x2814(%ebp)
  100379:	cf                   	iret   
  10037a:	8d 65 f4             	lea    -0xc(%ebp),%esp
  10037d:	5b                   	pop    %ebx
  10037e:	5e                   	pop    %esi
  10037f:	5f                   	pop    %edi
  100380:	5d                   	pop    %ebp
  100381:	c3                   	ret    
  100382:	66 90                	xchg   %ax,%ax

00100384 <initIdt>:
  100384:	55                   	push   %ebp
  100385:	89 e5                	mov    %esp,%ebp
  100387:	53                   	push   %ebx
  100388:	ba db 06 10 00       	mov    $0x1006db,%edx
  10038d:	89 d3                	mov    %edx,%ebx
  10038f:	c1 ea 10             	shr    $0x10,%edx
  100392:	b9 60 1b 10 00       	mov    $0x101b60,%ecx
  100397:	b8 60 13 10 00       	mov    $0x101360,%eax
  10039c:	66 89 18             	mov    %bx,(%eax)
  10039f:	66 c7 40 02 08 00    	movw   $0x8,0x2(%eax)
  1003a5:	c6 40 04 00          	movb   $0x0,0x4(%eax)
  1003a9:	c6 40 05 8f          	movb   $0x8f,0x5(%eax)
  1003ad:	66 89 50 06          	mov    %dx,0x6(%eax)
  1003b1:	83 c0 08             	add    $0x8,%eax
  1003b4:	39 c1                	cmp    %eax,%ecx
  1003b6:	75 e4                	jne    10039c <initIdt+0x18>
  1003b8:	b8 e4 06 10 00       	mov    $0x1006e4,%eax
  1003bd:	66 a3 c8 13 10 00    	mov    %ax,0x1013c8
  1003c3:	66 c7 05 ca 13 10 00 	movw   $0x8,0x1013ca
  1003ca:	08 00 
  1003cc:	c6 05 cc 13 10 00 00 	movb   $0x0,0x1013cc
  1003d3:	c6 05 cd 13 10 00 8f 	movb   $0x8f,0x1013cd
  1003da:	c1 e8 10             	shr    $0x10,%eax
  1003dd:	66 a3 ce 13 10 00    	mov    %ax,0x1013ce
  1003e3:	b8 eb 06 10 00       	mov    $0x1006eb,%eax
  1003e8:	66 a3 60 17 10 00    	mov    %ax,0x101760
  1003ee:	66 c7 05 62 17 10 00 	movw   $0x8,0x101762
  1003f5:	08 00 
  1003f7:	c6 05 64 17 10 00 00 	movb   $0x0,0x101764
  1003fe:	c6 05 65 17 10 00 ee 	movb   $0xee,0x101765
  100405:	c1 e8 10             	shr    $0x10,%eax
  100408:	66 a3 66 17 10 00    	mov    %ax,0x101766
  10040e:	66 c7 05 08 11 10 00 	movw   $0x7ff,0x101108
  100415:	ff 07 
  100417:	b8 60 13 10 00       	mov    $0x101360,%eax
  10041c:	66 a3 0a 11 10 00    	mov    %ax,0x10110a
  100422:	c1 e8 10             	shr    $0x10,%eax
  100425:	66 a3 0c 11 10 00    	mov    %ax,0x10110c
  10042b:	b8 08 11 10 00       	mov    $0x101108,%eax
  100430:	0f 01 18             	lidtl  (%eax)
  100433:	5b                   	pop    %ebx
  100434:	5d                   	pop    %ebp
  100435:	c3                   	ret    
  100436:	66 90                	xchg   %ax,%ax

00100438 <add_irq_handle>:
  100438:	55                   	push   %ebp
  100439:	89 e5                	mov    %esp,%ebp
  10043b:	53                   	push   %ebx
  10043c:	50                   	push   %eax
  10043d:	8b 5d 08             	mov    0x8(%ebp),%ebx
  100440:	83 fb 0f             	cmp    $0xf,%ebx
  100443:	7f 57                	jg     10049c <add_irq_handle+0x64>
  100445:	a1 2c 11 10 00       	mov    0x10112c,%eax
  10044a:	83 f8 20             	cmp    $0x20,%eax
  10044d:	7e 17                	jle    100466 <add_irq_handle+0x2e>
  10044f:	83 ec 08             	sub    $0x8,%esp
  100452:	6a 22                	push   $0x22
  100454:	68 09 07 10 00       	push   $0x100709
  100459:	e8 e6 01 00 00       	call   100644 <abort>
  10045e:	a1 2c 11 10 00       	mov    0x10112c,%eax
  100463:	83 c4 10             	add    $0x10,%esp
  100466:	8d 50 01             	lea    0x1(%eax),%edx
  100469:	89 15 2c 11 10 00    	mov    %edx,0x10112c
  10046f:	8b 55 0c             	mov    0xc(%ebp),%edx
  100472:	89 14 c5 80 11 10 00 	mov    %edx,0x101180(,%eax,8)
  100479:	8b 14 9d 40 11 10 00 	mov    0x101140(,%ebx,4),%edx
  100480:	89 14 c5 84 11 10 00 	mov    %edx,0x101184(,%eax,8)
  100487:	8d 04 c5 80 11 10 00 	lea    0x101180(,%eax,8),%eax
  10048e:	89 04 9d 40 11 10 00 	mov    %eax,0x101140(,%ebx,4)
  100495:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  100498:	c9                   	leave  
  100499:	c3                   	ret    
  10049a:	66 90                	xchg   %ax,%ax
  10049c:	83 ec 08             	sub    $0x8,%esp
  10049f:	6a 21                	push   $0x21
  1004a1:	68 09 07 10 00       	push   $0x100709
  1004a6:	e8 99 01 00 00       	call   100644 <abort>
  1004ab:	83 c4 10             	add    $0x10,%esp
  1004ae:	eb 95                	jmp    100445 <add_irq_handle+0xd>

001004b0 <syscallHandle>:
  1004b0:	55                   	push   %ebp
  1004b1:	89 e5                	mov    %esp,%ebp
  1004b3:	57                   	push   %edi
  1004b4:	56                   	push   %esi
  1004b5:	53                   	push   %ebx
  1004b6:	83 ec 1c             	sub    $0x1c,%esp
  1004b9:	8b 5d 08             	mov    0x8(%ebp),%ebx
  1004bc:	8b 43 1c             	mov    0x1c(%ebx),%eax
  1004bf:	85 c0                	test   %eax,%eax
  1004c1:	74 35                	je     1004f8 <syscallHandle+0x48>
  1004c3:	83 f8 2d             	cmp    $0x2d,%eax
  1004c6:	74 14                	je     1004dc <syscallHandle+0x2c>
  1004c8:	83 f8 36             	cmp    $0x36,%eax
  1004cb:	74 47                	je     100514 <syscallHandle+0x64>
  1004cd:	83 f8 04             	cmp    $0x4,%eax
  1004d0:	74 62                	je     100534 <syscallHandle+0x84>
  1004d2:	8d 65 f4             	lea    -0xc(%ebp),%esp
  1004d5:	5b                   	pop    %ebx
  1004d6:	5e                   	pop    %esi
  1004d7:	5f                   	pop    %edi
  1004d8:	5d                   	pop    %ebp
  1004d9:	c3                   	ret    
  1004da:	66 90                	xchg   %ax,%ax
  1004dc:	8b 43 10             	mov    0x10(%ebx),%eax
  1004df:	85 c0                	test   %eax,%eax
  1004e1:	74 49                	je     10052c <syscallHandle+0x7c>
  1004e3:	39 05 20 11 10 00    	cmp    %eax,0x101120
  1004e9:	73 05                	jae    1004f0 <syscallHandle+0x40>
  1004eb:	a3 20 11 10 00       	mov    %eax,0x101120
  1004f0:	a3 24 11 10 00       	mov    %eax,0x101124
  1004f5:	eb 28                	jmp    10051f <syscallHandle+0x6f>
  1004f7:	90                   	nop
  1004f8:	fb                   	sti    
  1004f9:	83 ec 08             	sub    $0x8,%esp
  1004fc:	ff 73 18             	pushl  0x18(%ebx)
  1004ff:	ff 73 10             	pushl  0x10(%ebx)
  100502:	e8 31 ff ff ff       	call   100438 <add_irq_handle>
  100507:	fa                   	cli    
  100508:	83 c4 10             	add    $0x10,%esp
  10050b:	8d 65 f4             	lea    -0xc(%ebp),%esp
  10050e:	5b                   	pop    %ebx
  10050f:	5e                   	pop    %esi
  100510:	5f                   	pop    %edi
  100511:	5d                   	pop    %ebp
  100512:	c3                   	ret    
  100513:	90                   	nop
  100514:	31 c0                	xor    %eax,%eax
  100516:	83 7b 10 02          	cmpl   $0x2,0x10(%ebx)
  10051a:	0f 97 c0             	seta   %al
  10051d:	f7 d8                	neg    %eax
  10051f:	89 43 1c             	mov    %eax,0x1c(%ebx)
  100522:	8d 65 f4             	lea    -0xc(%ebp),%esp
  100525:	5b                   	pop    %ebx
  100526:	5e                   	pop    %esi
  100527:	5f                   	pop    %edi
  100528:	5d                   	pop    %ebp
  100529:	c3                   	ret    
  10052a:	66 90                	xchg   %ax,%ax
  10052c:	a1 24 11 10 00       	mov    0x101124,%eax
  100531:	eb ec                	jmp    10051f <syscallHandle+0x6f>
  100533:	90                   	nop
  100534:	8b 0d 28 11 10 00    	mov    0x101128,%ecx
  10053a:	8d 94 09 00 80 0b 00 	lea    0xb8000(%ecx,%ecx,1),%edx
  100541:	8b 7b 18             	mov    0x18(%ebx),%edi
  100544:	8b 43 14             	mov    0x14(%ebx),%eax
  100547:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  10054a:	85 c0                	test   %eax,%eax
  10054c:	74 84                	je     1004d2 <syscallHandle+0x22>
  10054e:	31 db                	xor    %ebx,%ebx
  100550:	31 f6                	xor    %esi,%esi
  100552:	eb 11                	jmp    100565 <syscallHandle+0xb5>
  100554:	05 00 0c 00 00       	add    $0xc00,%eax
  100559:	66 89 04 4a          	mov    %ax,(%edx,%ecx,2)
  10055d:	41                   	inc    %ecx
  10055e:	46                   	inc    %esi
  10055f:	43                   	inc    %ebx
  100560:	39 5d e4             	cmp    %ebx,-0x1c(%ebp)
  100563:	76 30                	jbe    100595 <syscallHandle+0xe5>
  100565:	66 0f be 04 3b       	movsbw (%ebx,%edi,1),%ax
  10056a:	3c 0a                	cmp    $0xa,%al
  10056c:	75 e6                	jne    100554 <syscallHandle+0xa4>
  10056e:	b8 67 66 66 66       	mov    $0x66666667,%eax
  100573:	f7 e9                	imul   %ecx
  100575:	89 d0                	mov    %edx,%eax
  100577:	c1 f8 05             	sar    $0x5,%eax
  10057a:	c1 f9 1f             	sar    $0x1f,%ecx
  10057d:	29 c8                	sub    %ecx,%eax
  10057f:	8d 4c 80 05          	lea    0x5(%eax,%eax,4),%ecx
  100583:	c1 e1 04             	shl    $0x4,%ecx
  100586:	8d 94 36 00 80 0b 00 	lea    0xb8000(%esi,%esi,1),%edx
  10058d:	31 f6                	xor    %esi,%esi
  10058f:	43                   	inc    %ebx
  100590:	39 5d e4             	cmp    %ebx,-0x1c(%ebp)
  100593:	77 d0                	ja     100565 <syscallHandle+0xb5>
  100595:	89 0d 28 11 10 00    	mov    %ecx,0x101128
  10059b:	8d 65 f4             	lea    -0xc(%ebp),%esp
  10059e:	5b                   	pop    %ebx
  10059f:	5e                   	pop    %esi
  1005a0:	5f                   	pop    %edi
  1005a1:	5d                   	pop    %ebp
  1005a2:	c3                   	ret    
  1005a3:	90                   	nop

001005a4 <irqHandle>:
  1005a4:	55                   	push   %ebp
  1005a5:	89 e5                	mov    %esp,%ebp
  1005a7:	83 ec 08             	sub    $0x8,%esp
  1005aa:	8b 55 08             	mov    0x8(%ebp),%edx
  1005ad:	8b 42 20             	mov    0x20(%edx),%eax
  1005b0:	83 f8 0d             	cmp    $0xd,%eax
  1005b3:	74 2b                	je     1005e0 <irqHandle+0x3c>
  1005b5:	3d 80 00 00 00       	cmp    $0x80,%eax
  1005ba:	74 18                	je     1005d4 <irqHandle+0x30>
  1005bc:	40                   	inc    %eax
  1005bd:	74 12                	je     1005d1 <irqHandle+0x2d>
  1005bf:	83 ec 08             	sub    $0x8,%esp
  1005c2:	6a 39                	push   $0x39
  1005c4:	68 09 07 10 00       	push   $0x100709
  1005c9:	e8 76 00 00 00       	call   100644 <abort>
  1005ce:	83 c4 10             	add    $0x10,%esp
  1005d1:	c9                   	leave  
  1005d2:	c3                   	ret    
  1005d3:	90                   	nop
  1005d4:	89 55 08             	mov    %edx,0x8(%ebp)
  1005d7:	c9                   	leave  
  1005d8:	e9 d3 fe ff ff       	jmp    1004b0 <syscallHandle>
  1005dd:	8d 76 00             	lea    0x0(%esi),%esi
  1005e0:	83 ec 08             	sub    $0x8,%esp
  1005e3:	6a 67                	push   $0x67
  1005e5:	68 09 07 10 00       	push   $0x100709
  1005ea:	e8 55 00 00 00       	call   100644 <abort>
  1005ef:	83 c4 10             	add    $0x10,%esp
  1005f2:	c9                   	leave  
  1005f3:	c3                   	ret    

001005f4 <GProtectFaultHandle>:
  1005f4:	55                   	push   %ebp
  1005f5:	89 e5                	mov    %esp,%ebp
  1005f7:	83 ec 10             	sub    $0x10,%esp
  1005fa:	6a 67                	push   $0x67
  1005fc:	68 09 07 10 00       	push   $0x100709
  100601:	e8 3e 00 00 00       	call   100644 <abort>
  100606:	83 c4 10             	add    $0x10,%esp
  100609:	c9                   	leave  
  10060a:	c3                   	ret    
  10060b:	90                   	nop

0010060c <mm_brk>:
  10060c:	55                   	push   %ebp
  10060d:	89 e5                	mov    %esp,%ebp
  10060f:	8b 45 08             	mov    0x8(%ebp),%eax
  100612:	85 c0                	test   %eax,%eax
  100614:	74 16                	je     10062c <mm_brk+0x20>
  100616:	3b 05 20 11 10 00    	cmp    0x101120,%eax
  10061c:	76 05                	jbe    100623 <mm_brk+0x17>
  10061e:	a3 20 11 10 00       	mov    %eax,0x101120
  100623:	a3 24 11 10 00       	mov    %eax,0x101124
  100628:	5d                   	pop    %ebp
  100629:	c3                   	ret    
  10062a:	66 90                	xchg   %ax,%ax
  10062c:	a1 24 11 10 00       	mov    0x101124,%eax
  100631:	5d                   	pop    %ebp
  100632:	c3                   	ret    
  100633:	90                   	nop

00100634 <fs_ioctl>:
  100634:	55                   	push   %ebp
  100635:	89 e5                	mov    %esp,%ebp
  100637:	31 c0                	xor    %eax,%eax
  100639:	83 7d 08 02          	cmpl   $0x2,0x8(%ebp)
  10063d:	0f 97 c0             	seta   %al
  100640:	f7 d8                	neg    %eax
  100642:	5d                   	pop    %ebp
  100643:	c3                   	ret    

00100644 <abort>:
  100644:	55                   	push   %ebp
  100645:	89 e5                	mov    %esp,%ebp
  100647:	57                   	push   %edi
  100648:	56                   	push   %esi
  100649:	53                   	push   %ebx
  10064a:	83 ec 1c             	sub    $0x1c,%esp
  10064d:	8b 55 08             	mov    0x8(%ebp),%edx
  100650:	fa                   	cli    
  100651:	8a 02                	mov    (%edx),%al
  100653:	b9 12 10 10 00       	mov    $0x101012,%ecx
  100658:	84 c0                	test   %al,%al
  10065a:	74 0b                	je     100667 <abort+0x23>
  10065c:	41                   	inc    %ecx
  10065d:	42                   	inc    %edx
  10065e:	88 41 ff             	mov    %al,-0x1(%ecx)
  100661:	8a 02                	mov    (%edx),%al
  100663:	84 c0                	test   %al,%al
  100665:	75 f5                	jne    10065c <abort+0x18>
  100667:	c6 01 3a             	movb   $0x3a,(%ecx)
  10066a:	bb 9d 12 10 00       	mov    $0x10129d,%ebx
  10066f:	be 0a 00 00 00       	mov    $0xa,%esi
  100674:	bf 67 66 66 66       	mov    $0x66666667,%edi
  100679:	4b                   	dec    %ebx
  10067a:	8b 45 0c             	mov    0xc(%ebp),%eax
  10067d:	99                   	cltd   
  10067e:	f7 fe                	idiv   %esi
  100680:	8d 42 30             	lea    0x30(%edx),%eax
  100683:	88 45 e7             	mov    %al,-0x19(%ebp)
  100686:	88 03                	mov    %al,(%ebx)
  100688:	89 f8                	mov    %edi,%eax
  10068a:	f7 6d 0c             	imull  0xc(%ebp)
  10068d:	c1 fa 02             	sar    $0x2,%edx
  100690:	8b 45 0c             	mov    0xc(%ebp),%eax
  100693:	c1 f8 1f             	sar    $0x1f,%eax
  100696:	29 c2                	sub    %eax,%edx
  100698:	89 55 0c             	mov    %edx,0xc(%ebp)
  10069b:	75 dc                	jne    100679 <abort+0x35>
  10069d:	41                   	inc    %ecx
  10069e:	41                   	inc    %ecx
  10069f:	43                   	inc    %ebx
  1006a0:	8a 45 e7             	mov    -0x19(%ebp),%al
  1006a3:	88 41 ff             	mov    %al,-0x1(%ecx)
  1006a6:	8a 03                	mov    (%ebx),%al
  1006a8:	88 45 e7             	mov    %al,-0x19(%ebp)
  1006ab:	84 c0                	test   %al,%al
  1006ad:	75 ef                	jne    10069e <abort+0x5a>
  1006af:	c6 01 0a             	movb   $0xa,(%ecx)
  1006b2:	0f be 05 00 10 10 00 	movsbl 0x101000,%eax
  1006b9:	84 c0                	test   %al,%al
  1006bb:	74 1b                	je     1006d8 <abort+0x94>
  1006bd:	bb 00 10 10 00       	mov    $0x101000,%ebx
  1006c2:	83 ec 0c             	sub    $0xc,%esp
  1006c5:	50                   	push   %eax
  1006c6:	e8 99 f9 ff ff       	call   100064 <putChar>
  1006cb:	43                   	inc    %ebx
  1006cc:	0f be 03             	movsbl (%ebx),%eax
  1006cf:	83 c4 10             	add    $0x10,%esp
  1006d2:	84 c0                	test   %al,%al
  1006d4:	75 ec                	jne    1006c2 <abort+0x7e>
  1006d6:	66 90                	xchg   %ax,%ax
  1006d8:	f4                   	hlt    
  1006d9:	eb fd                	jmp    1006d8 <abort+0x94>

001006db <irqEmpty>:
  1006db:	6a 00                	push   $0x0
  1006dd:	6a ff                	push   $0xffffffff
  1006df:	e9 13 00 00 00       	jmp    1006f7 <asmDoIrq>

001006e4 <irqGProtectFault>:
  1006e4:	6a 0d                	push   $0xd
  1006e6:	e9 0c 00 00 00       	jmp    1006f7 <asmDoIrq>

001006eb <irqSyscall>:
  1006eb:	6a 00                	push   $0x0
  1006ed:	68 80 00 00 00       	push   $0x80
  1006f2:	e9 00 00 00 00       	jmp    1006f7 <asmDoIrq>

001006f7 <asmDoIrq>:
  1006f7:	60                   	pusha  
  1006f8:	54                   	push   %esp
  1006f9:	e8 a6 fe ff ff       	call   1005a4 <irqHandle>
  1006fe:	83 c4 04             	add    $0x4,%esp
  100701:	61                   	popa   
  100702:	83 c4 04             	add    $0x4,%esp
  100705:	83 c4 04             	add    $0x4,%esp
  100708:	cf                   	iret   
