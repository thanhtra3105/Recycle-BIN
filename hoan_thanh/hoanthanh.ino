#include <Servo.h>

Servo s1, s2;
#define trig 2
#define echo 3
#define metal_PIN_1 4
#define metal_PIN_2 5
#define metal_PIN_3 6
#define metal_PIN_4 7
#define metal_PIN_5 10
#define servo_PIN_1 8  // servo cua
#define servo_PIN_2 9  // servo phan loai
#define cong_tac 11
int value;
void setup() {
  Serial.begin(9600);
  s1.attach(servo_PIN_1);
  s2.attach(servo_PIN_2);
  pinMode(cong_tac, INPUT_PULLUP);
  pinMode(metal_PIN_1, INPUT);
  pinMode(metal_PIN_2, INPUT);
  pinMode(metal_PIN_3, INPUT);
  pinMode(metal_PIN_4, INPUT);
  pinMode(metal_PIN_5, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  s1.write(55);
  delay(100);
  s2.write(95);
  delay(100);
}

void loop() {
  value = digitalRead(cong_tac);
  if (value == 0) {
    if (do_KC() <= 40) {
      s1.write(130);
      delay(2000);
      s1.write(52);
      if (check_metal() == 0)  // co kim loai
      {
        s2.write(30);
        delay(1000);

      } else {
        s2.write(160);
        delay(1000);
      }
      s2.write(95);  // cho servo phan loai quay ve vi tri can bang

    }

    else {
      s1.write(52);
    }

    // 55
  }
}

unsigned int do_KC() {
  unsigned long duration;  // biến đo thời gian
  unsigned int distance;   // biến lưu khoảng cách


  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig


  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);


  Serial.print(distance);
  Serial.println("cm");
  delay(50);
  return distance;

  /* Serial.print("Check:");
  Serial.println(check_metal());
  delay(100); */
}

int check_metal() {
  int metal_value_1 = digitalRead(metal_PIN_1);
  int metal_value_2 = digitalRead(metal_PIN_2);
  int metal_value_3 = digitalRead(metal_PIN_3);
  int metal_value_4 = digitalRead(metal_PIN_4);
  int metal_value_5 = digitalRead(metal_PIN_5);
  //Serial.println(metal_value1);  // co kim loai:0
  // Serial.println(metal_value2);
  return metal_value_1 & metal_value_2 & metal_value_3 & metal_value_4 & metal_value_5;
}
