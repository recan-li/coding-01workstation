# 概述

本目录主要是gcc编译环境下编码实现aoti的函数功能。

# 文件说明

```shell
└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档
```

# 执行编译

在my_atoi目录下执行：

代码编译：
```shell
my_atoi$ ./build.sh 
gcc main.c -Wall -save-temps=obj -o test
```

# 编译清除

在my_atoi目录下执行：

```shell
./build.sh clean
```

# 代码执行

在my_atoi目录下执行：

测试用例执行：
```shell
my_atoi$ ./test 
gcc main.c -Wall -save-temps=obj -o test
atoi-0   : [1234] => 1234
my-atoi-0: [1234] => 1234
test-0   : [ OK ]
atoi-1   : [-1234] => -1234
my-atoi-1: [-1234] => -1234
test-1   : [ OK ]
atoi-2   : [1234a5678] => 1234
my-atoi-2: [1234a5678] => 1234
test-2   : [ OK ]
atoi-3   : [-1234a5678] => -1234
my-atoi-3: [-1234a5678] => -1234
test-3   : [ OK ]
atoi-4   : [ 1234] => 1234
my-atoi-4: [ 1234] => 1234
test-4   : [ OK ]
atoi-5   : [  -1234] => -1234
my-atoi-5: [  -1234] => -1234
test-5   : [ OK ]
atoi-6   : [   1234a5678] => 1234
my-atoi-6: [   1234a5678] => 1234
test-6   : [ OK ]
atoi-7   : [    -1234a5678] => -1234
my-atoi-7: [    -1234a5678] => -1234
test-7   : [ OK ]
atoi-8   : [abcd] => 0
my-atoi-8: [abcd] => 0
test-8   : [ OK ]
atoi-9   : [] => 0
my-atoi-9: [] => 0
test-9   : [ OK ]
atoi-10   : [01234] => 1234
my-atoi-10: [01234] => 1234
test-10   : [ OK ]
atoi-11   : [-01234] => -1234
my-atoi-11: [-01234] => -1234
test-11   : [ OK ]
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。