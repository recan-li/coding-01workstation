# 概述

本目录主要是学习gcc编译是如何一步步编译C代码的。

# 文件说明

```shell
└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    ├── sub.c 				sub模块的C源文件
    ├── sub.h 				sub模块的头文件
    └── README.md 			本说明文档
```

# 执行编译

在gcc_helloworld目录下执行：

按照正常流程编译，不生成中间文件：
```c
./build.sh
```

按照一步步的流程编译，生成中间文件：
```c
./build.sh step
```

按照一次性编译的流程，且生成中间文件：
```c
./build.sh allinone
```

按照一步步地的编译流程，使用交叉编译工具链，生成中间文件（由于没有添加C库链接，可能会链接报错）：
```c
./build.sh step cross
```

# 编译清除

在gcc_helloworld目录下执行：

```c
./build.sh clean
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。