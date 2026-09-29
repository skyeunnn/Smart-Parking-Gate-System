# Smart Parking Gate System
ระบบจำลองไม้กั้นอัตโนมัติและนับจำนวนรถเข้า-ออกลาน    จอดรถ โดยนำเทคโนโลยีอิเล็กทรอนิกส์และไมโครคอนโทรลเลอร์มาประยุกต์ใช้ในการตรวจจับรถ คำนวณพื้นที่ว่าง จัดการเปิด-ปิดไม้กั้น แสดงผลสถานะ และเพิ่มฟังก์ชันความสะดวกและความปลอดภัย เพื่อให้ผู้ใช้งานสามารถทราบสถานะที่จอดรถได้ทันที และช่วยให้การบริหารจัดการลานจอดรถมีประสิทธิภาพยิ่งขึ้น
# ฟีเจอร์หลัก (Features)
- การตรวจจับยานพาหนะ (Vehicle Detection): ใช้เซนเซอร์วัดระยะทางด้วยคลื่นเสียง (Ultrasonic Sensor) ตรวจจับรถยนต์ทั้งฝั่งขาเข้า (Entry) 
- การควบคุมทางเข้า (Barrier Control): ใช้มอเตอร์เซอร์โว (Servo Motor) ในการสั่งเปิด-ปิดไม้กั้นเมื่อมีรถผ่าน
- การคำนวณและแสดงผลช่องจอด (Occupancy & Display): คำนวณจำนวนรถและพื้นที่ว่างคงเหลือแบบ Real-time พร้อมแสดงผลผ่านหน้าจอ OLED
# Block Diagram
<img width="1920" height="1080" alt="Ultrasonic sensor" src="https://github.com/user-attachments/assets/51231a02-3329-4a8e-a5cd-3a84cd33dc2a" />

# ผังงานการทำงาน (Flowchart)

# อุปกรณ์ที่ต้องใช้ (Hardware Requirements)
- ESP32 DOIT DevKit V1
- Oled display
- Ultrasonic sensor
- Potentiometer
- Servo motor
- Push-button(เปิดไม้กั้นฉุกเฉิน1ตัว และเคลียร์จำนวนรถ1ตัว)
- LED(Red,Green)
# รายการเอกสารทางเทคนิค (Component Datasheets)
| อุปกรณ์ (Component) | เอกสารอ้างอิง (Datasheet) |
| --- | --- |
| ESP32 DOIT DevKit V1 | [ESP32 Datasheet](https://drive.google.com/file/d/1Ic243PlvosYpHaeQ5Si0iNkPEw1R4hw9/view) |
| OLED Display | [SSD1306 Datasheet](https://drive.google.com/file/d/14kyQGCQ9KdR1j_5-WBYeHLpgWmtnzE1P/view) |
| Servo Motor | [SG90 Datasheet](https://www.friendlywire.com/projects/ne555-servo-safe/SG90-datasheet.pdf) |
| HC-SR04 Ultrasonic | [HC-SR04 Datasheet](https://drive.google.com/file/d/1ITVnQZJ2ADjACwu-oFpP6KKXNsSg8Tzs/view) |
# การต่อสาย (Pin Configuration)
| Component | PIN | Note |
| --- | --- | --- |
| OLED SDA | GPIO 21 | I2C |
| OLED SCL | GPIO 22 | I2C |
| Potentiometer | GPIO 34 | Analog Input |
| HC-SR04 Trig | GPIO 18 | |
| HC-SR04 Echo | GPIO 5 | |
# การต่อวงจร (Circuit Diagram)

# Software & Libraries
Libraries มี
Adafruit SSD1306
ezButton
ESP32Servo

# คู่มือและขั้นตอนการใช้งาน (How to Use & Quick Start)

# โครงสร้างและการออกแบบ🚘
<img width="1414" height="2000" alt="image" src="https://github.com/user-attachments/assets/95bf450d-9382-442f-abc2-be4b6a711761" />

# หน้าที่ของปุ่มควบคุม (Controls Summary)

# หน้าจอและเมนูการตั้งค่า (Menu Navigation)

# เอกสารและคู่มือการใช้งาน (Documentation & Manual)
