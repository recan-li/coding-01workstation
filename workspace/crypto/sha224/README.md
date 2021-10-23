# 概述

本目录主要是SHA256的源码实现及相关的接口的简要测试。

# 执行编译

在sha256目录下执行：

```c
./build.sh
```

# 编译清除

在sha256目录下执行：

```c
./build.sh clean
```

# demo测试

在sha256目录下执行：

```c
./test
```

如果输出：

```c
SHA256 digest test OK
```

则表示SHA256的摘要结果计算成功；

如果输出：

```c
SHA256 digest test FAIL
```

则表示SHA256的摘要运算结果计算失败。

