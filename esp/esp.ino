#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html_test.h"

#define cong_tac D0
const char* ssid = "hex";
const char* pass = "11111111";
SoftwareSerial s(D5, D6);            // rx, tx  // METAL
LiquidCrystal_I2C lcd(0x27, 16, 2);  // D1 SCL, D2 SDA
ESP8266WebServer server(80);
const int trig1 = D3;
const int echo1 = D4;
const int trig2 = D7;
const int echo2 = D8;

int value;

void setup() {
  pinMode(cong_tac, INPUT_PULLUP);
  Serial.begin(115200);
  lcd.init();
  lcd.setCursor(0, 0);  // cot, hang
  lcd.print("Metal: ");
  lcd.setCursor(0, 1);
  lcd.print("Orther: ");
  s.begin(9600);
  //s2.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Da ket noi wifi");
  Serial.print("IP Address:");
  Serial.println(WiFi.localIP());
  server.on("/", ketnoi);
  server.on("/doc_metal", docdulieu_Metal);
  server.on("/doc_plastic", docdulieu_Plastic);
  server.begin();
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = digitalRead(cong_tac);
  Serial.print("value=");
  Serial.println(value);
  if (value == 0) {
    server.handleClient();
  }
}

void ketnoi() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void docdulieu_Metal() {
  int t = do_metal();
  t = constrain(t, 5, 25);  // gioi han 0 den 22
  t = map(t, 25, 5, 0, 100);

  lcd.setCursor(9, 0);
  lcd.print("   ");
  lcd.setCursor(9, 0);
  lcd.print(t);
  lcd.setCursor(12, 0);
  lcd.print("%");

  s.write(t);  // gui du lieu

  String metal = String(t);
  server.send(200, "text/plain", metal);
}
void docdulieu_Plastic() {
  int t = do_orther();
  t = constrain(t, 5, 25);  // gioi han 0 den 22
  t = map(t, 25, 5, 0, 100);
  lcd.setCursor(9, 1);
  lcd.print("   ");
  lcd.setCursor(9, 1);
  lcd.print(t);
  lcd.setCursor(12, 1);
  lcd.print("%");
  s.write(t);
  String plastic = String(t);
  server.send(200, "text/plain", plastic);
}

int do_metal() {
  unsigned long duration;  // biến đo thời gian
  unsigned int distance;   // biến lưu khoảng cách


  digitalWrite(trig1, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig1, 1);  // phát xung từ chân trig
  delayMicroseconds(5);    // xung có độ dài 5 microSeconds
  digitalWrite(trig1, 0);  // tắt chân trig


  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo1, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);
  Serial.println(distance);

  //s.write(distance);
  delay(100);
  return distance;
}

int do_orther() {
  unsigned long duration;  // biến đo thời gian
  unsigned int distance;   // biến lưu khoảng cách


  digitalWrite(trig2, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig2, 1);  // phát xung từ chân trig
  delayMicroseconds(5);    // xung có độ dài 5 microSeconds
  digitalWrite(trig2, 0);  // tắt chân trig


  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo2, HIGH);
  // Tính khoảng cách đến vật.
  distance = int(duration / 2 / 29.412);
  Serial.println(distance);
  //delay(100);
  //s.write(distance);
  delay(100);
  return distance;
}
