#include<stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>


TaskHandle_t task1;
TaskHandle_t task2;
QueueHandle_t queue;
BaseType_t result;


void Task1(void *pvParameters)
{
    int data=0;
    while(1)
    { 
    data++;
    
    xQueueSend(queue,&data,portMAX_DELAY);
    printf("data being sent is %d\n",data);
    vTaskSuspend(task1);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    if(data==10)
    {
        printf("data being sent is %d\n",data);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    }
}

void Task2(void *pvParameters)
{
    int Buffer;
    while(1)
    {
    vTaskResume(task1);
    xQueueReceive(queue,&Buffer,portMAX_DELAY);
    printf("data received from queue it is :%d\n",Buffer);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }  
}

void app_main()
{
printf("main function\n");
queue=xQueueCreate(10,sizeof(int));
xTaskCreate(Task1,"Task_1",2048,NULL,5,&task1);
xTaskCreate(Task2,"Task_2",2048,NULL,3,&task2);
}