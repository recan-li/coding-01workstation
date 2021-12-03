# 概述

本目录主要是freeRTOS下任务优先级数值的问题验证测试。

# 文件说明

└── gc_section
    ├── build.sh 			编译脚本
    ├── main.c 				测试源代码的main.c
    └── README.md 			本说明文档

# 执行编译

由于是对freeRTOS系统接口的测试，所以这些代码不能在Linux系统下，直接将main.c里面的代码搬到对应跑freeRTOS的代码中去跑。

主要是执行main.c里面的test函数`freertos_task_priority_test`:

# demo测试及分析
见我的[CSDN博文](http://yyds.recan-li.cn)。