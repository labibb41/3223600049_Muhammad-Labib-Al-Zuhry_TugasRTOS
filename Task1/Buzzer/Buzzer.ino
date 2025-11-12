#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Pin buzzer
#define BUZZER1_PIN 8
#define BUZZER2_PIN 9

// ---------------------------------------------------------------------
// Task 1 – Buzzer 1 di Core 0
// ---------------------------------------------------------------------
void task_buzzer1(void *pvParameter) {
    gpio_set_direction(BUZZER1_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        // Bunyi
        gpio_set_level(BUZZER1_PIN, 1);
        printf("[Core %d] Buzzer 1 ON\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(200));  // durasi beep 200 ms

        // Diam
        gpio_set_level(BUZZER1_PIN, 0);
        printf("[Core %d] Buzzer 1 OFF\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(500));  // jeda antar beep
    }
}

// ---------------------------------------------------------------------
// Task 2 – Buzzer 2 di Core 1
// ---------------------------------------------------------------------
void task_buzzer2(void *pvParameter) {
    gpio_set_direction(BUZZER2_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(BUZZER2_PIN, 1);
        printf("[Core %d] Buzzer 2 ON\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(300));  // durasi beep 300 ms

        gpio_set_level(BUZZER2_PIN, 0);
        printf("[Core %d] Buzzer 2 OFF\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(800));  // jeda antar beep
    }
}

// ---------------------------------------------------------------------
// Fungsi utama RTOS
// ---------------------------------------------------------------------
void app_main() {
    printf("=== FreeRTOS Dual Core Buzzer Test (ESP32-S3) ===\n");

    // Membuat task dan menetapkan ke core tertentu
    xTaskCreatePinnedToCore(task_buzzer1, "Buzzer1 Task", 2048, NULL, 1, NULL, 0); // Core 0
    xTaskCreatePinnedToCore(task_buzzer2, "Buzzer2 Task", 2048, NULL, 1, NULL, 1); // Core 1
}
