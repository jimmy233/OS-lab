
bootloader.elf:     file format elf32-i386


Disassembly of section .text:

00007c00 <start>:
    7c00:	fa                   	cli    
    7c01:	e4 92                	in     $0x92,%al
    7c03:	0c 02                	or     $0x2,%al
    7c05:	e6 92                	out    %al,$0x92
    7c07:	67 66 0f 01 15       	lgdtw  (%di)
    7c0c:	54                   	push   %esp
    7c0d:	7c 00                	jl     7c0f <start+0xf>
    7c0f:	00 0f                	add    %cl,(%edi)
    7c11:	20 c0                	and    %al,%al
    7c13:	0c 01                	or     $0x1,%al
    7c15:	0f 22 c0             	mov    %eax,%cr0
    7c18:	66 ea 20 7c 00 00    	ljmpw  $0x0,$0x7c20
    7c1e:	08 00                	or     %al,(%eax)

00007c20 <start32>:
    7c20:	66 b8 10 00          	mov    $0x10,%ax
    7c24:	8e d8                	mov    %eax,%ds
    7c26:	8e e0                	mov    %eax,%fs
    7c28:	8e d0                	mov    %eax,%ss
    7c2a:	8e c0                	mov    %eax,%es
    7c2c:	bd 00 00 00 00       	mov    $0x0,%ebp
    7c31:	bc ff ff ff 00       	mov    $0xffffff,%esp
    7c36:	e9 b9 00 00 00       	jmp    7cf4 <bootMain>
    7c3b:	90                   	nop

00007c3c <gdt>:
	...
    7c44:	ff                   	(bad)  
    7c45:	ff 00                	incl   (%eax)
    7c47:	00 00                	add    %al,(%eax)
    7c49:	9a cf 00 ff ff 00 00 	lcall  $0x0,$0xffff00cf
    7c50:	00 92 cf 00 17 00    	add    %dl,0x1700cf(%edx)

00007c54 <gdtDesc>:
    7c54:	17                   	pop    %ss
    7c55:	00 3c 7c             	add    %bh,(%esp,%edi,2)
    7c58:	00 00                	add    %al,(%eax)
    7c5a:	66 90                	xchg   %ax,%ax

00007c5c <waitDisk>:
    7c5c:	55                   	push   %ebp
    7c5d:	89 e5                	mov    %esp,%ebp
    7c5f:	ba f7 01 00 00       	mov    $0x1f7,%edx
    7c64:	ec                   	in     (%dx),%al
    7c65:	25 c0 00 00 00       	and    $0xc0,%eax
    7c6a:	83 f8 40             	cmp    $0x40,%eax
    7c6d:	75 f5                	jne    7c64 <waitDisk+0x8>
    7c6f:	5d                   	pop    %ebp
    7c70:	c3                   	ret    
    7c71:	8d 76 00             	lea    0x0(%esi),%esi

00007c74 <readSect>:
    7c74:	55                   	push   %ebp
    7c75:	89 e5                	mov    %esp,%ebp
    7c77:	53                   	push   %ebx
    7c78:	8b 4d 0c             	mov    0xc(%ebp),%ecx
    7c7b:	ba f7 01 00 00       	mov    $0x1f7,%edx
    7c80:	ec                   	in     (%dx),%al
    7c81:	25 c0 00 00 00       	and    $0xc0,%eax
    7c86:	83 f8 40             	cmp    $0x40,%eax
    7c89:	75 f5                	jne    7c80 <readSect+0xc>
    7c8b:	ba f2 01 00 00       	mov    $0x1f2,%edx
    7c90:	b0 01                	mov    $0x1,%al
    7c92:	ee                   	out    %al,(%dx)
    7c93:	ba f3 01 00 00       	mov    $0x1f3,%edx
    7c98:	88 c8                	mov    %cl,%al
    7c9a:	ee                   	out    %al,(%dx)
    7c9b:	89 c8                	mov    %ecx,%eax
    7c9d:	c1 f8 08             	sar    $0x8,%eax
    7ca0:	ba f4 01 00 00       	mov    $0x1f4,%edx
    7ca5:	ee                   	out    %al,(%dx)
    7ca6:	89 c8                	mov    %ecx,%eax
    7ca8:	c1 f8 10             	sar    $0x10,%eax
    7cab:	ba f5 01 00 00       	mov    $0x1f5,%edx
    7cb0:	ee                   	out    %al,(%dx)
    7cb1:	89 c8                	mov    %ecx,%eax
    7cb3:	c1 f8 18             	sar    $0x18,%eax
    7cb6:	83 c8 e0             	or     $0xffffffe0,%eax
    7cb9:	ba f6 01 00 00       	mov    $0x1f6,%edx
    7cbe:	ee                   	out    %al,(%dx)
    7cbf:	ba f7 01 00 00       	mov    $0x1f7,%edx
    7cc4:	b0 20                	mov    $0x20,%al
    7cc6:	ee                   	out    %al,(%dx)
    7cc7:	90                   	nop
    7cc8:	ec                   	in     (%dx),%al
    7cc9:	25 c0 00 00 00       	and    $0xc0,%eax
    7cce:	83 f8 40             	cmp    $0x40,%eax
    7cd1:	75 f5                	jne    7cc8 <readSect+0x54>
    7cd3:	8b 4d 08             	mov    0x8(%ebp),%ecx
    7cd6:	8d 99 00 02 00 00    	lea    0x200(%ecx),%ebx
    7cdc:	ba f0 01 00 00       	mov    $0x1f0,%edx
    7ce1:	8d 76 00             	lea    0x0(%esi),%esi
    7ce4:	ed                   	in     (%dx),%eax
    7ce5:	89 01                	mov    %eax,(%ecx)
    7ce7:	83 c1 04             	add    $0x4,%ecx
    7cea:	39 d9                	cmp    %ebx,%ecx
    7cec:	75 f6                	jne    7ce4 <readSect+0x70>
    7cee:	5b                   	pop    %ebx
    7cef:	5d                   	pop    %ebp
    7cf0:	c3                   	ret    
    7cf1:	8d 76 00             	lea    0x0(%esi),%esi

00007cf4 <bootMain>:
    7cf4:	55                   	push   %ebp
    7cf5:	89 e5                	mov    %esp,%ebp
    7cf7:	57                   	push   %edi
    7cf8:	56                   	push   %esi
    7cf9:	53                   	push   %ebx
    7cfa:	81 ec 0c 90 01 00    	sub    $0x1900c,%esp
    7d00:	8d b5 e8 6f fe ff    	lea    -0x19018(%ebp),%esi
    7d06:	31 db                	xor    %ebx,%ebx
    7d08:	43                   	inc    %ebx
    7d09:	53                   	push   %ebx
    7d0a:	56                   	push   %esi
    7d0b:	e8 64 ff ff ff       	call   7c74 <readSect>
    7d10:	81 c6 00 02 00 00    	add    $0x200,%esi
    7d16:	58                   	pop    %eax
    7d17:	5a                   	pop    %edx
    7d18:	81 fb c8 00 00 00    	cmp    $0xc8,%ebx
    7d1e:	75 e8                	jne    7d08 <bootMain+0x14>
    7d20:	8d 95 e8 6f fe ff    	lea    -0x19018(%ebp),%edx
    7d26:	03 95 04 70 fe ff    	add    -0x18ffc(%ebp),%edx
    7d2c:	0f b7 8d 14 70 fe ff 	movzwl -0x18fec(%ebp),%ecx
    7d33:	8d 59 ff             	lea    -0x1(%ecx),%ebx
    7d36:	31 c0                	xor    %eax,%eax
    7d38:	85 c9                	test   %ecx,%ecx
    7d3a:	74 29                	je     7d65 <bootMain+0x71>
    7d3c:	8d b5 e8 6f fe ff    	lea    -0x19018(%ebp),%esi
    7d42:	03 72 04             	add    0x4(%edx),%esi
    7d45:	8b 4a 10             	mov    0x10(%edx),%ecx
    7d48:	8b 7a 08             	mov    0x8(%edx),%edi
    7d4b:	f3 a4                	rep movsb %ds:(%esi),%es:(%edi)
    7d4d:	8b 72 10             	mov    0x10(%edx),%esi
    7d50:	8b 4a 14             	mov    0x14(%edx),%ecx
    7d53:	29 f1                	sub    %esi,%ecx
    7d55:	03 72 08             	add    0x8(%edx),%esi
    7d58:	89 f7                	mov    %esi,%edi
    7d5a:	f3 aa                	rep stos %al,%es:(%edi)
    7d5c:	83 c2 20             	add    $0x20,%edx
    7d5f:	4b                   	dec    %ebx
    7d60:	83 fb ff             	cmp    $0xffffffff,%ebx
    7d63:	75 d7                	jne    7d3c <bootMain+0x48>
    7d65:	ff 95 00 70 fe ff    	call   *-0x19000(%ebp)
    7d6b:	8d 65 f4             	lea    -0xc(%ebp),%esp
    7d6e:	5b                   	pop    %ebx
    7d6f:	5e                   	pop    %esi
    7d70:	5f                   	pop    %edi
    7d71:	5d                   	pop    %ebp
    7d72:	c3                   	ret    
