# 概述

本目录主要是gcc编译环境下static和inline函数的简要测试，并验证一个头文件包含引发的问题。

# 文件说明

```shell
└── static_inline
    ├── build.sh 			    编译脚本
    ├── main.c                  测试文件main.c
    ├── macro.h                 定义若干宏定义
    ├── macro_inline.h          定义一个内联函数
    └── README.md               本说明文档
```

# 执行编译

在static_inline_macro目录下执行：

正确执行编译：
```c
./build.sh
```

触发编译报错：
```c
./build.sh error
```

# 编译清除

在static_inline_macro目录下执行：

```c
./build.sh clean
```

# 代码运行

在static_inline_macro目录下执行：

```c
gcc/static_inline_macro$ ./test_static 
Hello world !
1, 2
1, 2
1, 2
1, 2
b: 12346
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。