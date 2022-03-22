#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>

TaskHandle_t xTask1;
gpio_num_t gpio_LED=23;
esp_err_t retn;


void task_LED(void *pvParameters)
{
    while(1)
    {
    //uint32_t level=1;
    printf("THIS IS LED_TASK\n");
    gpio_set_level(gpio_LED,1);
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    gpio_set_level(gpio_LED,0);
    vTaskDelay( 500 / portTICK_PERIOD_MS);
    }
}


void app_main()
{
printf("in main function\n");
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
xTaskCreate(task_LED,"Task1",2048,NULL,5,&xTask1);
}