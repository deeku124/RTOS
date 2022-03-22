#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TimerHandle_t timer1;


int count=0;
void TCALLBACK(TimerHandle_t xTimer)
{
printf("timer callback function\n");
count++;
if(count==5)
{
    printf("count is 5 so stopping timer\n");
    xTimerStop(xTimer,0);
}
}

void TIMER(void *pv)
{
    timer1=xTimerCreate("s/wtimer",pdMS_TO_TICKS(2000),pdTRUE,NULL,TCALLBACK);
    
    xTimerStart(timer1,0);
    
     vTaskDelete(NULL);
}

void app_main()
{
xTaskCreate(TIMER,"TIMER",2048,NULL,5,NULL);
while(1)
{
printf("main function\n");
vTaskDelay(pdMS_TO_TICKS(1000));
}
}