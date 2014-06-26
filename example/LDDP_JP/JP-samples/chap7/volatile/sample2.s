	.file	"sample2.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB12:
	.file 1 "sample2.c"
	.loc 1 4 0
	leal	4(%esp), %ecx
.LCFI0:
	andl	$-16, %esp
	pushl	-4(%ecx)
.LCFI1:
	pushl	%ebp
.LCFI2:
	movl	%esp, %ebp
.LCFI3:
	pushl	%ecx
.LCFI4:
	subl	$36, %esp
.LCFI5:
	.loc 1 8 0
	movl	$2008, -8(%ebp)
.LVL0:
	.loc 1 11 0
	movl	-8(%ebp), %eax
.LVL1:
	.loc 1 12 0
	movl	-8(%ebp), %eax
.LVL2:
	.loc 1 13 0
	movl	-8(%ebp), %eax
.LVL3:
	.loc 1 15 0
	movl	$.LC0, (%esp)
	movl	%eax, 4(%esp)
	call	printf
.LVL4:
	.loc 1 18 0
	addl	$36, %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
.LFE12:
	.size	main, .-main
	.section	.debug_frame,"",@progbits
.Lframe0:
	.long	.LECIE0-.LSCIE0
.LSCIE0:
	.long	0xffffffff
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE0:
.LSFDE0:
	.long	.LEFDE0-.LASFDE0
.LASFDE0:
	.long	.Lframe0
	.long	.LFB12
	.long	.LFE12-.LFB12
	.byte	0x4
	.long	.LCFI0-.LFB12
	.byte	0xc
	.uleb128 0x1
	.uleb128 0x0
	.byte	0x9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0x84
	.uleb128 0x3
	.align 4
.LEFDE0:
	.file 2 "/usr/include/stdio.h"
	.file 3 "/usr/include/libio.h"
	.file 4 "/usr/include/bits/types.h"
	.file 5 "/usr/lib/gcc/i386-redhat-linux/4.1.1/include/stddef.h"
	.text
.Letext0:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB12-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x1
	.byte	0x51
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI2-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI3-.Ltext0
	.long	.LFE12-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0x0
	.long	0x0
.LLST1:
	.long	.LVL1-.Ltext0
	.long	.LVL2-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL2-.Ltext0
	.long	.LVL3-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL3-.Ltext0
	.long	.LVL4-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0x0
	.long	0x0
	.section	.debug_info
	.long	0x341
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.Ldebug_line0
	.long	.Letext0
	.long	.Ltext0
	.long	.LASF51
	.byte	0x1
	.long	.LASF52
	.long	.LASF53
	.uleb128 0x2
	.long	.LASF8
	.byte	0x5
	.byte	0xd6
	.long	0x30
	.uleb128 0x3
	.long	.LASF0
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.long	.LASF1
	.byte	0x1
	.byte	0x8
	.uleb128 0x3
	.long	.LASF2
	.byte	0x2
	.byte	0x7
	.uleb128 0x3
	.long	.LASF3
	.byte	0x4
	.byte	0x7
	.uleb128 0x3
	.long	.LASF4
	.byte	0x1
	.byte	0x6
	.uleb128 0x3
	.long	.LASF5
	.byte	0x2
	.byte	0x5
	.uleb128 0x4
	.string	"int"
	.byte	0x4
	.byte	0x5
	.uleb128 0x3
	.long	.LASF6
	.byte	0x8
	.byte	0x5
	.uleb128 0x3
	.long	.LASF7
	.byte	0x8
	.byte	0x7
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x3b
	.long	0x61
	.uleb128 0x2
	.long	.LASF10
	.byte	0x4
	.byte	0x90
	.long	0x85
	.uleb128 0x3
	.long	.LASF11
	.byte	0x4
	.byte	0x5
	.uleb128 0x2
	.long	.LASF12
	.byte	0x4
	.byte	0x91
	.long	0x6f
	.uleb128 0x3
	.long	.LASF0
	.byte	0x4
	.byte	0x7
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x6
	.byte	0x4
	.long	0xa6
	.uleb128 0x3
	.long	.LASF13
	.byte	0x1
	.byte	0x6
	.uleb128 0x7
	.long	0x26d
	.long	.LASF44
	.byte	0x94
	.byte	0x2
	.byte	0x2e
	.uleb128 0x8
	.long	.LASF14
	.byte	0x3
	.value	0x10c
	.long	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0x8
	.long	.LASF15
	.byte	0x3
	.value	0x111
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.long	.LASF16
	.byte	0x3
	.value	0x112
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.long	.LASF17
	.byte	0x3
	.value	0x113
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.long	.LASF18
	.byte	0x3
	.value	0x114
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x8
	.long	.LASF19
	.byte	0x3
	.value	0x115
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.long	.LASF20
	.byte	0x3
	.value	0x116
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.long	.LASF21
	.byte	0x3
	.value	0x117
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.long	.LASF22
	.byte	0x3
	.value	0x118
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.long	.LASF23
	.byte	0x3
	.value	0x11a
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.long	.LASF24
	.byte	0x3
	.value	0x11b
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.long	.LASF25
	.byte	0x3
	.value	0x11c
	.long	0xa0
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.long	.LASF26
	.byte	0x3
	.value	0x11e
	.long	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.long	.LASF27
	.byte	0x3
	.value	0x120
	.long	0x2b1
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.long	.LASF28
	.byte	0x3
	.value	0x122
	.long	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.long	.LASF29
	.byte	0x3
	.value	0x126
	.long	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x8
	.long	.LASF30
	.byte	0x3
	.value	0x128
	.long	0x7a
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.long	.LASF31
	.byte	0x3
	.value	0x12c
	.long	0x3e
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.long	.LASF32
	.byte	0x3
	.value	0x12d
	.long	0x4c
	.byte	0x2
	.byte	0x23
	.uleb128 0x46
	.uleb128 0x8
	.long	.LASF33
	.byte	0x3
	.value	0x12e
	.long	0x2b7
	.byte	0x2
	.byte	0x23
	.uleb128 0x47
	.uleb128 0x8
	.long	.LASF34
	.byte	0x3
	.value	0x132
	.long	0x2c7
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.long	.LASF35
	.byte	0x3
	.value	0x13b
	.long	0x8c
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x8
	.long	.LASF36
	.byte	0x3
	.value	0x144
	.long	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x8
	.long	.LASF37
	.byte	0x3
	.value	0x145
	.long	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.long	.LASF38
	.byte	0x3
	.value	0x146
	.long	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x8
	.long	.LASF39
	.byte	0x3
	.value	0x147
	.long	0x9e
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.long	.LASF40
	.byte	0x3
	.value	0x148
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x8
	.long	.LASF41
	.byte	0x3
	.value	0x14a
	.long	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0x8
	.long	.LASF42
	.byte	0x3
	.value	0x14c
	.long	0x2cd
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.byte	0x0
	.uleb128 0x9
	.long	.LASF43
	.byte	0x3
	.byte	0xb0
	.uleb128 0x7
	.long	0x2ab
	.long	.LASF45
	.byte	0xc
	.byte	0x3
	.byte	0xb6
	.uleb128 0xa
	.long	.LASF46
	.byte	0x3
	.byte	0xb7
	.long	0x2ab
	.byte	0x2
	.byte	0x23
	.uleb128 0x0
	.uleb128 0xa
	.long	.LASF47
	.byte	0x3
	.byte	0xb8
	.long	0x2b1
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xa
	.long	.LASF48
	.byte	0x3
	.byte	0xbc
	.long	0x5a
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.long	0x274
	.uleb128 0x6
	.byte	0x4
	.long	0xad
	.uleb128 0xb
	.long	0x2c7
	.long	0xa6
	.uleb128 0xc
	.long	0x97
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.long	0x26d
	.uleb128 0xb
	.long	0x2dd
	.long	0xa6
	.uleb128 0xc
	.long	0x97
	.byte	0x27
	.byte	0x0
	.uleb128 0xd
	.long	0x31f
	.byte	0x1
	.long	.LASF54
	.byte	0x1
	.byte	0x4
	.byte	0x1
	.long	0x5a
	.long	.LFB12
	.long	.LFE12
	.long	.LLST0
	.uleb128 0xe
	.string	"val"
	.byte	0x1
	.byte	0x5
	.long	0x5a
	.byte	0x2
	.byte	0x75
	.sleb128 -8
	.uleb128 0xf
	.string	"n"
	.byte	0x1
	.byte	0x5
	.long	0x5a
	.long	.LLST1
	.uleb128 0x10
	.string	"p"
	.byte	0x1
	.byte	0x6
	.long	0x31f
	.byte	0x0
	.uleb128 0x6
	.byte	0x4
	.long	0x325
	.uleb128 0x11
	.long	0x5a
	.uleb128 0x12
	.long	.LASF49
	.byte	0x2
	.byte	0x8e
	.long	0x2b1
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.long	.LASF50
	.byte	0x2
	.byte	0x8f
	.long	0x2b1
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x10
	.uleb128 0x6
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x16
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x11
	.uleb128 0x35
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x12
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x17
	.value	0x2
	.long	.Ldebug_info0
	.long	0x345
	.long	0x2dd
	.string	"main"
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF10:
	.string	"__off_t"
.LASF15:
	.string	"_IO_read_ptr"
.LASF27:
	.string	"_chain"
.LASF8:
	.string	"size_t"
.LASF33:
	.string	"_shortbuf"
.LASF4:
	.string	"signed char"
.LASF11:
	.string	"long int"
.LASF21:
	.string	"_IO_buf_base"
.LASF7:
	.string	"long long unsigned int"
.LASF50:
	.string	"stdout"
.LASF6:
	.string	"long long int"
.LASF28:
	.string	"_fileno"
.LASF16:
	.string	"_IO_read_end"
.LASF14:
	.string	"_flags"
.LASF22:
	.string	"_IO_buf_end"
.LASF31:
	.string	"_cur_column"
.LASF9:
	.string	"__quad_t"
.LASF30:
	.string	"_old_offset"
.LASF35:
	.string	"_offset"
.LASF40:
	.string	"__pad5"
.LASF45:
	.string	"_IO_marker"
.LASF49:
	.string	"stdin"
.LASF0:
	.string	"unsigned int"
.LASF3:
	.string	"long unsigned int"
.LASF19:
	.string	"_IO_write_ptr"
.LASF47:
	.string	"_sbuf"
.LASF2:
	.string	"short unsigned int"
.LASF34:
	.string	"_lock"
.LASF29:
	.string	"_flags2"
.LASF41:
	.string	"_mode"
.LASF52:
	.string	"sample2.c"
.LASF23:
	.string	"_IO_save_base"
.LASF20:
	.string	"_IO_write_end"
.LASF43:
	.string	"_IO_lock_t"
.LASF44:
	.string	"_IO_FILE"
.LASF48:
	.string	"_pos"
.LASF53:
	.string	"/home/hirata/chap7/volatile"
.LASF26:
	.string	"_markers"
.LASF1:
	.string	"unsigned char"
.LASF5:
	.string	"short int"
.LASF32:
	.string	"_vtable_offset"
.LASF13:
	.string	"char"
.LASF46:
	.string	"_next"
.LASF12:
	.string	"__off64_t"
.LASF17:
	.string	"_IO_read_base"
.LASF25:
	.string	"_IO_save_end"
.LASF36:
	.string	"__pad1"
.LASF37:
	.string	"__pad2"
.LASF38:
	.string	"__pad3"
.LASF39:
	.string	"__pad4"
.LASF51:
	.string	"GNU C 4.1.1 20061011 (Red Hat 4.1.1-30)"
.LASF42:
	.string	"_unused2"
.LASF24:
	.string	"_IO_backup_base"
.LASF54:
	.string	"main"
.LASF18:
	.string	"_IO_write_base"
	.ident	"GCC: (GNU) 4.1.1 20061011 (Red Hat 4.1.1-30)"
	.section	.note.GNU-stack,"",@progbits
