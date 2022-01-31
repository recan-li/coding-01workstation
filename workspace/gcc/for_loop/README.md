# 概述

本目录主要是学习gcc编译是如何一步步编译C代码的。

# 文件说明

└── gc_section
    ├── build.sh 			编译脚本
    ├── 1.ok.c 				测试源代码的1.ok.c
    ├── 1.fail.c 			测试源代码的1.fail.c
    ├── 2.c 				checksum模块的C源文件
    ├── 2.h 				checksum模块的头文件
    └── README.md 			本说明文档

# 执行编译

在for_loop目录下执行：

按照正常流程编译，生成ok的可执行：
```c
./build.sh ok
```

按照正常流程编译，生成fail的可执行：
```c
./build.sh fail
```

# 编译清除

在for_loop目录下执行：

```c
./build.sh clean
```

# 验证分析
分析1.ok.s和1.fail.s文件，对比分析不同的汇编代码的差异。

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。