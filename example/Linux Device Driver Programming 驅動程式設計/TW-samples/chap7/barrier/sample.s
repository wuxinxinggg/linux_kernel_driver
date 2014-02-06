	.file	"sample.c"
	.section	.rodata
.LC0:
	.string	"%d, %d, %d\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$20, %esp
	movl	$10, a
	movl	$0, c
	movl	a, %eax
	movl	%eax, b
	movl	c, %eax
	movl	b, %edx
	movl	a, %ecx
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, %eax
	addl	$20, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.comm	a,4,4
	.comm	b,4,4
	.comm	c,4,4
	.ident	"GCC: (GNU) 4.1.1 20061011 (Red Hat 4.1.1-30)"
	.section	.note.GNU-stack,"",@progbits
