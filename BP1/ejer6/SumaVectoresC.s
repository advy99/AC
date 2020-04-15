	.file	"SumaVectoresC.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\357\277\275 componentes del vector"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"Tama\357\277\275o Vectores:%u (%u B)\n"
	.section	.rodata.str1.8
	.align 8
.LC2:
	.string	"No hay suficiente espacio para los vectores "
	.align 8
.LC4:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC5:
	.string	"Tiempo:%11.9f\t / Tama\357\277\275o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) / / V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC7:
	.string	"Tiempo:%11.9f\t / Tama\357\277\275o Vectores:%u\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	cmpl	$1, %edi
	jle	.L25
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	movq	%rax, %r13
	movl	%eax, %esi
	movl	$4, %edx
	movl	%r13d, %ebx
	movl	$.LC1, %edi
	xorl	%eax, %eax
	leaq	0(,%rbx,8), %r12
	call	printf
	movq	%r12, %rdi
	call	malloc
	movq	%r12, %rdi
	movq	%rax, %rbp
	call	malloc
	movq	%r12, %rdi
	movq	%rax, %r14
	call	malloc
	testq	%rbp, %rbp
	movq	%rax, %r12
	je	.L3
	testq	%r14, %r14
	je	.L3
	testl	%r13d, %r13d
	je	.L26
	pxor	%xmm1, %xmm1
	leal	-1(%r13), %r15d
	xorl	%eax, %eax
	movsd	.LC3(%rip), %xmm3
	cvtsi2sdq	%rbx, %xmm1
	movq	%r15, %rbx
	addq	$1, %r15
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L8:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	movapd	%xmm1, %xmm7
	cvtsi2sd	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	subsd	%xmm0, %xmm7
	movsd	%xmm2, 0(%rbp,%rax,8)
	movsd	%xmm7, (%r14,%rax,8)
	addq	$1, %rax
	cmpq	%rax, %r15
	jne	.L8
	movq	%rsp, %rsi
	xorl	%edi, %edi
	salq	$3, %r15
	call	clock_gettime
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L9:
	movsd	0(%rbp,%rax), %xmm0
	addsd	(%r14,%rax), %xmm0
	movsd	%xmm0, (%r12,%rax)
	addq	$8, %rax
	cmpq	%r15, %rax
	jne	.L9
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	pxor	%xmm0, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cmpl	$9, %r13d
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC6(%rip), %xmm0
	addsd	%xmm1, %xmm0
	jbe	.L27
	movl	%ebx, %eax
	movsd	(%r12), %xmm3
	movsd	(%r12,%rax,8), %xmm6
	movl	%ebx, %r8d
	movsd	(%r14,%rax,8), %xmm5
	movl	%ebx, %ecx
	movsd	0(%rbp,%rax,8), %xmm4
	movl	%ebx, %edx
	movsd	(%r14), %xmm2
	movl	%r13d, %esi
	movsd	0(%rbp), %xmm1
	movl	$.LC5, %edi
	movl	$7, %eax
	call	printf
.L11:
	movq	%rbp, %rdi
	call	free
	movq	%r14, %rdi
	call	free
	movq	%r12, %rdi
	call	free
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L27:
	.cfi_restore_state
	movl	%r13d, %esi
	movl	$.LC7, %edi
	movl	$1, %eax
	leaq	1(%rbx), %r13
	xorl	%ebx, %ebx
	call	printf
	.p2align 4,,10
	.p2align 3
.L12:
	movsd	(%r12,%rbx,8), %xmm2
	movl	%ebx, %ecx
	movsd	(%r14,%rbx,8), %xmm1
	movl	%ebx, %edx
	movsd	0(%rbp,%rbx,8), %xmm0
	movl	%ebx, %esi
	movl	$.LC4, %edi
	movl	$3, %eax
	addq	$1, %rbx
	call	printf
	cmpq	%rbx, %r13
	jne	.L12
	jmp	.L11
.L26:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime
	movq	24(%rsp), %rax
	subq	8(%rsp), %rax
	xorl	%esi, %esi
	pxor	%xmm0, %xmm0
	movl	$.LC7, %edi
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	movl	$1, %eax
	divsd	.LC6(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	printf
	jmp	.L11
.L25:
	movl	$.LC0, %edi
	call	puts
	orl	$-1, %edi
	call	exit
.L3:
	movl	$.LC2, %edi
	call	puts
	movl	$-2, %edi
	call	exit
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
	.long	2576980378
	.long	1069128089
	.align 8
.LC6:
	.long	0
	.long	1104006501
	.ident	"GCC: (GNU) 7.1.0"
	.section	.note.GNU-stack,"",@progbits
