#if 1

#define task_debug(fmt, arg...)     cli_printf(fmt, ##arg)

#include "task.h"

TaskHandle_t calling_task;
TaskHandle_t lower_task;
TaskHandle_t higher_task;

void create_lower_task(void *data)
{
    TaskStatus_t TaskStatus;

    vTaskGetInfo( lower_task,
                   &TaskStatus,
                   0,
                   eInvalid);
    while(1) {
        task_debug("%s:%d >>> prio: %d\r\n", __func__, __LINE__, TaskStatus.uxCurrentPriority);
        vTaskDelay(1000);
    }
}

void create_higher_task(void *data)
{
    TaskStatus_t TaskStatus;

    vTaskGetInfo( higher_task,
                   &TaskStatus,
                   0,
                   eInvalid);
    
    while(1) {
        task_debug("%s:%d >>> prio: %d\r\n", __func__, __LINE__, TaskStatus.uxCurrentPriority);
        vTaskDelay(1000);
    }
}

void create_calling_task(void *data)
{
    int ret;
    int lower_prio = 3;
    int higher_prio = 60;
    TaskStatus_t TaskStatus;

    (void)higher_prio;

    vTaskGetInfo( lower_task,
                   &TaskStatus,
                   0,
                   eInvalid);

    task_debug("%s:%d >>> prio: %d\r\n", __func__, __LINE__, TaskStatus.uxCurrentPriority);
    ret = xTaskCreate(create_lower_task, "test-2", 256, NULL, lower_prio, 
        (TaskHandle_t * const )&lower_task);
    if (ret != pdPASS) {
        task_debug("Error: Failed to create test task: %d\r\n", ret);
    }
    task_debug("%s:%d >>>\r\n", __func__, __LINE__);
#if 1
    task_debug("%s:%d >>>\r\n", __func__, __LINE__);
    ret = xTaskCreate(create_higher_task, "test-3", 256, NULL, higher_prio, 
        (TaskHandle_t * const )&higher_task);
    if (ret != pdPASS) {
        task_debug("Error: Failed to create test task: %d\r\n", ret);
    }
    task_debug("%s:%d >>>\r\n", __func__, __LINE__);
#endif

    while(1) {
        task_debug("%s:%d >>> prio: %d\r\n", __func__, __LINE__, TaskStatus.uxCurrentPriority);
        vTaskDelay(1000);
    }
}

void freertos_task_priority_test(void)
{
    int ret;
    int cur_prio = 4;

    {
        TaskStatus_t TaskStatus;

        vTaskGetInfo( xTaskGetHandle( "extended_app" ),
                   &TaskStatus,
                   0,
                   eInvalid);
        task_debug("%s:%d >>> prio: %d\r\n", __func__, __LINE__, TaskStatus.uxCurrentPriority);
    }

    task_debug("%s:%d >>>\r\n", __func__, __LINE__);
    ret = xTaskCreate(create_calling_task, "test-1", 256, NULL, cur_prio,  
        (TaskHandle_t * const )&calling_task);
    if (ret != pdPASS) {
        cli_printf("Error: Failed to create test task: %d\r\n", ret);
    }
    task_debug("%s:%d >>>\r\n", __func__, __LINE__);
}

#endif