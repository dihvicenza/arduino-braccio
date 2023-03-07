#include <Braccio.h>
#include <Servo.h>

/*
Step Delay: a milliseconds delay between the movement of each servo. Allowed values from 10 to 30 msec.
M1=base degrees. Allowed values from 0 to 180 degrees
M2=shoulder degrees. Allowed values from 15 to 165 degrees
M3=elbow degrees. Allowed values from 0 to 180 degrees
M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
*/

Servo base; // M1
Servo shoulder; // M2
Servo elbow; // M3
Servo wrist_ver; // M4
Servo wrist_rot; // M5
Servo gripper; // M6: 10deg - closed; 73deg - open

void setup() {

  Serial.begin(9600);
  Braccio.begin(); // Safety position: 90, 45, 180, 180, 90, 10
  Serial.println("Setup completato.");

  // the arm is aligned upwards and the gripper is closed
  //(step delay, M1, M2, M3, M4, M5, M6);

  // TEST BASE
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 180, 90, 90, 90, 0, 73);
  
  // TEST SHOULDER
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 15, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 165, 90, 90, 0, 73);

  // TEST ELBOW
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 0, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 180, 90, 0, 73);

  // TEST WRIST
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 90, 0, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 90, 180, 0, 73);

  // TEST WRIST ROT
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 180, 73);
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 180, 73);

  // TEST GRIPPER
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 10);
  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);

  // Braccio.ServoMovement(20, 0, 90, 90, 90, 0, 73);
}

void loop() {
}
