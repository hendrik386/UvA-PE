	.file	"matmul.cpp"
	.text
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1656:
	.cfi_startproc
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE1656:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d %d %f\n"
.LC1:
	.string	"read fauld"
	.text
	.p2align 4,,15
	.type	_Z11read_sparseP8_IO_FILEiiiPf.constprop.4, @function
_Z11read_sparseP8_IO_FILEiiiPf.constprop.4:
.LFB2411:
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
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%rdi, 8(%rsp)
	movl	%esi, 20(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	testl	%edx, %edx
	jle	.L3
	movl	%edx, %ebp
	movq	%rcx, %r12
	xorl	%ebx, %ebx
	leaq	52(%rsp), %r15
	leaq	48(%rsp), %r14
	leaq	44(%rsp), %r13
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L5:
	movl	44(%rsp), %eax
	addl	$1, %ebx
	vmovss	52(%rsp), %xmm0
	subl	$1, %eax
	imull	20(%rsp), %eax
	addl	48(%rsp), %eax
	cltq
	vmovss	%xmm0, -4(%r12,%rax,4)
	cmpl	%ebx, %ebp
	je	.L3
.L4:
	movq	8(%rsp), %rdi
	xorl	%eax, %eax
	movq	%r15, %r8
	movq	%r14, %rcx
	leaq	.LC0(%rip), %rsi
	movq	%r13, %rdx
	call	fscanf@PLT
	testl	%eax, %eax
	jne	.L5
	leaq	.LC1(%rip), %rsi
	movl	$10, %edx
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rdx
	testq	%rdx, %rdx
	je	.L15
	cmpb	$0, 56(%rdx)
	je	.L7
	movsbl	67(%rdx), %esi
.L8:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%rdx, %rdi
	movq	%rdx, 24(%rsp)
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	24(%rsp), %rdx
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdi
	movq	(%rdx), %rax
	movq	48(%rax), %rax
	cmpq	%rdi, %rax
	je	.L8
	movq	%rdx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L3:
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L16
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L15:
	.cfi_restore_state
	call	_ZSt16__throw_bad_castv@PLT
.L16:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2411:
	.size	_Z11read_sparseP8_IO_FILEiiiPf.constprop.4, .-_Z11read_sparseP8_IO_FILEiiiPf.constprop.4
	.p2align 4,,15
	.globl	_Z11matrix_multiiiPfS_S_
	.type	_Z11matrix_multiiiPfS_S_, @function
_Z11matrix_multiiiPfS_S_:
.LFB1899:
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
	movl	%edi, -8(%rsp)
	movq	%rcx, -40(%rsp)
	movq	%r8, -32(%rsp)
	testl	%edi, %edi
	jle	.L29
	movl	%edx, %r12d
	testl	%edx, %edx
	jle	.L29
	leaq	4(%rcx), %rax
	movslq	%edx, %r8
	movq	%r9, %rbp
	movq	%rax, -16(%rsp)
	leal	-1(%rsi), %eax
	salq	$2, %r8
	xorl	%r14d, %r14d
	movq	%rax, -24(%rsp)
	leal	(%rdx,%rdx), %eax
	xorl	%r13d, %r13d
	movl	%eax, -4(%rsp)
	.p2align 4,,10
	.p2align 3
.L23:
	movq	-40(%rsp), %rbx
	movslq	%r14d, %rax
	movl	%edx, %r15d
	movq	-16(%rsp), %rdi
	subl	%r12d, %r15d
	movq	-32(%rsp), %r11
	movl	%r15d, %r10d
	leaq	(%rbx,%rax,4), %rbx
	addq	-24(%rsp), %rax
	leaq	(%rdi,%rax,4), %r9
	movq	%rbp, %rdi
	.p2align 4,,10
	.p2align 3
.L20:
	movl	$0x00000000, (%rdi)
	movq	%r11, %rcx
	movq	%rbx, %rax
	vxorps	%xmm1, %xmm1, %xmm1
	testl	%esi, %esi
	jle	.L24
	.p2align 4,,10
	.p2align 3
.L22:
	vmovss	(%rax), %xmm0
	addq	$4, %rax
	vmulss	(%rcx), %xmm0, %xmm0
	addq	%r8, %rcx
	vaddss	%xmm0, %xmm1, %xmm1
	vmovss	%xmm1, (%rdi)
	cmpq	%rax, %r9
	jne	.L22
.L24:
	addl	$1, %r10d
	addq	$4, %rdi
	addq	$4, %r11
	cmpl	%edx, %r10d
	jne	.L20
	movl	-4(%rsp), %eax
	addl	$1, %r13d
	addq	%r8, %rbp
	addl	%esi, %r14d
	leal	(%rax,%r15), %edx
	cmpl	%r13d, -8(%rsp)
	jne	.L23
.L29:
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
	.cfi_endproc
.LFE1899:
	.size	_Z11matrix_multiiiPfS_S_, .-_Z11matrix_multiiiPfS_S_
	.p2align 4,,15
	.globl	_Z12generate_matiiiPfS_
	.type	_Z12generate_matiiiPfS_, @function
_Z12generate_matiiiPfS_:
.LFB1900:
	.cfi_startproc
	imull	%esi, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	testl	%edi, %edi
	jle	.L38
	leal	-1(%rdi), %eax
	cmpl	$6, %eax
	jbe	.L43
	movl	%edi, %r9d
	vmovaps	.LC3(%rip), %ymm0
	movq	%rcx, %rax
	shrl	$3, %r9d
	salq	$5, %r9
	addq	%rcx, %r9
	.p2align 4,,10
	.p2align 3
.L37:
	vmovups	%xmm0, (%rax)
	vextractf128	$0x1, %ymm0, 16(%rax)
	addq	$32, %rax
	cmpq	%r9, %rax
	jne	.L37
	movl	%edi, %eax
	andl	$-8, %eax
	cmpl	%eax, %edi
	je	.L38
.L35:
	vmovss	.LC4(%rip), %xmm0
	movslq	%eax, %r9
	vmovss	%xmm0, (%rcx,%r9,4)
	leal	1(%rax), %r9d
	cmpl	%r9d, %edi
	jle	.L38
	movslq	%r9d, %r9
	vmovss	%xmm0, (%rcx,%r9,4)
	leal	2(%rax), %r9d
	cmpl	%r9d, %edi
	jle	.L38
	movslq	%r9d, %r9
	vmovss	%xmm0, (%rcx,%r9,4)
	leal	3(%rax), %r9d
	cmpl	%r9d, %edi
	jle	.L38
	movslq	%r9d, %r9
	vmovss	%xmm0, (%rcx,%r9,4)
	leal	4(%rax), %r9d
	cmpl	%r9d, %edi
	jle	.L38
	movslq	%r9d, %r9
	vmovss	%xmm0, (%rcx,%r9,4)
	leal	5(%rax), %r9d
	cmpl	%r9d, %edi
	jle	.L38
	movslq	%r9d, %r9
	addl	$6, %eax
	vmovss	%xmm0, (%rcx,%r9,4)
	cmpl	%eax, %edi
	jle	.L38
	cltq
	vmovss	%xmm0, (%rcx,%rax,4)
.L38:
	imull	%esi, %edx
	testl	%edx, %edx
	jle	.L47
	leal	-1(%rdx), %eax
	cmpl	$6, %eax
	jbe	.L44
	movl	%edx, %ecx
	vmovaps	.LC3(%rip), %ymm0
	movq	%r8, %rax
	shrl	$3, %ecx
	salq	$5, %rcx
	addq	%r8, %rcx
	.p2align 4,,10
	.p2align 3
.L41:
	vmovups	%xmm0, (%rax)
	vextractf128	$0x1, %ymm0, 16(%rax)
	addq	$32, %rax
	cmpq	%rcx, %rax
	jne	.L41
	movl	%edx, %eax
	andl	$-8, %eax
	cmpl	%edx, %eax
	je	.L47
.L40:
	vmovss	.LC4(%rip), %xmm0
	movslq	%eax, %rcx
	vmovss	%xmm0, (%r8,%rcx,4)
	leal	1(%rax), %ecx
	cmpl	%edx, %ecx
	jge	.L47
	movslq	%ecx, %rcx
	vmovss	%xmm0, (%r8,%rcx,4)
	leal	2(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L47
	movslq	%ecx, %rcx
	vmovss	%xmm0, (%r8,%rcx,4)
	leal	3(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L47
	movslq	%ecx, %rcx
	vmovss	%xmm0, (%r8,%rcx,4)
	leal	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L47
	movslq	%ecx, %rcx
	vmovss	%xmm0, (%r8,%rcx,4)
	leal	5(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L47
	movslq	%ecx, %rcx
	addl	$6, %eax
	vmovss	%xmm0, (%r8,%rcx,4)
	cmpl	%eax, %edx
	jle	.L47
	cltq
	vmovss	%xmm0, (%r8,%rax,4)
.L47:
	vzeroupper
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L44:
	.cfi_restore_state
	xorl	%eax, %eax
	jmp	.L40
.L43:
	xorl	%eax, %eax
	jmp	.L35
	.cfi_endproc
.LFE1900:
	.size	_Z12generate_matiiiPfS_, .-_Z12generate_matiiiPfS_
	.p2align 4,,15
	.globl	_Z11read_sparseP8_IO_FILEiiiPf
	.type	_Z11read_sparseP8_IO_FILEiiiPf, @function
_Z11read_sparseP8_IO_FILEiiiPf:
.LFB1901:
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
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%rdi, 8(%rsp)
	movl	%edx, 20(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	testl	%ecx, %ecx
	jle	.L49
	movl	%ecx, %ebp
	movq	%r8, %r12
	xorl	%ebx, %ebx
	leaq	52(%rsp), %r15
	leaq	48(%rsp), %r14
	leaq	44(%rsp), %r13
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L51:
	movl	44(%rsp), %eax
	addl	$1, %ebx
	vmovss	52(%rsp), %xmm0
	subl	$1, %eax
	imull	20(%rsp), %eax
	addl	48(%rsp), %eax
	cltq
	vmovss	%xmm0, -4(%r12,%rax,4)
	cmpl	%ebx, %ebp
	je	.L49
.L50:
	movq	8(%rsp), %rdi
	xorl	%eax, %eax
	movq	%r15, %r8
	movq	%r14, %rcx
	leaq	.LC0(%rip), %rsi
	movq	%r13, %rdx
	call	fscanf@PLT
	testl	%eax, %eax
	jne	.L51
	leaq	.LC1(%rip), %rsi
	movl	$10, %edx
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %rdx
	testq	%rdx, %rdx
	je	.L61
	cmpb	$0, 56(%rdx)
	je	.L53
	movsbl	67(%rdx), %esi
.L54:
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L53:
	movq	%rdx, %rdi
	movq	%rdx, 24(%rsp)
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	24(%rsp), %rdx
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdi
	movq	(%rdx), %rax
	movq	48(%rax), %rax
	cmpq	%rdi, %rax
	je	.L54
	movq	%rdx, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L54
	.p2align 4,,10
	.p2align 3
.L49:
	movq	56(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L62
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L61:
	.cfi_restore_state
	call	_ZSt16__throw_bad_castv@PLT
.L62:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1901:
	.size	_Z11read_sparseP8_IO_FILEiiiPf, .-_Z11read_sparseP8_IO_FILEiiiPf
	.p2align 4,,15
	.globl	_Z12write_sparseP8_IO_FILEiiPKf
	.type	_Z12write_sparseP8_IO_FILEiiPKf, @function
_Z12write_sparseP8_IO_FILEiiPKf:
.LFB1902:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rcx, %r14
	movl	%esi, %ecx
	imull	%edx, %ecx
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movl	%esi, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movl	%edx, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	testl	%ecx, %ecx
	jle	.L64
	leal	-1(%rcx), %r15d
	cmpl	$3, %r15d
	jbe	.L81
	movl	%ecx, %edx
	movq	%r14, %rax
	vpxor	%xmm1, %xmm1, %xmm1
	vxorps	%xmm2, %xmm2, %xmm2
	shrl	$2, %edx
	salq	$4, %rdx
	addq	%r14, %rdx
	.p2align 4,,10
	.p2align 3
.L66:
	vcmpneqps	(%rax), %xmm2, %xmm0
	addq	$16, %rax
	vpsubd	%xmm0, %xmm1, %xmm1
	cmpq	%rdx, %rax
	jne	.L66
	vpsrldq	$8, %xmm1, %xmm0
	movl	%ecx, %eax
	vpaddd	%xmm0, %xmm1, %xmm1
	andl	$-4, %eax
	vpsrldq	$4, %xmm1, %xmm0
	vpaddd	%xmm0, %xmm1, %xmm1
	vmovd	%xmm1, %ebx
	vxorps	%xmm1, %xmm1, %xmm1
	cmpl	%eax, %ecx
	je	.L67
.L65:
	movslq	%eax, %rdx
	vxorps	%xmm1, %xmm1, %xmm1
	vcomiss	(%r14,%rdx,4), %xmm1
	jne	.L91
.L68:
	leal	1(%rax), %edx
	cmpl	%ecx, %edx
	jge	.L67
	movslq	%edx, %rdx
	vcomiss	(%r14,%rdx,4), %xmm1
	jne	.L92
.L70:
	leal	2(%rax), %edx
	cmpl	%ecx, %edx
	jge	.L67
	movslq	%edx, %rdx
	vcomiss	(%r14,%rdx,4), %xmm1
	je	.L72
	addl	$1, %ebx
.L72:
	addl	$3, %eax
	cmpl	%eax, %ecx
	jle	.L67
	cltq
	vcomiss	(%r14,%rax,4), %xmm1
	je	.L67
	addl	$1, %ebx
.L67:
	leaq	20(%rsp), %rsi
	movq	%r12, %rdi
	vmovss	%xmm1, 12(%rsp)
	movl	$1196573517, 20(%rsp)
	call	_Z15mm_write_bannerP8_IO_FILEPc@PLT
	movl	%ebx, %ecx
	movl	%r13d, %esi
	movl	%ebp, %edx
	leaq	.LC0(%rip), %r13
	movq	%r12, %rdi
	xorl	%ebx, %ebx
	call	_Z21mm_write_mtx_crd_sizeP8_IO_FILEiii@PLT
	vmovss	12(%rsp), %xmm1
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L76:
	leaq	1(%rbx), %rax
	cmpq	%r15, %rbx
	je	.L63
.L82:
	movq	%rax, %rbx
.L78:
	vmovss	(%r14,%rbx,4), %xmm0
	movl	%ebx, %eax
	vcomiss	%xmm1, %xmm0
	je	.L76
	cltd
	movl	$1, %esi
	movq	%r12, %rdi
	vmovss	%xmm1, 12(%rsp)
	idivl	%ebp
	vcvtss2sd	%xmm0, %xmm0, %xmm0
	leal	1(%rax), %ecx
	movl	$1, %eax
	leal	1(%rdx), %r8d
	movq	%r13, %rdx
	call	__fprintf_chk@PLT
	vmovss	12(%rsp), %xmm1
	leaq	1(%rbx), %rax
	cmpq	%r15, %rbx
	jne	.L82
.L63:
	movq	24(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L93
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
	.p2align 4,,10
	.p2align 3
.L91:
	.cfi_restore_state
	addl	$1, %ebx
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L92:
	addl	$1, %ebx
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L64:
	leaq	20(%rsp), %rsi
	movl	$1196573517, 20(%rsp)
	call	_Z15mm_write_bannerP8_IO_FILEPc@PLT
	xorl	%ecx, %ecx
	movl	%ebp, %edx
	movl	%r13d, %esi
	movq	%r12, %rdi
	call	_Z21mm_write_mtx_crd_sizeP8_IO_FILEiii@PLT
	jmp	.L63
.L81:
	xorl	%ebx, %ebx
	xorl	%eax, %eax
	jmp	.L65
.L93:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1902:
	.size	_Z12write_sparseP8_IO_FILEiiPKf, .-_Z12write_sparseP8_IO_FILEiiPKf
	.section	.rodata.str1.1
.LC5:
	.string	"%f "
	.text
	.p2align 4,,15
	.globl	_Z10read_denseP8_IO_FILEiiPf
	.type	_Z10read_denseP8_IO_FILEiiPf, @function
_Z10read_denseP8_IO_FILEiiPf:
.LFB1903:
	.cfi_startproc
	testl	%esi, %esi
	jle	.L109
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leal	-1(%rdx), %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	xorl	%r14d, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movl	%eax, 12(%rsp)
	leaq	4(%rcx), %rax
	movq	%rcx, 24(%rsp)
	movl	%edx, 4(%rsp)
	movl	%esi, 8(%rsp)
	movq	%rax, 16(%rsp)
	.p2align 4,,10
	.p2align 3
.L98:
	movl	4(%rsp), %eax
	testl	%eax, %eax
	jle	.L103
	movq	24(%rsp), %rax
	movslq	%r14d, %rdx
	movq	16(%rsp), %rcx
	leaq	(%rax,%rdx,4), %rbx
	movl	12(%rsp), %eax
	addq	%rdx, %rax
	leaq	(%rcx,%rax,4), %rbp
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L99:
	addq	$4, %rbx
	cmpq	%rbx, %rbp
	je	.L103
.L104:
	xorl	%eax, %eax
	movq	%rbx, %rdx
	movq	%r12, %rdi
	leaq	.LC5(%rip), %rsi
	call	fscanf@PLT
	testl	%eax, %eax
	jne	.L99
	leaq	.LC1(%rip), %rsi
	movl	$10, %edx
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	leaq	_ZSt4cout(%rip), %rdx
	movq	-24(%rax), %rax
	movq	240(%rdx,%rax), %r15
	testq	%r15, %r15
	je	.L112
	cmpb	$0, 56(%r15)
	je	.L101
	movsbl	67(%r15), %esi
.L102:
	leaq	_ZSt4cout(%rip), %rdi
	addq	$4, %rbx
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	cmpq	%rbx, %rbp
	jne	.L104
.L103:
	addl	$1, %r13d
	addl	4(%rsp), %r14d
	cmpl	%r13d, 8(%rsp)
	jne	.L98
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
	.p2align 4,,10
	.p2align 3
.L101:
	.cfi_restore_state
	movq	%r15, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r15), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rcx
	movq	48(%rax), %rax
	cmpq	%rcx, %rax
	je	.L102
	movq	%r15, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L102
.L109:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
.L112:
	.cfi_def_cfa_offset 96
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE1903:
	.size	_Z10read_denseP8_IO_FILEiiPf, .-_Z10read_denseP8_IO_FILEiiPf
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.string	"Could not process Matrix Market banneri for A.\n"
	.align 8
.LC7:
	.string	"Could not process Matrix Market banner for B.\n"
	.text
	.p2align 4,,15
	.globl	_Z8read_matPiS_S_S_S_P8_IO_FILES1_
	.type	_Z8read_matPiS_S_S_S_P8_IO_FILES1_, @function
_Z8read_matPiS_S_S_S_P8_IO_FILES1_:
.LFB1904:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%r8, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rcx, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%r9, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%rdi, (%rsp)
	leaq	32(%rsp), %rsi
	movq	%r9, %rdi
	movq	112(%rsp), %rbp
	movq	%rdx, 8(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_Z14mm_read_bannerP8_IO_FILEPA4_c@PLT
	testl	%eax, %eax
	jne	.L135
	leaq	36(%rsp), %rsi
	movq	%rbp, %rdi
	call	_Z14mm_read_bannerP8_IO_FILEPA4_c@PLT
	movl	%eax, %r13d
	testl	%eax, %eax
	jne	.L136
	cmpb	$67, 34(%rsp)
	je	.L125
	cmpb	$67, 38(%rsp)
	je	.L126
	cmpb	$77, 32(%rsp)
	je	.L137
.L128:
	movl	$-8, %r13d
.L113:
	movq	40(%rsp), %rcx
	xorq	%fs:40, %rcx
	movl	%r13d, %eax
	jne	.L138
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
	.p2align 4,,10
	.p2align 3
.L137:
	.cfi_restore_state
	movzbl	33(%rsp), %eax
	cmpb	$67, %al
	je	.L139
	cmpb	$65, %al
	jne	.L128
	movq	(%rsp), %rsi
	movl	$0, (%r14)
	movq	%r12, %rdx
	movq	%rbx, %rdi
	call	_Z22mm_read_mtx_array_sizeP8_IO_FILEPiS1_@PLT
	testl	%eax, %eax
	jne	.L122
.L120:
	cmpb	$77, 36(%rsp)
	je	.L119
.L129:
	movl	$-9, %r13d
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L119:
	movzbl	37(%rsp), %eax
	cmpb	$67, %al
	je	.L140
	cmpb	$65, %al
	jne	.L129
	movq	8(%rsp), %rdx
	movl	$0, (%r15)
	leaq	28(%rsp), %rsi
	movq	%rbp, %rdi
	call	_Z22mm_read_mtx_array_sizeP8_IO_FILEPiS1_@PLT
	testl	%eax, %eax
	jne	.L122
.L123:
	movl	28(%rsp), %eax
	cmpl	%eax, (%r12)
	movl	$-15, %eax
	cmovne	%eax, %r13d
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L139:
	movq	(%rsp), %rsi
	movq	%r14, %rcx
	movq	%r12, %rdx
	movq	%rbx, %rdi
	call	_Z20mm_read_mtx_crd_sizeP8_IO_FILEPiS1_S1_@PLT
	testl	%eax, %eax
	je	.L120
.L118:
	movl	$-10, %r13d
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L140:
	movq	8(%rsp), %rdx
	leaq	28(%rsp), %rsi
	movq	%r15, %rcx
	movq	%rbp, %rdi
	call	_Z20mm_read_mtx_crd_sizeP8_IO_FILEPiS1_S1_@PLT
	testl	%eax, %eax
	je	.L123
	jmp	.L118
	.p2align 4,,10
	.p2align 3
.L122:
	movl	$-11, %r13d
	jmp	.L113
	.p2align 4,,10
	.p2align 3
.L135:
	leaq	.LC6(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$-3, %r13d
	jmp	.L113
.L125:
	movl	$-6, %r13d
	jmp	.L113
.L126:
	movl	$-7, %r13d
	jmp	.L113
.L136:
	leaq	.LC7(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	$-4, %r13d
	jmp	.L113
.L138:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1904:
	.size	_Z8read_matPiS_S_S_S_P8_IO_FILES1_, .-_Z8read_matPiS_S_S_S_P8_IO_FILES1_
	.section	.rodata.str1.8
	.align 8
.LC8:
	.string	"Usage: %s [martix1] [matrix2] [resultmatrix] \n"
	.section	.rodata.str1.1
.LC9:
	.string	"rt"
.LC10:
	.string	"Matrices are incompatible! \n"
.LC11:
	.string	"Out of memory A! \n"
.LC12:
	.string	"Out of memory B! \n"
.LC13:
	.string	"Out of memory C1! \n"
.LC14:
	.string	"wt"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1905:
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
	subq	$120, %rsp
	.cfi_def_cfa_offset 176
	movq	%rsi, 72(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 104(%rsp)
	xorl	%eax, %eax
	movl	$0, 96(%rsp)
	movl	$0, 100(%rsp)
	cmpl	$2, %edi
	jle	.L175
	movq	8(%rsi), %rdi
	leaq	.LC9(%rip), %rsi
	call	fopen@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L174
	movq	72(%rsp), %rax
	leaq	.LC9(%rip), %rsi
	movq	16(%rax), %rdi
	call	fopen@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L176
	leaq	96(%rsp), %rcx
	movq	%rbp, %r9
	leaq	92(%rsp), %rdx
	leaq	88(%rsp), %rsi
	leaq	84(%rsp), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 184
	pushq	%rax
	.cfi_def_cfa_offset 192
	leaq	116(%rsp), %r8
	call	_Z8read_matPiS_S_S_S_P8_IO_FILES1_
	popq	%rdx
	.cfi_def_cfa_offset 184
	popq	%rcx
	.cfi_def_cfa_offset 176
	cmpl	$-15, %eax
	je	.L177
	movl	84(%rsp), %r15d
	movl	$4, %esi
	movl	88(%rsp), %r14d
	movl	%r15d, %edi
	imull	%r14d, %edi
	movslq	%edi, %rdi
	call	calloc@PLT
	movq	%rax, %r13
	testq	%rax, %rax
	je	.L178
	movl	92(%rsp), %edi
	movl	$4, %esi
	imull	%r14d, %edi
	movslq	%edi, %rdi
	call	calloc@PLT
	movq	%rax, %r12
	testq	%rax, %rax
	je	.L179
	movl	96(%rsp), %edx
	movq	%r13, %rcx
	testl	%edx, %edx
	jle	.L148
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_Z11read_sparseP8_IO_FILEiiiPf.constprop.4
.L149:
	movl	100(%rsp), %edx
	movq	%r12, %rcx
	movl	92(%rsp), %esi
	testl	%edx, %edx
	jle	.L150
	movq	%rbx, %rdi
	call	_Z11read_sparseP8_IO_FILEiiiPf.constprop.4
.L151:
	movq	%rbp, %rdi
	call	fclose@PLT
	movq	%rbx, %rdi
	call	fclose@PLT
	movl	84(%rsp), %edi
	movl	$4, %esi
	movl	92(%rsp), %eax
	movl	%edi, 8(%rsp)
	imull	%eax, %edi
	movl	%eax, (%rsp)
	movslq	%edi, %rdi
	call	calloc@PLT
	movq	%rax, 56(%rsp)
	testq	%rax, %rax
	je	.L180
	movl	8(%rsp), %eax
	movl	88(%rsp), %ebp
	testl	%eax, %eax
	jle	.L153
	movl	(%rsp), %esi
	testl	%esi, %esi
	jle	.L153
	movslq	%esi, %rax
	subl	$1, %esi
	movl	%ebp, %edx
	movl	$10, 68(%rsp)
	leaq	4(,%rsi,4), %rbx
	shrl	$2, %edx
	movq	%rsi, 32(%rsp)
	movq	%rbx, 24(%rsp)
	leal	-1(%rbp), %ebx
	salq	$4, %rdx
	leaq	0(,%rax,4), %r14
	movl	%ebx, 64(%rsp)
	movq	%rax, %rbx
	leaq	(%rax,%rax,2), %rax
	salq	$4, %rbx
	movq	%rdx, 40(%rsp)
	salq	$2, %rax
	movq	%rbx, 16(%rsp)
	movq	%rax, 48(%rsp)
	movl	%ebp, %eax
	andl	$-4, %eax
	movl	%eax, 12(%rsp)
	.p2align 4,,10
	.p2align 3
.L155:
	movq	56(%rsp), %r8
	xorl	%ebx, %ebx
	movl	$0, 4(%rsp)
	.p2align 4,,10
	.p2align 3
.L161:
	movq	24(%rsp), %rdx
	xorl	%esi, %esi
	movq	%r8, %rdi
	call	memset@PLT
	movq	%r12, %r9
	xorl	%esi, %esi
	movq	%rax, %r8
	movslq	%ebx, %rax
	leaq	0(%r13,%rax,4), %r10
	movq	40(%rsp), %rax
	leaq	(%r10,%rax), %r11
	.p2align 4,,10
	.p2align 3
.L154:
	movl	%esi, %edi
	testl	%ebp, %ebp
	jle	.L156
	cmpl	$4, 64(%rsp)
	jbe	.L164
	movq	%r9, %rax
	movq	%r10, %rdx
	vxorps	%xmm0, %xmm0, %xmm0
.L158:
	movq	48(%rsp), %rcx
	addq	$16, %rdx
	vmovss	(%rax,%r14,2), %xmm1
	vinsertps	$0x10, (%rax,%rcx), %xmm1, %xmm2
	vmovss	(%rax), %xmm1
	vinsertps	$0x10, (%rax,%r14), %xmm1, %xmm1
	vmovlhps	%xmm2, %xmm1, %xmm1
	vmulps	-16(%rdx), %xmm1, %xmm1
	addq	16(%rsp), %rax
	vaddps	%xmm1, %xmm0, %xmm0
	cmpq	%r11, %rdx
	jne	.L158
	movl	12(%rsp), %eax
	vhaddps	%xmm0, %xmm0, %xmm0
	vhaddps	%xmm0, %xmm0, %xmm0
	movl	%eax, %edx
	cmpl	%eax, %ebp
	je	.L159
.L157:
	movl	(%rsp), %eax
	leal	(%rbx,%rdx), %r15d
	movslq	%r15d, %r15
	vmovss	0(%r13,%r15,4), %xmm1
	imull	%edx, %eax
	leal	(%rax,%rdi), %ecx
	movslq	%ecx, %rcx
	vmulss	(%r12,%rcx,4), %xmm1, %xmm1
	leal	1(%rdx), %ecx
	vaddss	%xmm1, %xmm0, %xmm0
	cmpl	%ecx, %ebp
	jle	.L159
	addl	(%rsp), %eax
	addl	%ebx, %ecx
	movslq	%ecx, %rcx
	vmovss	0(%r13,%rcx,4), %xmm1
	leal	2(%rdx), %ecx
	leal	(%rax,%rdi), %r15d
	movslq	%r15d, %r15
	vmulss	(%r12,%r15,4), %xmm1, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	cmpl	%ecx, %ebp
	jle	.L159
	addl	(%rsp), %eax
	addl	%ebx, %ecx
	movslq	%ecx, %rcx
	vmovss	0(%r13,%rcx,4), %xmm1
	leal	3(%rdx), %ecx
	leal	(%rdi,%rax), %r15d
	movslq	%r15d, %r15
	vmulss	(%r12,%r15,4), %xmm1, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	cmpl	%ecx, %ebp
	jle	.L159
	addl	(%rsp), %eax
	addl	%ebx, %ecx
	addl	$4, %edx
	movslq	%ecx, %rcx
	vmovss	0(%r13,%rcx,4), %xmm1
	leal	(%rdi,%rax), %r15d
	movslq	%r15d, %r15
	vmulss	(%r12,%r15,4), %xmm1, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	cmpl	%edx, %ebp
	jle	.L159
	addl	(%rsp), %eax
	addl	%ebx, %edx
	movslq	%edx, %rdx
	addl	%eax, %edi
	movslq	%edi, %rdi
	vmovss	(%r12,%rdi,4), %xmm1
	vmulss	0(%r13,%rdx,4), %xmm1, %xmm1
	vaddss	%xmm1, %xmm0, %xmm0
	.p2align 4,,10
	.p2align 3
.L159:
	vmovss	%xmm0, (%r8,%rsi,4)
.L156:
	leaq	1(%rsi), %rax
	addq	$4, %r9
	cmpq	%rsi, 32(%rsp)
	je	.L181
	movq	%rax, %rsi
	jmp	.L154
	.p2align 4,,10
	.p2align 3
.L164:
	vxorps	%xmm0, %xmm0, %xmm0
	xorl	%edx, %edx
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L181:
	addl	$1, 4(%rsp)
	addq	%r14, %r8
	addl	%ebp, %ebx
	movl	4(%rsp), %eax
	cmpl	%eax, 8(%rsp)
	jne	.L161
	subl	$1, 68(%rsp)
	jne	.L155
.L153:
	movq	72(%rsp), %rax
	leaq	.LC14(%rip), %rsi
	movq	24(%rax), %rdi
	call	fopen@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L182
	movq	56(%rsp), %r14
	movq	%rax, %rdi
	movl	84(%rsp), %esi
	movl	92(%rsp), %edx
	movq	%r14, %rcx
	call	_Z12write_sparseP8_IO_FILEiiPKf
	movq	%rbx, %rdi
	call	fclose@PLT
	movq	%r13, %rdi
	call	free@PLT
	movq	%r12, %rdi
	call	free@PLT
	movq	%r14, %rdi
	call	free@PLT
	xorl	%eax, %eax
	movq	104(%rsp), %rsi
	xorq	%fs:40, %rsi
	jne	.L183
	addq	$120, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L148:
	.cfi_restore_state
	movl	%r14d, %edx
	movl	%r15d, %esi
	movq	%rbp, %rdi
	call	_Z10read_denseP8_IO_FILEiiPf
	jmp	.L149
.L150:
	movl	%esi, %edx
	movl	88(%rsp), %esi
	movq	%rbx, %rdi
	call	_Z10read_denseP8_IO_FILEiiPf
	jmp	.L151
.L179:
	leaq	.LC12(%rip), %rsi
.L173:
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
.L174:
	movl	$1, %edi
	call	exit@PLT
.L180:
	leaq	.LC13(%rip), %rsi
	movl	$1, %edi
	call	__printf_chk@PLT
	movl	$1, %edi
	call	exit@PLT
.L175:
	movq	(%rsi), %rcx
	leaq	.LC8(%rip), %rdx
	movl	$1, %esi
	xorl	%eax, %eax
	movq	stderr(%rip), %rdi
	call	__fprintf_chk@PLT
	movl	$1, %edi
	call	exit@PLT
.L177:
	leaq	.LC10(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%rbp, %rdi
	call	fclose@PLT
	movq	%rbx, %rdi
	call	fclose@PLT
	jmp	.L174
.L176:
	movl	$2, %edi
	call	exit@PLT
.L178:
	leaq	.LC11(%rip), %rsi
	jmp	.L173
.L183:
	call	__stack_chk_fail@PLT
.L182:
	movl	$3, %edi
	call	exit@PLT
	.cfi_endproc
.LFE1905:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__Z11matrix_multiiiPfS_S_, @function
_GLOBAL__sub_I__Z11matrix_multiiiPfS_S_:
.LFB2402:
	.cfi_startproc
	leaq	_ZStL8__ioinit(%rip), %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE2402:
	.size	_GLOBAL__sub_I__Z11matrix_multiiiPfS_S_, .-_GLOBAL__sub_I__Z11matrix_multiiiPfS_S_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z11matrix_multiiiPfS_S_
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
.LC3:
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.long	1065353216
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC4:
	.long	1065353216
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0"
	.section	.note.GNU-stack,"",@progbits
