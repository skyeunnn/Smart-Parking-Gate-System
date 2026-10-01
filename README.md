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
| Servo Motor | GPIO 23 | Signal |
| Green LED | GPIO 13 | ต่อผ่านตัวต้านทาน 330Ω |
| Red LED | GPIO 12 | ต่อผ่านตัวต้านทาน 330Ω |
| ปุ่มฉุกเฉินเปิดไม้กั้น | GPIO 4 | |
| ปุ่มเคลียร์รถออกจากลาน | GPIO 14 | |
# การต่อวงจร (Circuit Diagram)

# Software & Libraries
- `Adafruit SSD1306`
- `ezButton`
- `ESP32Servo`

# คู่มือและขั้นตอนการใช้งาน (How to Use & Quick Start)
(การใช้งานใดใด ไบท์ใส่)
หน้าที่ของปุ่มควบคุม (Controls Summary)
- ปุ่มที่1 : สำหรับกดเปิดไม้กั้นฉุกเฉินหากไม้กั้นทำงานผิดปกติ
- ปุ่มที่2 : สำหรับกดเคลียร์รถออกจากลาน(แบบจำลอง) เมื่อมีรถที่ต้องการออกจากลาน
  
# โครงสร้างและการออกแบบ🚘
<img width="1414" height="2000" alt="image" src="https://github.com/user-attachments/assets/95bf450d-9382-442f-abc2-be4b6a711761" />

# หน้าจอแสดงผลบนOLED

# วิดีโอสาธิตการทำงาน (Video Demonstration)

# เอกสารและคู่มือการใช้งาน (Documentation & Manual)
1. สถานะการทำงานปกติ
- ไม้กั้น จะอยู่ในตำแหน่ง ปิดลงมาที่ 90 องศา
- ไฟแสดงสถานะ LDE สีเขียวติด เพื่อให้รู้ว่ามีที่จอดรถ
- หน้าจอ OLED จะแสดงข้อความ PARKING SYSTEM , จำนวณที่จอดรถว่าง Available: 6/6 ,สถานะ Status: WELCOME และแสดงระยะเวลาค้างของไม้กั้น Hold Time

2. เมื่อมีรถเข้ามาจอด
- เมื่อมีรถวิ่งเข้ามา ตัวเซนเซอร์จะตรวจจับรถที่เข้ามาในระยะ 4-10ซม
- ระบบไม้กั้นจะทำงานอัตโนมัติ ยกไม้กั้นขึ้นไปที่ 0 องศา ระบบจะทำการนับเพิ่มจำนวณรถที่ผ่านเข้ามา +1 คัน และจะไปอัปเดตที่หน้าจอ OLED
- เมื่อรถขับผ่านไปไม้กั้นจะค้าง ตามเวลาที่ตั้งไว้ 1-10 วินาที เมื่อครบ 1-10 วินาทีแล้วก็จะทำการปิดลงมาอัตโนมัติที่ 90 องศา

3. เมื่อที่รถจอดครบตามจำนวนสูงสุด 6 คัน
- ไฟ LED สีแดงจะติด และไฟเขียวจะดับ
- หน้าจอ OLED จะเปลี่ยนข้อความแสดงสถานะเป็น Status: FULL
- เมื่อมีรถคันใหม่ขับเข้ามาหน้าเซนเซอร์ Ultrasonic ไม่กั้นก็จะไม่เปิดยกขึ้นให้ จนกว่าจะมีที่จอดว่าง

4. เมื่อมีรถขับออกจากลานจอดรถ
- กดปุ่ม BTN2 เพื่อเคลียร์รถขาออก 1 ครั้ง
- จำนวนรถสะสมจะลดลง -1 หน้าจอ OLED จะอัปเดตคืนจำนวนช่องจอดว่าง และเปลี่ยนไฟเตือนกลับเป็น LED สีเขียว

5. โหมดฉุกเฉิน ควบคุมด้วย BTN1
- เมื่อไม้กั้นไม่ทำงาน ให้กดปุ่ม BTN1 1 ครั้ง
- ระบบจะสั่ง เปิดไม้กั้นค้างไว้ที่ 0 องศาตลอดเวลา
- หน้าจอ OLED จะขึ้นข้อความเตือนตัวใหญ่ว่า EMERGENCY และ BARRIER FORCED OPEN
- ระบบเซนเซอร์ตรวจจับรถจะหยุดทำงานชั่วคราวเพื่อความปลอดภัย
- การเลิกใช้งานโหมดฉุกเฉิน: กดปุ่ม BTN1 ซ้ำอีก 1 ครั้ง ไม้กั้นจะหมุนปิดกลับลงมาที่ 90 องศา และระบบจะกลับเข้าสู่โหมดการทำงานปกติอัตโนมัติ
