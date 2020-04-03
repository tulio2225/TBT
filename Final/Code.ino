#define ma1 3 //กำหนด Pin motorA เดินหน้า
#define ma2 4 //กำหนด Pin motorA ถอยหลัง
#define mb1 5 //กำหนด Pin motorB เดินหน้า
#define mb2 6 //กำหนด Pin motorB ถอยหลัง

#define sensorL 10 //sensor ซ้าย
#define sensorR 11 //sensor ขวา
#define sensorB 12 //sensor หลัง
#define sensorC A0 //sensor สี

#define RED 1
#define YELLOW 2
#define BLACK 3
#define NOCOLOR 0
#define maxSpd 255    // motor max speed

#include <NewPing.h>

#define TRIG_PIN 7
#define ECHO_PIN 8
#define MAX_DISTANCE 200
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

#define sw1 9

int ledState = 10;

int sw_1 = 0;
int old_sw1 = 0;
int state = 0;

int color = 0;
int getColor() {
  int NO_color = analogRead(sensorC);           //อ่านค่า sensor สี ที่ต่อกับ TCRT5000
  if ((NO_color > 2200) && (NO_color < 2500)) //สีแดง
    return RED;
  else if ((NO_color > 1900) && (NO_color < 2200)) //สีเหลือง
    return YELLOW;
  else if ((NO_color > 3600) && (NO_color < 3900)) //สีดำ
    return BLACK;
  else                                        //ไม่พบสี
    return NOCOLOR;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorL, INPUT);
  pinMode(sensorR, INPUT);
  pinMode(sensorB, INPUT);
  pinMode(sensorC, INPUT);
  pinMode(sw1, INPUT);
  pinMode(ledState, OUTPUT);
  pinMode(ma1, OUTPUT);
  pinMode(ma2, OUTPUT);
  pinMode(mb1, OUTPUT);
  pinMode(mb2, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  color = getColor();
  sw_1 = digitalRead(sw1);
  if ( (sw_1 == HIGH) && (old_sw1 == LOW))
  {
    state = !state;
  }
  old_sw1 = sw_1;
  if (state == 1) // state = 1 กลยุทธ์รุก
  {
    digitalWrite(ledState, HIGH);
    if ((sonar.ping_cm() > 10) && ((digitalRead(sensorL) == HIGH) || (digitalRead(sensorR) == HIGH))) // เดินหน้าเมื่อ ultrasonic ด้านหน้าและ sensor ด้านข้าง ไม่เจอสิ่งกีดขวาง
    {
      moveAhead(175);
    }

    if ((sonar.ping_cm() < 10) && ((digitalRead(sensorL) == HIGH) || (digitalRead(sensorR) == HIGH))) // break เมื่อ ultrasonic ด้านหน้าเจอ แต่ sensor ด้านข้างและด้านล่างไมเจอสิ่งกีดขวาง
    {
      aBreak();
      bBreak();
    }

    if ((sonar.ping_cm() < 10) && ((digitalRead(sensorL) == LOW) || (digitalRead(sensorR) == LOW))) // เดินถอยหลัง 2 วิ เมื่อเจอสิ่งกีดขวางด้านหน้าและข้างซ้ายขวา
    {
      moveBack(100);
      delay(2000);
    }

    if (color == RED) // เดินกลับรถ เมื่อ sensor ด้านล่างตรวจจับเส้นสีแดงได้
    {
      uTurn(200);
      delay(1500);
    }

    if (color == YELLOW) // รถหยุด เมื่อ sensor ด้านล่างตรวจจับเส้นสีเหลืองได้
    {
      aStop();
      bStop();
    }
  }
  else if (state == 0) // state = 0 กลยุทธ์รับ
  {
    digitalWrite (ledState, LOW);
    if ((sonar.ping_cm() > 5) && ((digitalRead(sensorL) == HIGH) || (digitalRead(sensorR) == HIGH))) // เดินหน้าเมื่อ sensor ด้านหลัง ด้านข้าง ไม่ทำงาน
    {
      moveAhead(175);
    }

    if ((sonar.ping_cm() < 5) && ((digitalRead(sensorL) == HIGH) || (digitalRead(sensorR) == HIGH))) // กลับรถเมื่อ ultrasonic เจอสิ่งกีดขวาง
    {
      uTurn(200);
      delay(1500);
    }

    if ((digitalRead(sensorL) == LOW) || (digitalRead(sensorR) == LOW)) // เบรค เมื่อ sensor ด้านข้างซ้ายหรือขวาทำงาน
    {
      aBreak();
      bBreak();
    }
  }
  delay(20);
}

void moveAhead(int spd)
{
  analogWrite(ma1, spd);
  digitalWrite(ma2, LOW);
  analogWrite(mb1, spd);
  digitalWrite(mb2, LOW);
}

void moveBack(int spd)
{
  analogWrite(ma1, LOW);
  digitalWrite(ma2, spd);
  analogWrite(mb1, LOW);
  digitalWrite(mb2, spd);
}

void uTurn(int spd)
{
  analogWrite(ma1, spd);
  digitalWrite(ma2, LOW);
  analogWrite(mb1, LOW);
  digitalWrite(mb2, spd);
}

void aStop()
{
  digitalWrite(ma1, LOW);   // motor stop
  digitalWrite(ma2, LOW);
}

void aBreak()
{
  digitalWrite(ma1, HIGH);   // motor break
  digitalWrite(ma2, HIGH);
}

void bStop()
{
  digitalWrite(mb1, LOW);   // motor stop
  digitalWrite(mb2, LOW);
}

void bBreak()
{
  digitalWrite(mb1, HIGH);   // motor break
  digitalWrite(mb2, HIGH);
}

void aForward(int speed)
{
  analogWrite(ma1, speed);
  digitalWrite(ma2, LOW);

}

void bForward(int speed)
{
  digitalWrite(mb2, LOW);
  analogWrite(mb1, speed);
}
