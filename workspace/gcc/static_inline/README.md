# 概述

本目录主要是gcc编译环境下static和inline函数的简要测试。

# 文件说明

```shell
└── static_inline
    ├── build.sh 			编译脚本
    ├── main.c 				修正后的main.c
    ├── main.nostatic.c 	编译报错的main.c
    └── README.md 			本说明文档
```

# 执行编译

在static_inline目录下执行：

```c
./build.sh
```

# 编译清除

在static_inline目录下执行：

```c
./build.sh clean
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。