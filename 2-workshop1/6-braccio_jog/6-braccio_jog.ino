/*
 Written by Gabriele Sha @ Digital Innovation Hub Vicenza

 Code derived from: 

 Basic_Movement.ino - version 0.1 written by Lukas Severinghaus
 under GNU license.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <BraccioV2.h>
#include "constants.h"

Braccio arm;

int valPot1;
int valPot2;

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up Braccio with calibration values...");

  pinMode(13, OUTPUT); // LED
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  arm.setJointCenter(BASE_ROT, BASE_ROT_CENTER);
  arm.setJointMin(BASE_ROT, BASE_ROT_MIN);
  arm.setJointMax(BASE_ROT, BASE_ROT_MAX);

  arm.setJointCenter(SHOULDER, SHOULDER_CENTER);
  arm.setJointMin(SHOULDER, SHOULDER_MIN);
  arm.setJointMax(SHOULDER, SHOULDER_MAX);

  arm.setJointCenter(ELBOW, ELBOW_CENTER);
  arm.setJointMin(ELBOW, ELBOW_MIN);
  arm.setJointMax(ELBOW, ELBOW_MAX);

  arm.setJointCenter(WRIST, WRIST_CENTER);
  arm.setJointMin(WRIST, WRIST_MIN);
  arm.setJointMax(WRIST, WRIST_MAX);

  arm.setJointCenter(WRIST_ROT, WRIST_ROT_CENTER);
  arm.setJointMin(WRIST_ROT, WRIST_ROT_MIN);
  arm.setJointMax(WRIST_ROT, WRIST_ROT_MAX);

  arm.setJointCenter(GRIPPER, GRIPPER_CENTER);
  arm.setJointMin(GRIPPER, GRIPPER_MIN);
  arm.setJointMax(GRIPPER, GRIPPER_MAX);

  arm.begin(true);

  Serial.println("Set up complete.");
}

void blink() {
  digitalWrite(13, HIGH);   
  delay(1000);              
  digitalWrite(13, LOW);   
  delay(1000);             
}

void moving() {
  Serial.println("Starting movement");
  for (int i = 0; i < 3; i++) {
    blink();
  }            
  digitalWrite(13, HIGH);   
  delay(1000);
}

void stopped() {
  digitalWrite(13, LOW);  
  delay(1000); 
}

void loop() {

  valPot1 = analogRead(A0);
  valPot2 = analogRead(A1);
  Serial.println("Pot 1: " + String(valPot1) + " Pot2: " + String(valPot2));
  int angle1 = map(valPot1, 0, 1023, 0, 180);
  int angle2 = map(valPot2, 0, 1023, 0, 180);
  Serial.println("Angolo base: " + String(angle1) + " Angolo gomito: " + String(angle2));
  arm.setOneAbsolute(BASE_ROT, angle1);
  arm.safeDelay(1000);
  arm.setOneAbsolute(ELBOW, angle2);
  arm.safeDelay(1000);
}

void openGripper() {
  arm.setOneAbsolute(GRIPPER, GRIPPER_OPENED);
}

void closeGripper() {
  arm.setOneAbsolute(GRIPPER, GRIPPER_CLOSED);
}
