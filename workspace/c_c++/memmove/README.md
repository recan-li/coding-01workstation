# 概述

本目录主要是memmove、memcpy库函数的简要测试。

# 文件说明

└── dns
    ├── build.sh 			编译脚本
    ├── memmove.c 			测试源代码的main.c
    └── README.md 			本说明文档

# 执行编译

在memmove目录下执行：

```shell
./build.sh
```

# 编译清除

在memmove目录下执行：

```shell
./build.sh clean
```

# 代码执行

在memmove目录下执行：

```shell
c_c++/memmove$ ./test 
before-memmove-buf: 123456789abcdef
after-memmove-buf: 123451239abcdef
before-memcpy-buf: 123451239abcdef
after-memcpy-buf: 123451239abcdef
before-memmove-buf: 123451239abcdef
after-memmove-buf: 12345123451239f
before-memcpy-buf: 12345123451239f
after-memcpy-buf: 12345123451234f
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。