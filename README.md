# Smart Parking Gate System
 ระบบจำลองไม้กั้นอัตโนมัติและนับจำนวนรถเข้า-ออกลาน จอดรถ โดยนำ
 เทคโนโลยีอิเล็กทรอนิกส์และไมโครคอนโทรลเลอร์มาประยุกต์ใช้ในการตรวจจับรถ
 คำนวณพื้นที่ว่าง จัดการเปิด-ปิดไม้กั้น แสดงผลสถานะ และเพิ่มฟังก์ชันความ
 สะดวกและความปลอดภัย เพื่อให้ผู้ใช้งานสามารถทราบสถานะที่จอดรถได้ทันที
 และช่วยให้การบริหารจัดการลานจอดรถมีประสิทธิภาพยิ่งขึ้น

# ฟีเจอร์หลัก (Features)
- การตรวจจับยานพาหนะ (Vehicle Detection): ใช้เซนเซอร์วัดระยะทางด้วยคลื่นเสียง (Ultrasonic Sensor) ตรวจจับรถยนต์ทั้งฝั่งขาเข้า (Entry)
- การควบคุมทางเข้า (Barrier Control): ใช้มอเตอร์เซอร์โว (Servo Motor) ในการสั่งเปิด-ปิดไม้กั้นเมื่อมีรถผ่าน
- การคำนวณและแสดงผลช่องจอด (Occupancy & Display): คำนวณจำนวนรถและพื้นที่ว่างคงเหลือแบบ Real-time พร้อมแสดงผลผ่านหน้าจอ OLED

# Block Diagram
<img width="1920" height="1080" alt="image" src="https://github.com/user-attachments/assets/904e10da-6907-42d4-a0ed-490bf56ba9ef" />

# ผังงานการทำงาน (Flowchart)
<img width="1496" height="1315" alt="image" src="https://github.com/user-attachments/assets/fa9e6217-9b5f-4c5b-8b31-2f150ee93d5a" />

# อุปกรณ์ที่ต้องใช้ (Hardware Requirements)
- ESP32 DOIT DevKit V1
- Oled display
- Ultrasonic sensor
- Potentiometer
- Servo motor
- LED(Red,Green)
- Push-button(เปิดไม้กั้นฉุกเฉิน1ตัว และเคลียร์จำนวนรถ1ตัว)

# รายการเอกสารทางเทคนิค (Component Datasheets)
| อุปกรณ์ (Component) | เอกสารอ้างอิง (Datasheet) |
| -- | -- |
| ESP32 DOIT DevKit V1 |[ESP32 Datasheet](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32/esp-dev-kits-en-master-esp32.pdf)|
| OLED Display | [SSD1306 Datasheet](https://e2e.ti.com/cfs-file/__key/communityserver-discussions-components-files/791/SSD1306-Datasheet-for-096-OLED-_2800_1_2900_.pdf) |
| HC-SR04 Ultrasonic | [HC-SR04 Datasheet](https://www.alldatasheet.com/datasheet-pdf/view/1132204/ETC2/HCSR04.html) |
| Servo Motor | [SG90 Datasheet](https://www.friendlywire.com/projects/ne555-servo-safe/SG90-datasheet.pdf) |

# การต่อสาย (Pin Configuration)
| อุปกรณ์ (Component) | ขา ESP32 (Pin) | Note |
| -- | -- | -- |
| OLED SDA | GPIO 21 | I2C |
| OLED SCL | GPIO 22 | I2C |
| Ultrasonic TRIG | GPIO 18 | HC-SR04 |
| Ultrasonic ECHO | GPIO 5 | HC-SR04 |
| Green LED | GPIO 12 | Parking Available |
| Red LED | GPIO 13 | Parking Full |
| Potentiometer | GPIO 34 | Analog Input |
| Button 1 | GPIO 4 | Emergency |
| Button 2 | GPIO 14 | Exit |
| Servo Motor | GPIO 23 | Barrier Control |

# แผนภาพการต่อวงจร (Circuit Diagram)
<img width="1081" height="797" alt="Screenshot 2026-10-02 180459" src="https://github.com/user-attachments/assets/8c69defb-ddb3-4130-ab8d-9de17a7cbebe" />

# ซอฟต์แวร์และไลบรารี (Software & Libraries)
- `Adafruit SSD1306`
- `ezButton`
- `ESP32Servo`

# คู่มือและขั้นตอนการใช้งาน (How to Use & Quick Start)
1. การเตรียมระบบก่อนใช้งาน (System Setup)
​ ต่อสายจ่ายไฟ 5V (Adapter) เข้ากับระบบ เพื่อจ่ายไฟเลี้ยงให้กับ ESP32, Servo Motor, เซนเซอร์ และหน้าจอ OLED
​ เมื่อเปิดเครื่องครั้งแรก ระบบจะทำการเปิดหน้าจอ OLED ขึ้นมา แสดงผลหน้าจอเริ่มต้น PARKING SYSTEM
​ ไม้กั้น (Servo) จะทำการเซ็ตตำแหน่งปิดลงมาที่ 90 องศา โดยอัตโนมัติ
​ ปรับตั้งเวลาค้างของไม้กั้นโดยหมุน Potentiometer (ตั้งเวลาได้ระหว่าง 1 ถึง 10 วินาที) ค่าจะแสดงผลบนหน้าจอ OLED ในช่อง Hold Time
​
2. ขั้นตอนการทำงานปกติ — รถเข้า (Entry Process)
​ เมื่อรถขับเข้ามาจอดหน้าทางเข้าในระยะ 4 - 10 เซนติเมตร ตรงกับ Ultrasonic Sensor
​ ระบบจะตรวจสอบจำนวนที่จอดรถว่าง:
​ กรณีที่จอดรถยังไม่เต็ม:
 ​จำนวนรถบวกเพิ่ม 1 คัน (Current Parked + 1)
​ ไม้กั้นหมุนเปิดขึ้นไปที่ 0 องศา
​ ไฟ LED สีเขียวติด (หากยังไม่เต็ม)
​ หน้าจอ OLED แสดงสถานะ PARKING AVAILABLE และอัปเดตจำนวนที่จอดว่าง
​ เมื่อรถผ่านไป ไม้กั้นจะเปิดค้างไว้ตามเวลาที่ตั้งค่าจาก Potentiometer แล้วปิดลงมาที่ 90 องศา ตามเดิม
  ​กรณีที่จอดรถเต็มแล้ว (6/6):
  ​ไฟ LED สีแดงจะติด
​  หน้าจอ OLED แสดงข้อความ PARKING FULL
​  ไม้กั้นจะไม่เปิดยอมให้รถเข้า จนกว่าจะมีรถขาออก

3. ขั้นตอนการทำงานปกติ — รถออก (Exit Process)
​เมื่อมีรถต้องการออกจากลานจอด ให้กดปุ่ม BTN2 (ปุ่มรถขาออก)
​ระบบจะทำการลดจำนวนรถลง 1 คัน (Current Parked - 1)
 ​หน้าจอ OLED และไฟ LED สีเขียวจะอัปเดตจำนวนที่จอดว่างทันที เพื่อให้รถคันใหม่สามารถเข้าจอดได้
  
  4. ขั้นตอนการใช้งานโหมดฉุกเฉิน (Emergency Mode)
  ​เมื่อเกิดเหตุฉุกเฉิน (เช่น ไฟไหม้ หรือต้องการเปิดทางด่วน):
   ​กดปุ่ม BTN1 (ปุ่มฉุกเฉิน) 1 ครั้ง
   ​ไม้กั้นจะเปิดขึ้นไปที่ 0 องศา ทันที และเปิดค้างไว้ตลอดเวลา
   ​หน้าจอ OLED จะขึ้นเตือนข้อความตัวใหญ่ว่า EMERGENCY และ BARRIER FORCED OPEN
   ​ระบบจะ หยุด/ล็อก การทำงานของ Ultrasonic และปุ่มรถออกชั่วคราวเพื่อความปลอดภัย
   ​การยกเลิกโหมดฉุกเฉินเพื่อกลับสู่สภาวะปกติ:
   ​กดปุ่ม BTN1 (ปุ่มฉุกเฉิน) ซ้ำอีก 1 ครั้ง
   ​ไม้กั้นจะปิดลงมาที่ 90 องศา หน้าจอ OLED และไฟ LED จะกลับมาแสดงสถานะลานจอดตามปกติ
  
# ภาพชิ้นงานจริง
<img width="2364" height="1774" alt="image" src="https://github.com/user-attachments/assets/88a7368e-d703-4781-b0a5-76b1baf7db40" />

# วิดีโอสาธิตการทำงาน (Video Demonstration)
https://drive.google.com/file/d/1DpSWVMpt97qAKMgUWJTMub2WuIHpYued/view?usp=drivesdk
# เอกสาร (Documentation)
https://sway.cloud.microsoft/wZeZ7cTVoWPW3O0D
