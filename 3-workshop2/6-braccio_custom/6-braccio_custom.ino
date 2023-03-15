
#include <Servo.h>
#include "constants.h"

// Posizioni centrali in gradi
int _jntCenter[6] = { BASE_ROT_CENTER, SHOULDER_CENTER, ELBOW_CENTER, WRIST_CENTER, WRIST_ROT_CENTER, GRIPPER_CENTER };

// Posizioni minime in gradi
int _jntMin[6] = { BASE_ROT_MIN, SHOULDER_MIN, ELBOW_MIN, WRIST_MIN, WRIST_ROT_MIN, GRIPPER_MIN };

// Posizioni massime in gradi
int _jntMax[6] = { BASE_ROT_MAX, SHOULDER_MAX, ELBOW_MAX, WRIST_MAX, WRIST_ROT_MAX, GRIPPER_MAX };

// Posizioni attuali in gradi
int _curPos[6] = { 0 };

// Pin associato a ogni servomotore
int _jntPins[6] = {_BASE_ROT_PIN, _SHOULDER_PIN, _ELBOW_PIN, _WRIST_PIN, _WRIST_ROT_PIN, _GRIPPER_PIN};

bool _stopped = false; // variabile di supporto per il loop

Servo _jnt[6]; // Servomotori

void _softwarePWM(int high_time, int low_time) { // NON MODIFICARE
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

/* Carica le posizioni attuali negli array rispettivi */
void getPos() {
  for (int i = 0; i < 6; i++) {
    _curPos[i] = _jnt[i].read();
  }
}

/* Stampa in seriale le ultime posizioni registrate in gradi o in millisecondi */
void printPos() {
  for (int i = 0; i < 6; i++) {
      Serial.println(_jnt[i].read());
  }
}

/* Riporta il braccio nella posizione di home */
void moveHome(int ms) {
  for (int i = 0; i < 6; i++) {
    moveTo(i, _jntCenter[i], ms);
  }
}

/* Muovi il giunto <jnt> all'angolo <angle>. Velocità: 1 grado ogni <ms>  */
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

  pinMode(SOFT_START_PIN, OUTPUT); // NON MODIFICARE
  digitalWrite(SOFT_START_PIN, LOW);
  _softStart();

  for (int i = 0; i < 6; i++) {
    _jnt[i].write(_jntCenter[i]);
    _jnt[i].attach(_jntPins[i]); // associa ogni servomotore al pin corrispondente
  }

  moveHome(100); // porta il braccio in Home

  Serial.println("Initalization complete.");
}

void loop() {

  if (!_stopped) {
    moveTo(5, GRIPPER_MIN, 50);
    moveTo(5, GRIPPER_MAX, 50);
  }

  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    if (input == "go") { // riparti se fermo
      _stopped = false;
      Serial.println(input);
    }
    else if (input == "home") { // torna a casa
      _stopped = true;
      Serial.println(input);
      moveHome(100);
    }
    else if (input == "1") { // esegui un movimento specifico
      _stopped = true;
      Serial.println(input);
      moveTo(1, 50, 50);
    }
    else if (input == "print") { // stampa le ultime posizioni registrate
      Serial.println(input);
      printPos();
    }
  }
}
