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

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up Braccio with calibration values...");

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

  Serial.println("Set up complete.");

  arm.begin(true);  // Start to default vertical position.
}

void loop() {

  openGripper();
  arm.safeDelay(3000);

  closeGripper();
  arm.safeDelay(3000);

  arm.setDelta(BASE_ROT, 1);
  arm.setOneRelative(BASE_ROT, 45);
  arm.safeDelay(3000);
  arm.setOneRelative(BASE_ROT, -90);
  arm.safeDelay(3000);

  // arm.setOneRelative(WRIST, 30);  //Set the Wrist to a position 30 degrees past its current position
  // arm.safeDelay(3000);

  // arm.setOneRelative(WRIST, -30);  //Set the Wrist to a position 30 degrees behind its current position
  // arm.safeDelay(3000, 20);         //Delay for 3000ms while still updating the movement every 20ms

  // arm.setOneAbsolute(ELBOW, arm.getCenter(ELBOW));
  // arm.safeDelay(3000);
}

void openGripper() {
  arm.setOneAbsolute(GRIPPER, GRIPPER_OPENED);
}

void closeGripper() {
  arm.setOneAbsolute(GRIPPER, GRIPPER_CLOSED);
}
