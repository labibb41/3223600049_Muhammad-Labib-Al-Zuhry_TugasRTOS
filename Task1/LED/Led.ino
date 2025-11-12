#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Definisi pin LED
#define LED1_PIN 5
#define LED2_PIN 6
#define LED3_PIN 7

// ---------------------------------------------------------------------
// Task 1 - LED1 di Core 0 (300 ms)
// ---------------------------------------------------------------------
void task_led1(void *pvParameter) {
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED1_PIN, 1);
        printf("[Core %d] LED1 ON\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(300));

        gpio_set_level(LED1_PIN, 0);
        printf("[Core %d] LED1 OFF\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

// ---------------------------------------------------------------------
// Task 2 - LED2 di Core 1 (500 ms)
// ---------------------------------------------------------------------
void task_led2(void *pvParameter) {
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED2_PIN, 1);
        printf("[Core %d] LED2 ON\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED2_PIN, 0);
        printf("[Core %d] LED2 OFF\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// ---------------------------------------------------------------------
// Task 3 - LED3 di Core 0 (1000 ms)
// ---------------------------------------------------------------------
void task_led3(void *pvParameter) {
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        gpio_set_level(LED3_PIN, 1);
        printf("[Core %d] LED3 ON\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(LED3_PIN, 0);
        printf("[Core %d] LED3 OFF\n", xPortGetCoreID());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// ---------------------------------------------------------------------
// app_main() - Titik awal program FreeRTOS ESP-IDF
// ---------------------------------------------------------------------
void app_main() {
    printf("=== FreeRTOS Dual Core LED Test (ESP32-S3) ===\n");

    // Membuat task dan memetakan ke core tertentu
    xTaskCreatePinnedToCore(task_led1, "LED1 Task", 2048, NULL, 1, NULL, 0); // Core 0
    xTaskCreatePinnedToCore(task_led2, "LED2 Task", 2048, NULL, 1, NULL, 1); // Core 1
    xTaskCreatePinnedToCore(task_led3, "LED3 Task", 2048, NULL, 1, NULL, 0); // Core 0
}
