	.file	"timer.c"
	.section	.rodata
.LC0:
	.string	"%d %d %d\n"
	.align 8
.LC1:
	.string	"\n Time to do 300 squares and cubes= %d seconds\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	.cfi_offset 3, -24
	call	time
	movl	$1, -20(%rbp)
	jmp	.L2
.L3:
	movl	-20(%rbp), %eax
	imull	-20(%rbp), %eax
	movl	%eax, %ecx
	imull	-20(%rbp), %ecx
	movl	-20(%rbp), %eax
	movl	%eax, %edx
	imull	-20(%rbp), %edx
	movl	$.LC0, %eax
	movl	-20(%rbp), %ebx
	movl	%ebx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	addl	$1, -20(%rbp)
.L2:
	cmpl	$300, -20(%rbp)
	jle	.L3
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	time
	movq	-40(%rbp), %rax
	movslq	%eax, %rdx
	movq	-32(%rbp), %rax
	subq	%rax, %rdx
	movl	$.LC1, %eax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	addq	$40, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-16)"
	.section	.note.GNU-stack,"",@progbits
