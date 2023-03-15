
#include <Servo.h>
#include "constants.h"
#include <string.h>

int _jntCenter[6] = { BASE_ROT_CENTER, SHOULDER_CENTER, ELBOW_CENTER, WRIST_CENTER, WRIST_ROT_CENTER, GRIPPER_CENTER };
int _jntMin[6] = { BASE_ROT_MIN, SHOULDER_MIN, ELBOW_MIN, WRIST_MIN, WRIST_ROT_MIN, GRIPPER_MIN };
int _jntMax[6] = { BASE_ROT_MAX, SHOULDER_MAX, ELBOW_MAX, WRIST_MAX, WRIST_ROT_MAX, GRIPPER_MAX };
int _curPos[6] = { 0 };
int _jntPins[6] = {_BASE_ROT_PIN, _SHOULDER_PIN, _ELBOW_PIN, _WRIST_PIN, _WRIST_ROT_PIN, _GRIPPER_PIN};

bool _stopped = false;

Servo _jnt[6];

int valPot;

void _softwarePWM(int high_time, int low_time) {
  digitalWrite(SOFT_START_PIN, HIGH);
  delayMicroseconds(high_time);
  digitalWrite(SOFT_START_PIN, LOW);
  delayMicroseconds(low_time);
}

void _softStart() { // the Braccio Shield v4 controls voltage levels on startup
  long int tmp = millis();
  while (millis() - tmp < 2000)
    _softwarePWM(80, 450);  //the sum should be 530usec

  while (millis() - tmp < 6000)
    _softwarePWM(75, 430);  //the sum should be 505usec

  digitalWrite(SOFT_START_PIN, HIGH);
}

void getPos() {
  for (int i = 0; i < 6; i++) {
    _curPos[i] = _jnt[i].read();
  }
}

void printPos() {
  for (int i = 0; i < 6; i++) {
    Serial.println(_jnt[i].read());
  }
}

void moveHome(int ms) {
  for (int i = 0; i < 6; i++) {
    moveTo(i, _jntCenter[i], ms);
  }
}

void moveTo(int jnt, int angle, int ms) {

  getPos();

  int c = _curPos[jnt];
  int t = angle;
  int dir = 1;
  if (c > t) {
    dir = -1;
  }
  while (abs(c - t) != 0) {
    c += dir;
    _jnt[jnt].write(c);
    delay(ms);
  }
  _curPos[jnt] = c;
}

void moveAll(int a1, int a2, int a3, int a4, int a5, int a6, int ms) {
  moveTo(0, a1, ms);
  moveTo(1, a2, ms);
  moveTo(2, a3, ms);
  moveTo(3, a4, ms);
  moveTo(4, a5, ms);
  moveTo(5, a6, ms);
}

void closeGripper() {
  moveTo(5, GRIPPER_CLOSED, 50);
}

void openGripper() {
  moveTo(5, GRIPPER_OPENED, 50);
}

void setup() {
  Serial.begin(9600);

  Serial.println("Inizializzazione...");

  pinMode(SOFT_START_PIN, OUTPUT); 
  digitalWrite(SOFT_START_PIN, LOW);
  _softStart();

  pinMode(A0, INPUT);

  for (int i = 0; i < 6; i++) {
    _jnt[i].write(_jntCenter[i]);
    _jnt[i].attach(_jntPins[i]);
  }

  moveHome(50);

  Serial.println("Inizializzazione completata.");
}

void loop() {

  if (!_stopped) {
    moveTo(5, GRIPPER_MIN, 50);
    moveTo(5, GRIPPER_MAX, 50);
  }

  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    if (input == "go") {
      _stopped = true;
      Serial.println(input);

      // 1. Esegui i movimenti desiderati
      // 2. Ritorna a home

    }
    else if (input == "home") {
      _stopped = true;
      Serial.println(input);
      moveHome(50);
    }
    else if (input == "0" | input == "1" | input == "2" | input == "3" | input == "4" | input == "5") {
      _stopped = true;
      Serial.println("Inizio modalità JOG");
      int j = atoi(input.c_str());
      while(1) {
        while (Serial.available()==0){
          valPot = analogRead(A0);
          int angle = map(valPot, 0, 1023, 0, 180);
          moveTo(j, angle, 50);
          Serial.println("Spostato giunto " + String(j) + " a " + String(angle));
          delay(1000);
        }
        String input2 = Serial.readString();
        input2.trim();
        if (input2 == "stop") {
          Serial.println("Termine modalità JOG");
          break;
        }
      }
    }
  }
}

