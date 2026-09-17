#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/i2c.h"
#include "esp_log.h"

#define TAG "PWM Example"
#define PWM_GPIO 2
#define TEST_INA219_W_FAN

// PWM Function Declarations
extern int duty_cycle_to_bits(int duty_cycle);
extern void configure_fan_pwm(void);

// I2C Function Declarations
extern void init_i2c(void);
extern void sweep_i2c(void);
extern void ina219_task(void *pvParameters);

// DHT Function Declarations
extern void dht11_task(void *pvParameters);


// Fan Global Variables
int fan_duty[3] = {10, 10, 10};
ledc_timer_config_t ledc_fan_timer[3];
ledc_channel_config_t ledc_fan_channel[3];

// DHT Global Variables
uint8_t *humidity;
uint8_t *temperature;

void app_main(void)
{
    // Initialize PWM Hardware
    configure_fan_pwm();
    init_i2c();
    

#ifdef TEST_INA219_W_FAN
    xTaskCreate(ina219_task, "ina219_task", 4096, NULL, 5, NULL);
    xTaskCreate(dht11_task, "dht11_task", 4096, NULL, 5, NULL);
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
        if (fan_duty[0] < 80)
        {
            fan_duty[0] += 30;
        }
        else
        {
            fan_duty[0] = 0;
        }

        int bit_duty = duty_cycle_to_bits(fan_duty[0]);

        // Push updated duty cycle to the LEDC hardware module
        ledc_set_duty(ledc_fan_channel[0].speed_mode, ledc_fan_channel[0].channel, bit_duty);
        ledc_update_duty(ledc_fan_channel[0].speed_mode, ledc_fan_channel[0].channel);

        // ESP_LOGI(TAG, "PWM updated on GPIO %d (fan duty: %d%%)", PWM_GPIO, fan_duty[0]);
    }
#endif
}