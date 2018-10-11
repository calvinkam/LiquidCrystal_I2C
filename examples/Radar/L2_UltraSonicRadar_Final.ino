#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
const int pingPin = 9;
const int echoPin = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;
double velocity = 0.034;
void setup() {
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(3);
  lcd.init();
  lcd.backlight();
  lcd.init_bargraph(LCDI2C_HORIZONTAL_BAR_GRAPH);
  
}
int totalLen = 16*5;
void loop() {
  for (int i = 0 ; i < 180; i++) {
    myServo.write(i);
    delay(30);
    int dist = getDistance();
    lcd.clear(0);
    lcd.print(dist);
    lcd.print("cm");
    int value = map(dist, 0, 50, 0, totalLen);
    lcd.draw_horizontal_graph(1, 0, totalLen, (byte)value);
  }
  for (int i = 180 ; i >0; i--) {
    myServo.write(i);
    delay(30);
    int dist = getDistance();
    lcd.clear(0);
    lcd.print(dist);
    lcd.print("cm");
    int value = map(dist, 0, 50, 0, totalLen);
    lcd.draw_horizontal_graph(1, 0, totalLen, (byte)value);
  }
}

int getDistance() {
  long duration, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = duration * velocity /2;

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  return cm;
}

