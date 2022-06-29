# 概述

本目录主要是gcc编译环境下带返回值的宏函数简要测试。

# 文件说明

```shell
└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档
```

# 执行编译

在return_macro目录下执行：

```shell
./build.sh
```

# 编译清除

在return_macro目录下执行：

```shell
./build.sh clean
```

# 代码执行

在return_macro目录下执行：

```shell
c_c++/return_macro$ ./test 
Hello world !
RETURN_MACRO: 1
RETURN_MACRO2: 1
a + b = 13
a + b = 13
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。