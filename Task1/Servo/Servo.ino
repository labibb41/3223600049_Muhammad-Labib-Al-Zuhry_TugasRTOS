#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

// Pin servo
#define SERVO1_PIN 14
#define SERVO2_PIN 19

// Fungsi konversi derajat ke duty LEDC
uint32_t servo_angle_to_duty(int angle) {
    int min_pulse = 500;   // 0.5 ms
    int max_pulse = 2500;  // 2.5 ms
    int us = min_pulse + (max_pulse - min_pulse) * angle / 180;
    // 50 Hz = periode 20000 µs
    return (us * 16383) / 20000;  // 14-bit resolution
}

// =====================================================
// Task 1 - Servo 1 di Core 0
// =====================================================
void task_servo1(void *pvParameter) {
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_14_BIT, // GANTI DARI 16_BIT
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = SERVO1_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&channel_conf);

    while (1) {
        for (int angle = 0; angle <= 180; angle += 30) {
            uint32_t duty = servo_angle_to_duty(angle);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            printf("[Core %d] Servo 1 angle: %d°\n", xPortGetCoreID(), angle);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        for (int angle = 180; angle >= 0; angle -= 30) {
            uint32_t duty = servo_angle_to_duty(angle);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            printf("[Core %d] Servo 1 angle: %d°\n", xPortGetCoreID(), angle);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

// =====================================================
// Task 2 - Servo 2 di Core 1
// =====================================================
void task_servo2(void *pvParameter) {
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_1,
        .duty_resolution = LEDC_TIMER_14_BIT, // GANTI DARI 16_BIT
        .freq_hz = 50,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = SERVO2_PIN,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_1,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&channel_conf);

    while (1) {
        for (int angle = 0; angle <= 180; angle += 45) {
            uint32_t duty = servo_angle_to_duty(angle);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            printf("[Core %d] Servo 2 angle: %d°\n", xPortGetCoreID(), angle);
            vTaskDelay(pdMS_TO_TICKS(600));
        }
        for (int angle = 180; angle >= 0; angle -= 45) {
            uint32_t duty = servo_angle_to_duty(angle);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
            printf("[Core %d] Servo 2 angle: %d°\n", xPortGetCoreID(), angle);
            vTaskDelay(pdMS_TO_TICKS(600));
        }
    }
}

// =====================================================
// Fungsi utama
// =====================================================
void app_main() {
    printf("=== Dual Servo with FreeRTOS on ESP32-S3 ===\n");

    // Jalankan 2 task di 2 core
    xTaskCreatePinnedToCore(task_servo1, "Servo1 Task", 4096, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task_servo2, "Servo2 Task", 4096, NULL, 1, NULL, 1);
}
