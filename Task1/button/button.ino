#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Definisi pin tombol
#define BUTTON1_PIN 4
#define BUTTON2_PIN 5

// Variabel global untuk menyimpan status
volatile int button1_state = 1;
volatile int button2_state = 1;

// ---------------------------------------------------------------------
// Task 1 - Membaca tombol 1 di Core 0
// ---------------------------------------------------------------------
void task_button1(void *pvParameter) {
    gpio_set_direction(BUTTON1_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON1_PIN);

    while (1) {
        int current = gpio_get_level(BUTTON1_PIN);
        if (current != button1_state) {
            button1_state = current;
            if (current == 0) {
                printf("[Core %d] Button 1 Pressed\n", xPortGetCoreID());
            } else {
                printf("[Core %d] Button 1 Released\n", xPortGetCoreID());
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // debounce
    }
}

// ---------------------------------------------------------------------
// Task 2 - Membaca tombol 2 di Core 1
// ---------------------------------------------------------------------
void task_button2(void *pvParameter) {
    gpio_set_direction(BUTTON2_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON2_PIN);

    while (1) {
        int current = gpio_get_level(BUTTON2_PIN);
        if (current != button2_state) {
            button2_state = current;
            if (current == 0) {
                printf("[Core %d] Button 2 Pressed\n", xPortGetCoreID());
            } else {
                printf("[Core %d] Button 2 Released\n", xPortGetCoreID());
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// ---------------------------------------------------------------------
// Fungsi utama RTOS
// ---------------------------------------------------------------------
void app_main() {
    printf("=== FreeRTOS Dual Core Button Test (ESP32-S3) ===\n");

    // Membuat task dan menetapkannya ke core tertentu
    xTaskCreatePinnedToCore(task_button1, "Button1 Task", 2048, NULL, 1, NULL, 0); // Core 0
    xTaskCreatePinnedToCore(task_button2, "Button2 Task", 2048, NULL, 1, NULL, 1); // Core 1
}
