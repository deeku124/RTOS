#include<stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xtask1;

void Task_example(void *pvParameters)
{
    printf("task function\n");
    vTaskDelete(NULL);
   // printf("task deleted\n");
}

void app_main()
{
 BaseType_t result;
printf("main function\n");
result=xTaskCreate(Task_example,"Task_example",2048,NULL,5,&xtask1);
if(result==pdPASS)
{
    printf("task_example is created\n");
   
}
}