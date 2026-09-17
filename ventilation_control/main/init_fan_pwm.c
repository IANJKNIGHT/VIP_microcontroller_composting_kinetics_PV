#include <stdio.h>
#include "driver/ledc.h"
#include "esp_log.h"

#define PWM_GPIO 2
// Extern global variable for fan duty cycles
extern ledc_timer_config_t ledc_fan_timer[3];
extern ledc_channel_config_t ledc_fan_channel[3];
extern int fan_duty[3];
extern int duty_cycle_to_bits(int duty_cycle);

void configure_fan_pwm(void)
{

    ledc_fan_timer[0] = (ledc_timer_config_t) {
            .speed_mode = LEDC_LOW_SPEED_MODE, // updates registers with the APB clock - allows Low-Speed channels to continue generating PWM signals even when the CPU enters light sleep mode
            .duty_resolution = LEDC_TIMER_13_BIT,
            .timer_num = LEDC_TIMER_0,
            .freq_hz = 1000,  // 1 kHz frequency
            .clk_cfg = LEDC_AUTO_CLK // LEDC source clock will be automatically selected based on the giving resolution and duty parameter when init the timer
        };
    (ledc_timer_config(&ledc_fan_timer[0]));
        // Configure LEDC channel
    ledc_fan_channel[0] = (ledc_channel_config_t) {
            .gpio_num = PWM_GPIO,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel = LEDC_CHANNEL_0,
            .timer_sel = LEDC_TIMER_0,
            .duty = duty_cycle_to_bits(fan_duty[0]),  // 50% of 8192 (13-bit)
            .hpoint = 0
        };
    (ledc_channel_config(&ledc_fan_channel[0]));
}

