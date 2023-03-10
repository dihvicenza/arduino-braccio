
#include <Servo.h>
#include "constants.h"




// Array


// Definizione funzioni










int _jntCenter[6] = { BASE_ROT_CENTER, SHOULDER_CENTER, ELBOW_CENTER, WRIST_CENTER, WRIST_ROT_CENTER, GRIPPER_CENTER };
int _jntCenterMs[6] = {BASE_ROT_CENTER_MS, SHOULDER_CENTER_MS, ELBOW_CENTER_MS, WRIST_CENTER_MS, WRIST_ROT_CENTER_MS, GRIPPER_CENTER_MS};
int _jntMin[6] = { BASE_ROT_MIN, SHOULDER_MIN, ELBOW_MIN, WRIST_MIN, WRIST_ROT_MIN, GRIPPER_MIN };
int _jntMax[6] = { BASE_ROT_MAX, SHOULDER_MAX, ELBOW_MAX, WRIST_MAX, WRIST_ROT_MAX, GRIPPER_MAX };
int _curPos[6] = { 0 };
int _curPosMs[6] = { 0 };
int _jntPins[6] = {_BASE_ROT_PIN, _SHOULDER_PIN, _ELBOW_PIN, _WRIST_PIN, _WRIST_ROT_PIN, _GRIPPER_PIN};

bool _stopped = false;

Servo _jnt[6];

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
    _curPosMs[i] = _jnt[i].readMicroseconds();
  }
}

void printPos(String option="ms") {
  for (int i = 0; i < 6; i++) {
    if (option == "deg") {
      Serial.println(_jnt[i].read());
    }
    else {
      Serial.println(_jnt[i].readMicroseconds());
    }
  }
}

void moveHome(int ms) {

  // 1. Scrivere una funzione per riportare i motori alle posizioni centrali

}

void moveTo(int jnt, int angle, int ms) {

  getPos(); // leggi le posizioni attuali

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

void setup() {
  Serial.begin(9600);

  Serial.println("Initializing...");

  pinMode(SOFT_START_PIN, OUTPUT); // with soft start
  digitalWrite(SOFT_START_PIN, LOW);
  _softStart();

  for (int i = 0; i < 6; i++) {
    _jnt[i].write(_jntCenter[i]);
    _jnt[i].attach(_jntPins[i]);
  }

  moveHome(100);

  Serial.println("Initalization complete.");
}

void loop() {

  if (!_stopped) {
    moveTo(5, GRIPPER_MIN, 50);
    moveTo(5, GRIPPER_MAX, 50);
  }

  // 2. Gestire comandi di input da seriale: home, go, attivazione di un movimento

}
