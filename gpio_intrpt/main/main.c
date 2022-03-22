#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>
#include<FreeRTOS/semphr.h>

gpio_num_t gpio_LED=23;
gpio_num_t gpio_button=22;
esp_err_t retn;
SemaphoreHandle_t sem;
#define ESP_INTR_FLAG_DEFAULT 0



void task_LED(void *ARG)
{
    while(1)
    {
    if(xSemaphoreTake(sem,portMAX_DELAY))
    { 
    printf("BUTTON PRESSED\n");
    gpio_set_level(gpio_LED,1);
    }
    vTaskDelete(NULL);
    }
}
 
 void IRAM_ATTR button_isr(void* arg)
{
    printf("this is handler connection\n");
    xSemaphoreGiveFromISR(sem,NULL);
}

void app_main()
{
printf("in main function\n");
sem=xSemaphoreCreateBinary();
retn=gpio_reset_pin(gpio_LED);
if(retn==ESP_OK)
    {
        printf("gpio obtained!\n");
        gpio_set_direction(gpio_LED,GPIO_MODE_OUTPUT);
        if(retn==ESP_OK)
        {
            printf("gpio direction set to output\n");
        }
        else
        {
            printf("gpio direction cannot be set....invalid error!\n");  
        }
    }
else
    {
            printf("gpio cannot be obtained\n");
    }
retn=gpio_reset_pin(gpio_button);
if(retn==ESP_OK)
    {
        printf("gpio obtained!\n");
        gpio_set_direction(gpio_button,GPIO_MODE_INPUT);
        if(retn==ESP_OK)
        {
            printf("gpio direction set to input\n");
        }
        else
        {
            printf("gpio direction cannot be set....invalid error!\n");  
        }
    } 
else
    {
        printf("gpio cannot be obtained\n");
    }
    gpio_set_intr_type(gpio_button,GPIO_INTR_POSEDGE | GPIO_INTR_NEGEDGE);
    xTaskCreate(task_LED,"Task1",2048,NULL,5,NULL);
    gpio_install_isr_service (ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(gpio_button,button_isr,NULL);
    

}