#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

TaskHandle_t xTask1;
TaskHandle_t xTask2;

void task1(void *pvParameters)
{
    while(1)
    {
    printf("this is task1 %d\n",uxTaskGetStackHighWaterMark(xTask1));
    printf("priority of task1: %d\n",uxTaskPriorityGet(xTask1));
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}
void task2(void *pvParameters)
{
    while(1)
    {
    printf("this is task2 %d\n",uxTaskGetStackHighWaterMark(xTask2));
    printf("priority of task2:%d\n",uxTaskPriorityGet(xTask2));
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
printf("in main function\n");
xTaskCreate(task1,"Task1",2048,NULL,5,&xTask1);
xTaskCreate(task2,"Task2",2048,NULL,3,&xTask2);
}