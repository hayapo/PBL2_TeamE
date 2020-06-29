#include <Wire.h>
#include <ZumoShield.h>
//Git練習
#define REFLECTANCE_THRESHOLD  400
#define ROTATE_DELAY 810
#define INTERSECTION_OSTIM 250
#define MOTOR_SPEED 120
#define TURN_SPEED 120

void setup(){
  Serial.begin(9600);
  button.waitForPress();
}

void loop() {
  delay(1000);
  goStraight();
  //stop();
  doTurn('r');
}

void goStraight(){
  reflectances.update();
  //1と6のセンサが黒を認識するまで直進
  while ((reflectances.value(1) < REFLECTANCE_THRESHOLD) && (reflectances.value(6) < REFLECTANCE_THRESHOLD)) {
    if((reflectances.value(2) > 400) && (reflectances.value(5) < 400)){
      motors.setSpeeds(-70,70);
      reflectances.update();
    }
    else if((reflectances.value(5) > 400) && (reflectances.value(2) < 400)){
      motors.setSpeeds(70,-70);
      reflectances.update();
    }
    else{
      motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
      reflectances.update();
    }
    led.on();
  }
  motors.setSpeeds(MOTOR_SPEED, MOTOR_SPEED);
  delay(INTERSECTION_OSTIM);
  motors.setSpeeds(0,0);
  delay(1000);
  led.off();
}

 void doTurn(char dir){
  reflectances.update();
  if (dir == 'r'){
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(ROTATE_DELAY);
    motors.setSpeeds(0, 0);
  }
  if (dir == 'l'){
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(ROTATE_DELAY);
    motors.setSpeeds(0, 0);
  }
 }

void stop(){
      motors.setSpeeds(0, 0);
      delay(1000);
}

void end(){
  motors.setSpeeds(0, 0);
  buzzer.playOn();
  while(1){
    //LEDをON
    led.on();
    //1秒待機
    delay(1000);
    //LEDをOFF
    led.off();
    delay(1000);
  }
}
