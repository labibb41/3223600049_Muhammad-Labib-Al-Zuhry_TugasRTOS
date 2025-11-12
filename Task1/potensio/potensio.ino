#define POT1_PIN 1  // Potensiometer 1
#define POT2_PIN 2  // Potensiometer 2

void TaskPot1(void *pvParameters) {
  while (1) {
    int value1 = analogRead(POT1_PIN);
    Serial.print("[Core 0] POT1: ");
    Serial.println(value1);
    vTaskDelay(100 / portTICK_PERIOD_MS); // delay 100ms
  }
}

void TaskPot2(void *pvParameters) {
  while (1) {
    int value2 = analogRead(POT2_PIN);
    Serial.print("[Core 1] POT2: ");
    Serial.println(value2);
    vTaskDelay(100 / portTICK_PERIOD_MS); // delay 100ms
  }
}

void setup() {
  Serial.begin(115200);
  delay(100); // beri waktu Serial mulai

  // Task POT1 di Core 0
  xTaskCreatePinnedToCore(TaskPot1, "POT1", 2048, NULL, 1, NULL, 0);

  // Task POT2 di Core 1
  xTaskCreatePinnedToCore(TaskPot2, "POT2", 2048, NULL, 1, NULL, 1);
}

void loop() {
  // Kosong, semua kerja ada di FreeRTOS task
}
