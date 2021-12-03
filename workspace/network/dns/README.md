# 概述

本目录主要是DNS解析的简要测试。

# 文件说明

└── dns
    ├── build.sh 			编译脚本
    ├── dns.c 				域名解析的组包/解析源码
    ├── dns.h 				导出接口的头文件
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档

# 执行编译

在dns目录下执行：

```c
./build.sh
```

# 编译清除

在dns目录下执行：

```c
./build.sh clean
```

# 代码执行

```c
network/dns$ ./test 
DNS resolve www.baidu.com                    by default                          => 180.101.49.11                 
DNS resolve www.baidu.com                    by 8.8.8.8                          => 103.235.46.39                 
DNS resolve www.baidu.com                    by 114.114.114.114                  => 180.101.49.12                 
DNS resolve www.hao123.com                   by default                          => 220.181.107.181               
DNS resolve www.hao123.com                   by 8.8.8.8                          => 103.235.46.234                
DNS resolve www.hao123.com                   by 114.114.114.114                  => 220.181.107.181
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。