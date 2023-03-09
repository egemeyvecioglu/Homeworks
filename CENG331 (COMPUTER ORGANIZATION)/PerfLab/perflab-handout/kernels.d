
kernels.o:     file format elf32-i386


Disassembly of section .text:

00000000 <naive_conv>:
   0:	f3 0f 1e fb          	endbr32 
   4:	55                   	push   %ebp
   5:	57                   	push   %edi
   6:	56                   	push   %esi
   7:	53                   	push   %ebx
   8:	83 ec 10             	sub    $0x10,%esp
   b:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
  12:	00 
  13:	e9 a9 00 00 00       	jmp    c1 <naive_conv+0xc1>
  18:	8b 44 24 08          	mov    0x8(%esp),%eax
  1c:	8b 2c 24             	mov    (%esp),%ebp
  1f:	01 e8                	add    %ebp,%eax
  21:	0f af 44 24 24       	imul   0x24(%esp),%eax
  26:	8b 4c 24 04          	mov    0x4(%esp),%ecx
  2a:	8d 14 31             	lea    (%ecx,%esi,1),%edx
  2d:	01 d0                	add    %edx,%eax
  2f:	8d 04 40             	lea    (%eax,%eax,2),%eax
  32:	8d 0c 00             	lea    (%eax,%eax,1),%ecx
  35:	03 4c 24 28          	add    0x28(%esp),%ecx
  39:	0f b7 19             	movzwl (%ecx),%ebx
  3c:	8d 04 ee             	lea    (%esi,%ebp,8),%eax
  3f:	8d 04 40             	lea    (%eax,%eax,2),%eax
  42:	8d 14 00             	lea    (%eax,%eax,1),%edx
  45:	03 54 24 2c          	add    0x2c(%esp),%edx
  49:	0f b7 02             	movzwl (%edx),%eax
  4c:	0f af d8             	imul   %eax,%ebx
  4f:	03 1f                	add    (%edi),%ebx
  51:	89 1f                	mov    %ebx,(%edi)
  53:	0f b7 41 02          	movzwl 0x2(%ecx),%eax
  57:	0f b7 6a 02          	movzwl 0x2(%edx),%ebp
  5b:	0f af c5             	imul   %ebp,%eax
  5e:	01 d8                	add    %ebx,%eax
  60:	89 07                	mov    %eax,(%edi)
  62:	0f b7 69 04          	movzwl 0x4(%ecx),%ebp
  66:	0f b7 5a 04          	movzwl 0x4(%edx),%ebx
  6a:	0f af eb             	imul   %ebx,%ebp
  6d:	01 e8                	add    %ebp,%eax
  6f:	89 07                	mov    %eax,(%edi)
  71:	83 c6 01             	add    $0x1,%esi
  74:	83 fe 07             	cmp    $0x7,%esi
  77:	7e 9f                	jle    18 <naive_conv+0x18>
  79:	83 04 24 01          	addl   $0x1,(%esp)
  7d:	83 3c 24 07          	cmpl   $0x7,(%esp)
  81:	7f 07                	jg     8a <naive_conv+0x8a>
  83:	be 00 00 00 00       	mov    $0x0,%esi
  88:	eb ea                	jmp    74 <naive_conv+0x74>
  8a:	83 44 24 04 01       	addl   $0x1,0x4(%esp)
  8f:	8b 74 24 04          	mov    0x4(%esp),%esi
  93:	39 74 24 0c          	cmp    %esi,0xc(%esp)
  97:	7e 23                	jle    bc <naive_conv+0xbc>
  99:	8b 44 24 08          	mov    0x8(%esp),%eax
  9d:	0f af 44 24 24       	imul   0x24(%esp),%eax
  a2:	03 44 24 04          	add    0x4(%esp),%eax
  a6:	8b 7c 24 30          	mov    0x30(%esp),%edi
  aa:	8d 3c 87             	lea    (%edi,%eax,4),%edi
  ad:	c7 07 00 00 00 00    	movl   $0x0,(%edi)
  b3:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
  ba:	eb c1                	jmp    7d <naive_conv+0x7d>
  bc:	83 44 24 08 01       	addl   $0x1,0x8(%esp)
  c1:	8b 44 24 24          	mov    0x24(%esp),%eax
  c5:	83 e8 07             	sub    $0x7,%eax
  c8:	89 44 24 0c          	mov    %eax,0xc(%esp)
  cc:	3b 44 24 08          	cmp    0x8(%esp),%eax
  d0:	7e 0a                	jle    dc <naive_conv+0xdc>
  d2:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  d9:	00 
  da:	eb b3                	jmp    8f <naive_conv+0x8f>
  dc:	83 c4 10             	add    $0x10,%esp
  df:	5b                   	pop    %ebx
  e0:	5e                   	pop    %esi
  e1:	5f                   	pop    %edi
  e2:	5d                   	pop    %ebp
  e3:	c3                   	ret    

000000e4 <convolution>:
  e4:	f3 0f 1e fb          	endbr32 
  e8:	ff 74 24 10          	pushl  0x10(%esp)
  ec:	ff 74 24 10          	pushl  0x10(%esp)
  f0:	ff 74 24 10          	pushl  0x10(%esp)
  f4:	ff 74 24 10          	pushl  0x10(%esp)
  f8:	e8 fc ff ff ff       	call   f9 <convolution+0x15>
  fd:	83 c4 10             	add    $0x10,%esp
 100:	c3                   	ret    

00000101 <naive_average_pooling>:
 101:	f3 0f 1e fb          	endbr32 
 105:	55                   	push   %ebp
 106:	57                   	push   %edi
 107:	56                   	push   %esi
 108:	53                   	push   %ebx
 109:	83 ec 04             	sub    $0x4,%esp
 10c:	bf 00 00 00 00       	mov    $0x0,%edi
 111:	e9 9c 00 00 00       	jmp    1b2 <naive_average_pooling+0xb1>
 116:	8d 14 7b             	lea    (%ebx,%edi,2),%edx
 119:	0f af 54 24 18       	imul   0x18(%esp),%edx
 11e:	8d 2c 71             	lea    (%ecx,%esi,2),%ebp
 121:	01 ea                	add    %ebp,%edx
 123:	8d 2c 52             	lea    (%edx,%edx,2),%ebp
 126:	8d 54 2d 00          	lea    0x0(%ebp,%ebp,1),%edx
 12a:	03 54 24 1c          	add    0x1c(%esp),%edx
 12e:	0f b7 2a             	movzwl (%edx),%ebp
 131:	66 01 28             	add    %bp,(%eax)
 134:	0f b7 6a 02          	movzwl 0x2(%edx),%ebp
 138:	66 01 68 02          	add    %bp,0x2(%eax)
 13c:	0f b7 52 04          	movzwl 0x4(%edx),%edx
 140:	66 01 50 04          	add    %dx,0x4(%eax)
 144:	83 c1 01             	add    $0x1,%ecx
 147:	83 f9 01             	cmp    $0x1,%ecx
 14a:	7e ca                	jle    116 <naive_average_pooling+0x15>
 14c:	83 c3 01             	add    $0x1,%ebx
 14f:	83 fb 01             	cmp    $0x1,%ebx
 152:	7f 07                	jg     15b <naive_average_pooling+0x5a>
 154:	b9 00 00 00 00       	mov    $0x0,%ecx
 159:	eb ec                	jmp    147 <naive_average_pooling+0x46>
 15b:	0f b7 10             	movzwl (%eax),%edx
 15e:	66 c1 ea 02          	shr    $0x2,%dx
 162:	66 89 10             	mov    %dx,(%eax)
 165:	0f b7 50 02          	movzwl 0x2(%eax),%edx
 169:	66 c1 ea 02          	shr    $0x2,%dx
 16d:	66 89 50 02          	mov    %dx,0x2(%eax)
 171:	0f b7 50 04          	movzwl 0x4(%eax),%edx
 175:	66 c1 ea 02          	shr    $0x2,%dx
 179:	66 89 50 04          	mov    %dx,0x4(%eax)
 17d:	83 c6 01             	add    $0x1,%esi
 180:	39 34 24             	cmp    %esi,(%esp)
 183:	7e 2a                	jle    1af <naive_average_pooling+0xae>
 185:	8b 04 24             	mov    (%esp),%eax
 188:	0f af c7             	imul   %edi,%eax
 18b:	01 f0                	add    %esi,%eax
 18d:	8d 14 40             	lea    (%eax,%eax,2),%edx
 190:	8d 04 12             	lea    (%edx,%edx,1),%eax
 193:	03 44 24 20          	add    0x20(%esp),%eax
 197:	66 c7 00 00 00       	movw   $0x0,(%eax)
 19c:	66 c7 40 02 00 00    	movw   $0x0,0x2(%eax)
 1a2:	66 c7 40 04 00 00    	movw   $0x0,0x4(%eax)
 1a8:	bb 00 00 00 00       	mov    $0x0,%ebx
 1ad:	eb a0                	jmp    14f <naive_average_pooling+0x4e>
 1af:	83 c7 01             	add    $0x1,%edi
 1b2:	8b 44 24 18          	mov    0x18(%esp),%eax
 1b6:	c1 e8 1f             	shr    $0x1f,%eax
 1b9:	03 44 24 18          	add    0x18(%esp),%eax
 1bd:	d1 f8                	sar    %eax
 1bf:	89 04 24             	mov    %eax,(%esp)
 1c2:	39 f8                	cmp    %edi,%eax
 1c4:	7e 07                	jle    1cd <naive_average_pooling+0xcc>
 1c6:	be 00 00 00 00       	mov    $0x0,%esi
 1cb:	eb b3                	jmp    180 <naive_average_pooling+0x7f>
 1cd:	83 c4 04             	add    $0x4,%esp
 1d0:	5b                   	pop    %ebx
 1d1:	5e                   	pop    %esi
 1d2:	5f                   	pop    %edi
 1d3:	5d                   	pop    %ebp
 1d4:	c3                   	ret    

000001d5 <average_pooling>:
 1d5:	f3 0f 1e fb          	endbr32 
 1d9:	55                   	push   %ebp
 1da:	57                   	push   %edi
 1db:	56                   	push   %esi
 1dc:	53                   	push   %ebx
 1dd:	83 ec 0c             	sub    $0xc,%esp
 1e0:	8b 44 24 20          	mov    0x20(%esp),%eax
 1e4:	d1 f8                	sar    %eax
 1e6:	89 44 24 08          	mov    %eax,0x8(%esp)
 1ea:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 1f1:	00 
 1f2:	e9 d7 00 00 00       	jmp    2ce <average_pooling+0xf9>
 1f7:	8b 5c 24 04          	mov    0x4(%esp),%ebx
 1fb:	0f af 5c 24 20       	imul   0x20(%esp),%ebx
 200:	8b 0c 24             	mov    (%esp),%ecx
 203:	8d 04 0b             	lea    (%ebx,%ecx,1),%eax
 206:	8d 04 40             	lea    (%eax,%eax,2),%eax
 209:	8d 34 85 00 00 00 00 	lea    0x0(,%eax,4),%esi
 210:	03 74 24 24          	add    0x24(%esp),%esi
 214:	0f b7 06             	movzwl (%esi),%eax
 217:	01 c9                	add    %ecx,%ecx
 219:	8d 51 01             	lea    0x1(%ecx),%edx
 21c:	8d 1c 5a             	lea    (%edx,%ebx,2),%ebx
 21f:	8d 3c 5b             	lea    (%ebx,%ebx,2),%edi
 222:	8d 1c 3f             	lea    (%edi,%edi,1),%ebx
 225:	03 5c 24 24          	add    0x24(%esp),%ebx
 229:	0f b7 2b             	movzwl (%ebx),%ebp
 22c:	01 c5                	add    %eax,%ebp
 22e:	8b 44 24 04          	mov    0x4(%esp),%eax
 232:	8d 7c 00 01          	lea    0x1(%eax,%eax,1),%edi
 236:	0f af 7c 24 20       	imul   0x20(%esp),%edi
 23b:	8d 04 39             	lea    (%ecx,%edi,1),%eax
 23e:	8d 04 40             	lea    (%eax,%eax,2),%eax
 241:	8d 0c 00             	lea    (%eax,%eax,1),%ecx
 244:	03 4c 24 24          	add    0x24(%esp),%ecx
 248:	0f b7 01             	movzwl (%ecx),%eax
 24b:	01 e8                	add    %ebp,%eax
 24d:	01 fa                	add    %edi,%edx
 24f:	8d 3c 52             	lea    (%edx,%edx,2),%edi
 252:	8d 14 3f             	lea    (%edi,%edi,1),%edx
 255:	03 54 24 24          	add    0x24(%esp),%edx
 259:	0f b7 3a             	movzwl (%edx),%edi
 25c:	01 f8                	add    %edi,%eax
 25e:	0f b7 7e 02          	movzwl 0x2(%esi),%edi
 262:	0f b7 6b 02          	movzwl 0x2(%ebx),%ebp
 266:	01 ef                	add    %ebp,%edi
 268:	0f b7 69 02          	movzwl 0x2(%ecx),%ebp
 26c:	01 fd                	add    %edi,%ebp
 26e:	0f b7 7a 02          	movzwl 0x2(%edx),%edi
 272:	01 ef                	add    %ebp,%edi
 274:	0f b7 76 04          	movzwl 0x4(%esi),%esi
 278:	0f b7 5b 04          	movzwl 0x4(%ebx),%ebx
 27c:	01 de                	add    %ebx,%esi
 27e:	0f b7 59 04          	movzwl 0x4(%ecx),%ebx
 282:	01 de                	add    %ebx,%esi
 284:	0f b7 5a 04          	movzwl 0x4(%edx),%ebx
 288:	01 de                	add    %ebx,%esi
 28a:	c1 f8 02             	sar    $0x2,%eax
 28d:	8b 54 24 04          	mov    0x4(%esp),%edx
 291:	0f af 54 24 08       	imul   0x8(%esp),%edx
 296:	8b 1c 24             	mov    (%esp),%ebx
 299:	01 da                	add    %ebx,%edx
 29b:	8d 0c 52             	lea    (%edx,%edx,2),%ecx
 29e:	8d 14 09             	lea    (%ecx,%ecx,1),%edx
 2a1:	03 54 24 28          	add    0x28(%esp),%edx
 2a5:	66 89 02             	mov    %ax,(%edx)
 2a8:	c1 ff 02             	sar    $0x2,%edi
 2ab:	66 89 7a 02          	mov    %di,0x2(%edx)
 2af:	c1 fe 02             	sar    $0x2,%esi
 2b2:	66 89 72 04          	mov    %si,0x4(%edx)
 2b6:	83 c3 01             	add    $0x1,%ebx
 2b9:	89 1c 24             	mov    %ebx,(%esp)
 2bc:	8b 74 24 08          	mov    0x8(%esp),%esi
 2c0:	39 34 24             	cmp    %esi,(%esp)
 2c3:	0f 8c 2e ff ff ff    	jl     1f7 <average_pooling+0x22>
 2c9:	83 44 24 04 01       	addl   $0x1,0x4(%esp)
 2ce:	8b 74 24 08          	mov    0x8(%esp),%esi
 2d2:	39 74 24 04          	cmp    %esi,0x4(%esp)
 2d6:	7d 09                	jge    2e1 <average_pooling+0x10c>
 2d8:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 2df:	eb db                	jmp    2bc <average_pooling+0xe7>
 2e1:	83 c4 0c             	add    $0xc,%esp
 2e4:	5b                   	pop    %ebx
 2e5:	5e                   	pop    %esi
 2e6:	5f                   	pop    %edi
 2e7:	5d                   	pop    %ebp
 2e8:	c3                   	ret    

000002e9 <register_conv_functions>:
 2e9:	f3 0f 1e fb          	endbr32 
 2ed:	53                   	push   %ebx
 2ee:	83 ec 10             	sub    $0x10,%esp
 2f1:	e8 fc ff ff ff       	call   2f2 <register_conv_functions+0x9>
 2f6:	81 c3 02 00 00 00    	add    $0x2,%ebx
 2fc:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 302:	50                   	push   %eax
 303:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 309:	50                   	push   %eax
 30a:	e8 fc ff ff ff       	call   30b <register_conv_functions+0x22>
 30f:	83 c4 08             	add    $0x8,%esp
 312:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 318:	50                   	push   %eax
 319:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 31f:	50                   	push   %eax
 320:	e8 fc ff ff ff       	call   321 <register_conv_functions+0x38>
 325:	83 c4 18             	add    $0x18,%esp
 328:	5b                   	pop    %ebx
 329:	c3                   	ret    

0000032a <register_average_pooling_functions>:
 32a:	f3 0f 1e fb          	endbr32 
 32e:	53                   	push   %ebx
 32f:	83 ec 10             	sub    $0x10,%esp
 332:	e8 fc ff ff ff       	call   333 <register_average_pooling_functions+0x9>
 337:	81 c3 02 00 00 00    	add    $0x2,%ebx
 33d:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 343:	50                   	push   %eax
 344:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 34a:	50                   	push   %eax
 34b:	e8 fc ff ff ff       	call   34c <register_average_pooling_functions+0x22>
 350:	83 c4 08             	add    $0x8,%esp
 353:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 359:	50                   	push   %eax
 35a:	8d 83 00 00 00 00    	lea    0x0(%ebx),%eax
 360:	50                   	push   %eax
 361:	e8 fc ff ff ff       	call   362 <register_average_pooling_functions+0x38>
 366:	83 c4 18             	add    $0x18,%esp
 369:	5b                   	pop    %ebx
 36a:	c3                   	ret    

Disassembly of section .text.__x86.get_pc_thunk.bx:

00000000 <__x86.get_pc_thunk.bx>:
   0:	8b 1c 24             	mov    (%esp),%ebx
   3:	c3                   	ret    
