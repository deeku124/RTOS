#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/event_groups.h>

TaskHandle_t xTask1;
TaskHandle_t xTask2;
TaskHandle_t xTask3;
EventGroupHandle_t evnt_grp;
EventBits_t Bit;

#define BIT_0 ( 1 << 0 )
#define BIT_7 ( 1 << 7 )

void task1(void *pvParameters)
{
    while(1)
    {
    printf("this is task1 \n");
    xEventGroupSetBits(evnt_grp,BIT_0);
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}
void task2(void *pvParameters)
{
    while(1)
    {
    printf("this is task2 \n");
    xEventGroupSetBits(evnt_grp,BIT_7);
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}
void task3(void *pvParameters)
{
    while(1)
    {
    printf("this is task3\n");
    Bit=xEventGroupWaitBits(evnt_grp,BIT_0 | BIT_7,pdTRUE,pdTRUE,pdMS_TO_TICKS(1000));
    ("")
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
evnt_grp=xEventGroupCreate();
printf("in main function\n");
xTaskCreate(task1,"Task1",2048,NULL,5,&xTask1);
xTaskCreate(task2,"Task2",2048,NULL,3,&xTask2);
xTaskCreate(task3,"Task3",2048,NULL,1,&xTask3);
}