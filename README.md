# Smart Parking Gate System
ระบบจำลองไม้กั้นอัตโนมัติและนับจำนวนรถเข้า-ออกลาน    จอดรถ โดยนำเทคโนโลยีอิเล็กทรอนิกส์และไมโครคอนโทรลเลอร์มาประยุกต์ใช้ในการตรวจจับรถ คำนวณพื้นที่ว่าง จัดการเปิด-ปิดไม้กั้น แสดงผลสถานะ และเพิ่มฟังก์ชันความสะดวกและความปลอดภัย เพื่อให้ผู้ใช้งานสามารถทราบสถานะที่จอดรถได้ทันที และช่วยให้การบริหารจัดการลานจอดรถมีประสิทธิภาพยิ่งขึ้น
# ฟีเจอร์หลัก (Features)
- การตรวจจับยานพาหนะ (Vehicle Detection): ใช้เซนเซอร์วัดระยะทางด้วยคลื่นเสียง (Ultrasonic Sensor) ตรวจจับรถยนต์ทั้งฝั่งขาเข้า (Entry) 
- การควบคุมทางเข้า (Barrier Control): ใช้มอเตอร์เซอร์โว (Servo Motor) ในการสั่งเปิด-ปิดไม้กั้นเมื่อมีรถผ่าน
- การคำนวณและแสดงผลช่องจอด (Occupancy & Display): คำนวณจำนวนรถและพื้นที่ว่างคงเหลือแบบ Real-time พร้อมแสดงผลผ่านหน้าจอ OLED
# Block Diagram

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

# การต่อสาย (Pin Configuration)

# การต่อวงจร (Circuit Diagram)

# Software & Libraries
Libraries มี
Adafruit SSD1306
ezButton
ESP32Servo

# คู่มือและขั้นตอนการใช้งาน (How to Use & Quick Start)

# หน้าที่ของปุ่มควบคุม (Controls Summary)

# หน้าจอและเมนูการตั้งค่า (Menu Navigation)

# เอกสารและคู่มือการใช้งาน (Documentation & Manual)
