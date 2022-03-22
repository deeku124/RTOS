#include<stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>


QueueHandle_t queue;
BaseType_t result;

void Task1(void *pvParameters)
{
    int i;
    char data[10]="hello!";
    while(1)
    { 
    for(i=0;i<6;i++)
    {
        xQueueSend(queue,&data[i],portMAX_DELAY);
        printf("data being sent is %c\n",data[i]);
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
    /*if(data==10)
    {
        printf("data being sent is %d\n",data);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }*/
    }
}

void Task2(void *pvParameters)
{
    char Buffer[10];
    while(1)
    {
    while(xQueueReceive(queue,&Buffer,portMAX_DELAY))
    {
    printf("data received from queue it is :%s\n",Buffer);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
printf("main function\n");
queue=xQueueCreate(10,sizeof(char));
if(queue==NULL)
{
    printf("queue is created\n");
}
xTaskCreate(Task1,"Task_1",2048,NULL,5,NULL);
xTaskCreate(Task2,"Task_2",2048,NULL,1,NULL);
}