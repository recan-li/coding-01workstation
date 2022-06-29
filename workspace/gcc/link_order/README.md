# 概述

本目录主要是学习gcc链接时如果有静态库参与链接，它的链接顺序是如何讲究的。

# 文件说明

└── link_order
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    ├── a.c 				a模块的C源文件
    ├── b.c 				b模块的C源文件
    ├── c.c 				c模块的C源文件
    ├── libd.c 				d模块的C源文件，打包成静态库参与链接
    ├── libe.c 				e模块的C源文件，打包成静态库参与链接
    ├── libf.c 				f模块的C源文件，打包成静态库参与链接
    └── README.md 			本说明文档

# 程序逻辑关系

在单静态库的情况下（MUL_LIB_TESt未定义），在程序中，main函数调用a.c的函数，a.c的函数调用b.c的函数，b.c的函数调用c.c的函数，c.c的函数调用libd.c的函数，libd.c的函数最终被打包成静态库参与链接。
在多静态库的情况下（MUL_LIB_TESt定义了），在程序中，main函数调用a.c的函数，a.c的函数调用b.c的函数，b.c的函数调用c.c的函数，c.c的函数调用libd.c的函数，libd.c的函数调用libe.c的函数，libe.c的函数调用libf.c的函数，libf.c的函数调用libd.c的函数，新城互相依赖的关系，libd.c、libe.c、libf.c的函数最终被打包成静态库参与链接。

# 执行编译

在link_order目录下执行：

按照正常流程编译，链接成功及运行结果：
```shell
link_order$ ./build.sh ok
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc c.o b.o a.o main.o -ld -L./ -lc -o test

link_order$ ./test 
This is main in [main.c] !
This is func_a in [a.c] !
This is func_b in [b.c] !
This is func_c in [c.c] !
This is func_d in [libd.c] (static library) !
```

按照正常流程编译，链接失败：
```shell
link_order$ ./build.sh fail
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc a.o b.o -ld -L./ c.o main.o -lc -o test
/usr/bin/ld: c.o: in function `func_c':
c.c:(.text+0x28): undefined reference to `func_d'
collect2: error: ld returned 1 exit status
```

解决因链接顺序而失败的操作，及其正确运行：

```shell
link_order$ ./build.sh fail-solve
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc -Wl,--whole-archive -Wl,--start-group a.o b.o -ld -L./ c.o main.o -lc -Wl,--end-group -Wl,-no-whole-archive -o test

link_order$ ./test
This is main in [main.c] !
This is func_a in [a.c] !
This is func_b in [b.c] !
This is func_c in [c.c] !
This is func_d in [libd.c] (static library) !
```

多静态库下，恰好链接顺序正确而链接成功的操作：

```shell
link_order$ ./build.sh mul-lib-ok
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc -c libe.c -o libe.o -save-temps=obj
ar -rcs libe.a libe.o
gcc -c libf.c -o libf.o -save-temps=obj
ar -rcs libf.a libf.o
gcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST
ar -rcs libd.a libd.o
gcc a.o b.o c.o main.o -ld -le -lf -L./ -lc -o test

link_order$ ./test
This is main in [main.c] !
This is func_a in [a.c] !
This is func_b in [b.c] !
This is func_c in [c.c] !
This is func_d in [libd.c] (static library) !
This is func_e in [libe.c] (static library) !
This is func_f in [libf.c] (static library) !
This is func_d_new in [libd.c] (static library) !
```

多静态库下，因链接顺序而失败的操作：

```shell
link_order$ ./build.sh mul-lib-fail
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc -c libe.c -o libe.o -save-temps=obj
ar -rcs libe.a libe.o
gcc -c libf.c -o libf.o -save-temps=obj
ar -rcs libf.a libf.o
gcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST
ar -rcs libd.a libd.o
gcc a.o b.o c.o main.o -lf -ld -le -L./ -lc -o test
/usr/bin/ld: .//libe.a(libe.o): in function `func_e':
libe.c:(.text+0x28): undefined reference to `func_f'
collect2: error: ld returned 1 exit status
```

多静态库下，解决因链接顺序而失败的操作，及其正确运行：

```shell
link_order$ ./build.sh mul-lib-fail-solve
gcc -c main.c -o main.o -save-temps=obj
gcc -c a.c -o a.o -save-temps=obj
gcc -c b.c -o b.o -save-temps=obj
gcc -c c.c -o c.o -save-temps=obj
gcc -c libd.c -o libd.o -save-temps=obj
ar -rcs libd.a libd.o
gcc -c libe.c -o libe.o -save-temps=obj
ar -rcs libe.a libe.o
gcc -c libf.c -o libf.o -save-temps=obj
ar -rcs libf.a libf.o
gcc -c libd.c -o libd.o -save-temps=obj -DMUL_LIB_TEST
ar -rcs libd.a libd.o
gcc -Wl,--whole-archive -Wl,--start-group a.o b.o c.o main.o -lf -ld -le -L./ -lc -Wl,--end-group -Wl,-no-whole-archive -o test

link_order$ ./test
This is main in [main.c] !
This is func_a in [a.c] !
This is func_b in [b.c] !
This is func_c in [c.c] !
This is func_d in [libd.c] (static library) !
This is func_e in [libe.c] (static library) !
This is func_f in [libf.c] (static library) !
This is func_d_new in [libd.c] (static library) !
```

# 编译清除

在link_order目录下执行：

```c
./build.sh clean
```

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。