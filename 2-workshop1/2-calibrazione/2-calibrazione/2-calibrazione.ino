/*
 Braccio_Calibration.ino - version 0.2
 Written by Lukas Severinghaus. Adapted by Gabriele Sha - Digital Innovation Hub Vicenza.
 
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

 /*
  SETUP: 
 - Serial monitor con baud rate 9600
 - Impostare "no line endings"
 - Copia i valori salvati
*/

#include "BraccioV2.h"
Braccio arm;

#define GRIPPER_CLOSED 85
#define GRIPPER_OPENED 20
#define UPDATE_TIME 2000

void setup() {
  Serial.begin(9600);
  Serial.print("Inizializzazione... ");

  arm.setJointCenter(WRIST_ROT, 90);//Wrist rotation joint should be parallel to rest of the arm
  arm.setJointCenter(WRIST, 90);
  arm.setJointCenter(ELBOW, 90);
  arm.setJointCenter(SHOULDER, 90);
  arm.setJointCenter(BASE_ROT, 90);//Base should be pointing at 0° mark on base platform
  arm.setJointCenter(GRIPPER, 50);//Rough center of gripper, default opening position

  // MIN e MAX di default sono: 0 e 180
  // Tranne il GRIPPER:
  arm.setJointMax(GRIPPER, 100); // Gripper closed
  arm.setJointMin(GRIPPER, 15); // Gripper open

  arm.begin(true); // richiede circa 8 secondi

  Serial.println("COMPLETATA");
  Serial.println("\nComandi: \n'c' -> modifica l'angolo di riferimento (change);\n's' -> conferma l'angolo attuale (set) e passa al prossimo");
  
  calibrateJoint(BASE_ROT, "BASE_ROT", arm);
  calibrateJoint(SHOULDER, "SHOULDER", arm);
  calibrateJoint(ELBOW, "ELBOW", arm);
  calibrateJoint(WRIST, "WRIST", arm);
  calibrateJoint(WRIST_ROT, "WRIST_ROT", arm);
  calibrateJoint(GRIPPER, "GRIPPER", arm);
  
  Serial.println("\nCALIBRAZIONE COMPLETATA\n");
}

void loop() {

}

void calibrateJoint(int joint, String joint_name, Braccio _arm){
  
  Serial.print("\nStai calibrando: ");
  Serial.println(joint_name);

  int centered_pos, min_pos, max_pos, currentPosition;

  if(joint != GRIPPER){
    Serial.println("\nCalibrazione CENTER");
    _arm.setOneAbsolute(joint, 90);
    _arm.safeDelay(UPDATE_TIME);
    bool centered = false;
    currentPosition = 90;

    while(!centered){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (CENTER)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if (c == 'c') {
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      } else if(c == 's') {
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        centered = true;
      } else {
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    centered_pos = currentPosition;

    Serial.println("\nCalibrazione MIN");
    _arm.setOneAbsolute(joint, 0);
    _arm.safeDelay(UPDATE_TIME);
    currentPosition = 0;
    bool minSet = false;
    while(!minSet){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (MIN)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if(c == 'c'){
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      }else if(c == 's'){
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        minSet = true;
      }else{
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    min_pos = currentPosition;


    Serial.println("\nCalibrazione MAX");
    _arm.setOneAbsolute(joint, 180);
    _arm.safeDelay(UPDATE_TIME);
    _arm.safeDelay(UPDATE_TIME);
    currentPosition = 180;
    bool maxSet = false;
    while(!maxSet){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (MAX)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if(c == 'c'){
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      }else if(c == 's'){
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        maxSet = true;
      }else{
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    max_pos = currentPosition;

    Serial.println("\n***Valori confermati. Salvali a parte***");
    Serial.print("Giunto: "); Serial.println(joint_name);
    Serial.print("CENTER: "); Serial.println(centered_pos);
    Serial.print("MIN: "); Serial.println(min_pos);
    Serial.print("MAX: "); Serial.println(max_pos);
    
    _arm.setOneAbsolute(joint, centered_pos);
    _arm.safeDelay(UPDATE_TIME);

  } else {

    // Calibrazione del GRIPPER
    Serial.println("\nCalibrazione CENTER");
    _arm.setOneAbsolute(joint, 40);
    _arm.safeDelay(UPDATE_TIME);
    bool centered = false;
    currentPosition = 40;

    while(!centered){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (CENTER)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if(c == 'c'){
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      }else if(c == 's'){
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        centered = true;
      }else{
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    centered_pos = currentPosition;


    Serial.println("\nCalibrazione MIN");
    _arm.setOneAbsolute(joint, 15);
    _arm.safeDelay(UPDATE_TIME);
    currentPosition = 15;
    bool minSet = false;
    while(!minSet){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (MIN)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if(c == 'c'){
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      } else if(c == 's'){
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        minSet = true;
      } else {
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    min_pos = currentPosition;


    Serial.println("\nCalibrazione MAX");
    _arm.setOneAbsolute(joint, 80);
    _arm.safeDelay(UPDATE_TIME);
    currentPosition = 80;
    bool maxSet = false;
    while(!maxSet){
      Serial.print("Posizione attuale: ");
      Serial.println(currentPosition);
      Serial.println("Scrivi c### per modificare la posizione, s per confermare la posizione (MAX)");
      while(Serial.available() < 1);
      char c = Serial.read();
      if(c == 'c'){
        currentPosition = Serial.parseInt();
        _arm.setOneAbsolute(joint, currentPosition);
        _arm.safeDelay(UPDATE_TIME);
      }else if(c == 's'){
        Serial.print("Salvato l'angolo: "); Serial.print(currentPosition); Serial.println(".");
        maxSet = true;
      }else{
        Serial.print("Input non riconosciuto. Riprova.");
      }
    }
    max_pos = currentPosition;

    Serial.println("\n***Valori confermati. Salvali a parte***");
    Serial.print("Tool: "); Serial.println(joint_name);
    Serial.print("CENTER: "); Serial.println(centered_pos);
    Serial.print("MIN: "); Serial.println(min_pos);
    Serial.print("MAX: "); Serial.println(max_pos);
  }
}
