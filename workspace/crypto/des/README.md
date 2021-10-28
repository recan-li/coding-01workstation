# 概述

本目录主要是DES的源码实现及相关的接口的简要测试。

# 执行编译

在des目录下执行：

```c
./build.sh
```

# 编译清除

在des目录下执行：

```c
./build.sh clean
```

# demo测试

在des目录下执行：

```c
./test
```

如果输出：

```c
DES encrypt OK
DES decrypt OK
```

则表示DES的结果计算成功；

如果输出：

```c
DES encrypt FAIL
DES decrypt FAIL
```

则表示DES的结果计算失败。

