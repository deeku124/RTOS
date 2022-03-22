#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>
#include<freertos/FreeRTOSConfig.h>

TaskHandle_t xTask1;
TaskHandle_t xTask2;
SemaphoreHandle_t sem;

static uint32_t IntrptHndlr(void)
{
    BaseType_t xHigherPriorityTaskWoken;
    xSemaphoreGiveFromISR(sem, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void task1(void *pvParameters)
{
    while(1)
    {
    printf("this is task1 GENERATING THE INTERRUPT\n");
    vPortGenerateSimulatedInterrupt(10);
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}
void task2(void *pvParameters)
{
    while(1)
    {
    xSemaphoreTake(sem,portMAX_DELAY);
    printf("this is handler task for the interrupt\n");
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
printf("in main function\n");
sem=xSemaphoreCreateBinary();
xTaskCreate(task1,"MAIN TASK",2048,NULL,6,NULL);
xTaskCreate(task2,"HANDLERTASK",2048,NULL,8,NULL);
vPortSetInterruptHandler(10,IntrptHndlr);
}