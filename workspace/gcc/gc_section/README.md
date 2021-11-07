# 概述

本目录主要是gcc编译环境下段（函数/全局变量等）回收的简要测试。

# 文件说明

└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    ├── default.lds 		修改后的链接脚本
    └── README.md 			本说明文档

# 执行编译

在gc-section目录下执行：

```c
./build.sh
```

# 编译清除

在gc_section目录下执行：

```c
./build.sh clean
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。