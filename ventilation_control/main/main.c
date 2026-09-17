#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/i2c.h"
#include "esp_log.h"

#define TAG "PWM Example"
#define PWM_GPIO 2


// PWM Function Declarations
extern int duty_cycle_to_bits(int duty_cycle);
extern void configure_fan_pwm(void);

// Fan Global Variables
int fan_duty[3] = {10, 10, 10};
ledc_timer_config_t ledc_fan_timer[3];
ledc_channel_config_t ledc_fan_channel[3];

// I2C Function Declarations
extern void init_i2c(void);
extern void sweep_i2c(void);
extern void ina219_task(void *pvParameters);

// DHT Function Declarations
extern void dht11_task(void *pvParameters);

// DHT Global Variables
uint8_t *humidity;
uint8_t *temperature;

// ESP32 CAM Function Declarations


// ESP32 CAM Global Variables

// #define TEST_INA219_W_FAN
// #define TEST_ESP32_CAM

void app_main(void)
{
    configure_fan_pwm();
    init_i2c();

#if defined(TEST_INA219_W_FAN)
    xTaskCreate(ina219_task, "ina219_task", 4096, NULL, 5, NULL);
    xTaskCreate(dht11_task, "dht11_task", 4096, NULL, 5, NULL);
#endif

#if defined(TEST_ESP32_CAM)
    
#endif

    // Main loop runs regardless
    while (1)
    {
#if defined(TEST_INA219_W_FAN)
        vTaskDelay(pdMS_TO_TICKS(5000));
        if (fan_duty < 80)
        {
            fan_duty += 30;
        }
        else
        {
            fan_duty = 0;
        }

        int bit_duty = duty_cycle_to_bits(fan_duty);
        ledc_set_duty(ledc_fan_channel.speed_mode, ledc_fan_channel.channel, bit_duty);
        ledc_update_duty(ledc_fan_channel.speed_mode, ledc_fan_channel.channel);
#endif

#if defined(TEST_ESP32_CAM)
        // esp32_cam_loop();
#endif
    }
}
