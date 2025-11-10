# 🧠 ESP32-S3 RTOS Multi-Task Control System

Proyek ini menampilkan **implementasi FreeRTOS berbasis dua core** pada **ESP32-S3 DevKitC-1**, dengan beberapa task paralel yang mengontrol LED, tombol, buzzer, servo, OLED, potensiometer, rotary encoder, dan motor stepper.

---

## ⚙️ Fitur Utama

| Komponen | Fungsi | Core RTOS |
|-----------|---------|-----------|
| **LED1–LED3** | Efek running / blink / breathing (PWM) | Core 0 |
| **Tombol BTN1** | Toggle buzzer (ON/OFF) | Core 0 |
| **Tombol BTN2** | Ganti mode LED | Core 0 |
| **Buzzer (PWM)** | Dihidupkan/dimatikan dengan BTN1 | Core 0 |
| **Potensiometer (ADC)** | Mengatur sudut servo (0–180°) | Core 1 |
| **OLED 0.96" I2C (SSD1306)** | Menampilkan nilai sensor dan status sistem | Core 1 |
| **Rotary Encoder (KY-040)** | Mengontrol kecepatan stepper & mendeteksi arah | Core 1 |
| **Tombol Encoder (SW)** | Mengubah arah putaran stepper (CW/CCW) | Core 1 |
| **Stepper Motor 28BYJ-48 (ULN2003)** | Bergerak dengan kecepatan tergantung encoder | Core 1 |
| **Servo Motor (SG90 / MG90S)** | Bergerak sesuai nilai potensiometer | Core 1 |

---

## 🧩 Arsitektur RTOS

Empat task berjalan secara paralel pada dua core:

| Task | Deskripsi | Core |
|------|------------|------|
| `taskLEDs` | Efek LED dinamis (chaser, blink, breathing) | 0 |
| `taskButtonsBuzzer` | Membaca tombol, mengatur buzzer, kirim notifikasi ke LED task | 0 |
| `taskServoOLED` | Baca potensiometer, kendalikan servo, update tampilan OLED | 1 |
| `taskStepper` | Kendalikan stepper dengan kecepatan berdasarkan rotary encoder | 1 |

---

## 🔌 Pin Mapping (ESP32-S3)

| Komponen | Pin | Keterangan |
|-----------|-----|------------|
| LED1 | 40 | Hijau |
| LED2 | 41 | Kuning |
| LED3 | 42 | Merah |
| BTN1 | 44 | Toggle buzzer |
| BTN2 | 2 | Ganti mode LED |
| Buzzer | 19 | PWM (LEDC) |
| OLED SDA | 5 | I²C data |
| OLED SCL | 4 | I²C clock |
| Potensiometer | 6 | ADC input (0–4095) |
| Encoder A | 9 | Interrupt A |
| Encoder B | 10 | Interrupt B |
| Encoder SW | 11 | Tombol tekan (LOW aktif) |
| Stepper IN1 (A–) | 39 | ULN2003 input |
| Stepper IN2 (A+) | 38 | ULN2003 input |
| Stepper IN3 (B+) | 37 | ULN2003 input |
| Stepper IN4 (B–) | 36 | ULN2003 input |
| Servo | 14 | PWM servo |

---

## 📦 Library yang Digunakan

Pastikan library berikut sudah terpasang di Arduino IDE:

- [`Adafruit GFX`](https://github.com/adafruit/Adafruit-GFX-Library)
- [`Adafruit SSD1306`](https://github.com/adafruit/Adafruit_SSD1306)
- [`ESP32Servo`](https://github.com/madhephaestus/ESP32Servo)
- `Wire` (bawaan ESP32 core)
- `FreeRTOS` (terintegrasi dalam ESP32 Arduino Core)

---

## 🧰 Cara Menggunakan

1. Buka proyek di **Arduino IDE** atau **PlatformIO**.  
2. Pilih board **ESP32-S3 DevKitC-1**.  
3. Upload program ke board.  
4. Lihat tampilan OLED:
   - Nilai **potensiometer**, **sudut servo**, **encoder count**, dan **status tombol encoder**.
5. Gunakan:
   - **BTN1** → hidup/matikan buzzer.  
   - **BTN2** → ganti pola LED.  
   - **Encoder** → ubah kecepatan stepper.  
   - **Tekan encoder** → ubah arah putaran stepper.  
   - **Potensiometer** → atur posisi servo (0°–180°).  

---

## 🖥️ Tampilan Wiring 
<img width="754" height="622" alt="image" src="https://github.com/user-attachments/assets/94b788db-3bb5-4a2d-ae76-d2264f0e94d5" />


## 🖥️ Video hasil

https://github.com/user-attachments/assets/b7414a7a-3112-4ab9-a568-c82d47a1bca5


