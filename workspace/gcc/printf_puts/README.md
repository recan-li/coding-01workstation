# 概述

本目录主要是介绍gcc编译环境下验证一个printf函数如何变成puts函数的。

# 文件说明

```shell
└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档
```

# 执行编译

在gcc/printf_puts目录下执行：

```c
./build.sh
```

# 编译清除

在gcc/printf_puts目录下执行：

```c
./build.sh clean
```

# 代码执行

在gcc/printf_puts目录下执行：

```c
./test
```

# 简单分析

执行代码编译之后，查看`test.s`文件，找到main函数的汇编代码：

```shell
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$6, -16(%rbp)
	movl	$7, -12(%rbp)
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	movl	$1, %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-16(%rbp), %edx
	movl	-12(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	add
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
```

可以清晰地看到main函数C代码中的第一个`printf("Hello world !\n");`，在汇编里面已经变成了`call	puts@PLT`。

也就是说调用printf函数已经变成了调用puts函数。

# 详细分析
见我的[CSDN博文](http://yyds.recan-li.cn)。