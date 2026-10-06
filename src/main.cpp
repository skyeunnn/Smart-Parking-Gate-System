#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

//กำหนดขาอุปกรณ์
#define LED_GREEN 13  // LED สีเขียว
#define LED_RED   12  // LED สีแดง
#define SERVO_PIN 23  // Servo ใช้สำหรับเปิดปิดไม้กั้น
#define ADC_PIN   34  // Potentiometer ตั้งเวลาในการค้างของไม้กั้น
#define BTN1      14  // ปุ่มฉุกเฉิน
#define BTN2      4   // ปุ่มกดรถขาออก (กดเพื่อเคลียร์จำนวนรถ)
#define U_TRIG    18  // Ultrasonic Trig
#define U_ECHO    5   // Ultrasonic Echo

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MAX_PARKING = 6;      
int currentParked = 0;          
Servo barrierServo;             

unsigned long barrierCloseTime = 0;
bool isBarrierOpen = false;//โหมดฉุกเฉิน
bool isEmergencyMode = false;

float currentHoldTimeSec = 10.0;

bool lastBtn1State = HIGH;
bool lastBtn2State = HIGH;
unsigned long lastBtn1DebounceTime = 0;
unsigned long lastBtn2DebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 150;

//ประกาศฟังก์ชัน
int readUltrasonicCM();
void updateLEDs();
void updateOLEDDisplay();

void setup() {
  Serial.begin(115200);

  pinMode(U_TRIG, OUTPUT);
  pinMode(U_ECHO, INPUT); 
  pinMode(BTN1, INPUT_PULLUP); 
  pinMode(BTN2, INPUT_PULLUP); 
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  ESP32PWM::allocateTimer(0);
  barrierServo.setPeriodHertz(50);
  barrierServo.attach(SERVO_PIN, 500, 2400);
  
  // ตั้งค่าเริ่มต้น ไม้กั้นอยู่ในสถานะปิดที่ 90 องศา
  barrierServo.write(90); 
  isBarrierOpen = false;

  Wire.begin(21, 22); //SDA,SCL
  Wire.setClock(100000); 
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("OLED Failed");
  }

  updateLEDs();
  updateOLEDDisplay();
}

void loop() {
  unsigned long currentMillis = millis();

  // Potentiometer ปรับเวลาค้าง (1 - 10 วินาที)
  int potVal = analogRead(ADC_PIN);
  unsigned long barrierHoldDuration = map(potVal, 0, 4095, 1000, 10000); 
  currentHoldTimeSec = barrierHoldDuration / 1000.0;

  // ปุ่มฉุกเฉิน BTN1
  bool readingBtn1 = digitalRead(BTN1);
  if (readingBtn1 == LOW && lastBtn1State == HIGH && (currentMillis - lastBtn1DebounceTime > DEBOUNCE_DELAY)) {
    lastBtn1DebounceTime = currentMillis;
    isEmergencyMode = !isEmergencyMode; 

    if (isEmergencyMode) {
      barrierServo.write(0);  // โหมดฉุกเฉิน: เปิดไม้กั้นค้างที่ 0 องศา
    } else {
      barrierServo.write(90); // ปิดกลับลงมาที่ 90 องศา
      isBarrierOpen = false;
    }
    updateLEDs();
    updateOLEDDisplay();
  }
  lastBtn1State = readingBtn1;

  if (isEmergencyMode) return; 

  // ปุ่มเคลียร์จำนวนรถขาออก BTN2 
  bool readingBtn2 = digitalRead(BTN2);
  if (readingBtn2 == LOW && lastBtn2State == HIGH && (currentMillis - lastBtn2DebounceTime > DEBOUNCE_DELAY)) {
    lastBtn2DebounceTime = currentMillis;
    
    if (currentParked > 0) {
      currentParked--; // ลดจำนวนรถลง 1 คัน
      updateLEDs();
      updateOLEDDisplay();
    }
  }
  lastBtn2State = readingBtn2;

 
  // ระบบสั่งงานไม้กั้น (เปิดที่ 0° และ ปิดที่ 90°)
  // ถ้าไม้กั้นปิดอยู่ ที่ 90 องศา ให้ตรวจจับรถขาเข้า
  if (!isBarrierOpen) {
    int distancia = readUltrasonicCM();

    // เมื่อพบรถเข้ามาระยะ 4 - 10 ซม. และที่จอดรถยังไม่เต็ม
    if (distancia >= 4 && distancia <= 10 && currentParked < MAX_PARKING) {
      currentParked++;        // เพิ่มจำนวนรถ
      barrierServo.write(0);  // **สั่งเปิดไม้กั้นไปที่ 0 องศา**
      isBarrierOpen = true;
      
      // ตั้งเวลานับถอยหลังเพื่อปิดไม้กั้น
      barrierCloseTime = currentMillis + barrierHoldDuration; 
      
      updateLEDs();
      updateOLEDDisplay();
    }
  } 
  // ถ้าไม้กั้นกำลังเปิดอยู่ ที่ 0 องศา ให้รอนับเวลาปิด
  else {
    if (currentMillis >= barrierCloseTime) {
      barrierServo.write(90); // **สั่งปิดไม้กั้นกลับมาที่ 90 องศา**
      isBarrierOpen = false;
      
      updateLEDs();
      updateOLEDDisplay();
    }
  }

  delay(20);
}

int readUltrasonicCM() {
  digitalWrite(U_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(U_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(U_TRIG, LOW);

  long t = pulseIn(U_ECHO, HIGH, 25000); 
  if (t == 0) return 999; 
  return t / 58.2;
}

void updateLEDs() {
  if (currentParked >= MAX_PARKING) {
    digitalWrite(LED_RED, HIGH);   
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH); 
  }
}

void updateOLEDDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(18, 0);
  display.print(F("PARKING SYSTEM"));
  display.drawLine(0, 10, 128, 10, WHITE);

  if (isEmergencyMode) {
    display.setTextSize(2);
    display.setCursor(10, 25);
    display.print(F("EMERGENCY"));
    display.setTextSize(1);
    display.setCursor(15, 48);
    display.print(F("BARRIER FORCED OPEN"));
  } else {
    int available = MAX_PARKING - currentParked;
    
    display.setTextSize(1);
    display.setCursor(0, 18);
    display.print(F("Available: "));
    display.setTextSize(2);
    display.print(available);       
    display.print(F("/"));
    display.print(MAX_PARKING);

    display.setTextSize(1);
    display.setCursor(10, 40);
    if (available <= 0) {
      display.print(F("PARKING FULL"));
    } else {
      display.print(F("PARKING AVAILABLE"));
    }

    display.setCursor(0, 52);
    display.print(F("Hold Time: "));
    display.print(currentHoldTimeSec, 1);
    display.print(F(" s"));
  }

  display.display();
}