# 概述

本目录主要是gcc编译环境下#if语句的简要测试。

# 文件说明

```shell
└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档
```

# 执行编译

在if_enum_macro目录下执行：

枚举方式定义版本：
```shell
c_c++/if_enum_macro$ ./build.sh 
gcc main.c -Wall -save-temps=obj -o test
main.c:24:3: warning: #warning "warning here 111" [-Wcpp]
   24 |  #warning "warning here 111"
      |   ^~~~~~~
```

宏方式定义版本：
```shell
c_c++/if_enum_macro$ ./build.sh macro
gcc main.c -Wall -save-temps=obj -o test -DMACRO_DEFINE_EN=1
main.c:27:3: warning: #warning "warning here 222" [-Wcpp]
   27 |  #warning "warning here 222"
      |   ^~~~~~~
```

# 编译清除

在if_enum_macro目录下执行：

```shell
./build.sh clean
```

# 代码执行

在if_enum_macro目录下执行：

枚举方式定义版本： 与期望的不一样！
```shell
c_c++/if_enum_macro$ ./test 
Hello world !
TRUN_ON: 1
TRUN_OFF: 0
APP_CONFIG_SELECT: 1
do something here 111 (off) ...
```

宏方式定义版本： 与期望的一样！
```shell
c_c++/if_enum_macro$ ./test 
Hello world !
TRUN_ON: 1
TRUN_OFF: 0
APP_CONFIG_SELECT: 1
do other things here 222 (on) ...
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。