// Encoder 1
#define CLK1 18
#define DT1  19

// Encoder 2
#define CLK2 15
#define DT2  16

volatile int count1 = 0;
volatile int count2 = 0;

int lastState1;
int lastState2;

void TaskEncoder1(void *pvParameters) {
  pinMode(CLK1, INPUT_PULLUP);
  pinMode(DT1, INPUT_PULLUP);

  lastState1 = digitalRead(CLK1);

  while (1) {
    int currentState = digitalRead(CLK1);
    if (currentState != lastState1) {
      if (digitalRead(DT1) != currentState) count1++;
      else count1--;

      Serial.print("Encoder1: ");
      Serial.println(count1);
    }
    lastState1 = currentState;
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void TaskEncoder2(void *pvParameters) {
  pinMode(CLK2, INPUT_PULLUP);
  pinMode(DT2, INPUT_PULLUP);

  lastState2 = digitalRead(CLK2);

  while (1) {
    int currentState = digitalRead(CLK2);
    if (currentState != lastState2) {
      if (digitalRead(DT2) != currentState) count2++;
      else count2--;

      Serial.print("Encoder2: ");
      Serial.println(count2);
    }
    lastState2 = currentState;
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(100); // beri waktu Serial mulai

  // Jalankan tiap encoder di core berbeda
  xTaskCreatePinnedToCore(TaskEncoder1, "ENC1", 2048, NULL, 1, NULL, 0); // core 0
  xTaskCreatePinnedToCore(TaskEncoder2, "ENC2", 2048, NULL, 1, NULL, 1); // core 1
}

void loop() {
  // Kosong karena semua dijalankan di task
}
