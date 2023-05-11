
#include <stdio.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <esp_err.h>
#include <dht/dht.h>
//#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHT_GPIO 16 // D1 pin
void setup()
{
    xMutex = xSemaphoreCreateMutex();
}
void temperature_task(void *arg)
{
    ESP_ERROR_CHECK(dht_init(DHT_GPIO, false));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        int humidity = 0;
        int temperature = 0;
        if (dht_read_data(DHT_TYPE_DHT22, DHT_GPIO, &humidity, &temperature) == ESP_OK) {
            // e.g. in dht22, 604 = 60.4%, 252 = 25.2 C
            // If you want to print float data, you should run `make menuconfig`
            // to enable full newlib and call dht_read_float_data() here instead
            printf("Humidity: %d Temperature: %d\n", humidity, temperature);
        } else {
            printf("Fail to get dht temperature data\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    int temp = Temperature;
    int humid = Humidity
    vTaskDelete(NULL);
}

void Output_Task(int temp,int humid)
{
 vTaskDelay(1000 / portTICK_PERIOD_MS)
 while(1)
 {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0); //col=0 row=0
  lcd.print("Humidity: %d Temperature: %d\n", humid, temp);
 }
}
void app_main() {
    xTaskCreate(temperature_task, "temperature task", 2048, NULL, tskIDLE_PRIORITY, NULL);
    xTaskCreate(Output_Task, "Printer Task ", 2048, NULL, 2, NULL);
}
