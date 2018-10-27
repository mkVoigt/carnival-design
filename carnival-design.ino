#include <Servo.h>

Servo door_servo;
int SERVO_PIN = 11;
int TIMER_PIN = 8;
int ACTION_PIN = 7;
int WAIT_DURATION = 15000; // 15 seconds
bool do_the_thing;
bool timer_set;
bool opened;
unsigned long elapsed_time;
unsigned long start_time;

void open_door();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  elapsed_time = 0;
  do_the_thing = false;
  timer_set = false;
  opened = false;
  door_servo.attach(SERVO_PIN);
  door_servo.write(3);
  Serial.begin(9600);
}

void loop() {
  
  elapsed_time = millis();

  if(!timer_set && digitalRead(TIMER_PIN == HIGH)) {
    start_time = millis();
    timer_set = true;
    Serial.println("= [ START TIMER ] =");
  }
  
  if (!do_the_thing && digitalRead(ACTION_PIN) == HIGH) {
    do_the_thing = true;
    Serial.println("= [ ACTIVATED ] =");
  }

  if (!opened && do_the_thing && (elapsed_time - start_time >= WAIT_DURATION)) {
    Serial.println("= [ OPENING ] =");
    open_door();
    opened = true;
  }
}

void open_door() {
  digitalWrite(LED_BUILTIN, HIGH);
  door_servo.write(90);
  return;
}
