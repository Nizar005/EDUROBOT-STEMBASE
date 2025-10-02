#include <Wire.h>
#include "Adafruit_TCS34725.h"


int ins[20]; // instruction model
int insstep = 0;  //instructions step
float red, green, blue; //sensor value

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  //pb
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  //motor
  pinMode(16, OUTPUT); //motor in1-motor1
  pinMode(17, OUTPUT); //motor in2-motor1
  pinMode(18, OUTPUT); //motor in3-motor2
  pinMode(19, OUTPUT); //motor in4-motor2

  //start tcs sensor and confirm
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } 
  // if tcs failed, stop
  else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); 
  }
}


void loop() {
  if(digitalRead(13) == 0){
    scan();
  }
  else if(digitalRead(14) == 0){
    for(int i = 0; i < 20; i++){
      int x = ins[i];
      if(x == 1){
        analogWrite(16, 100);
        analogWrite(17, 0);
        analogWrite(18, 100);
        analogWrite(19, 0);
        delay(2000);
      }
      else if(x == 2){
        analogWrite(16, 100);
        analogWrite(17, 0);
        analogWrite(18, 0);
        analogWrite(19, 0);
        delay(1000);
      }
      else if(x == 3){
        analogWrite(16, 0);
        analogWrite(17, 0);
        analogWrite(18, 100);
        analogWrite(19, 0);
        delay(1000);
      }
      else if(x == 0){
       analogWrite(16, 0);
       analogWrite(17, 0);
       analogWrite(18, 0);
       analogWrite(19, 0);
       break;
      }
    }
  }
}


void scan(){
  getsensor();
  delay(100);
  intoarray(compare());
  //Serial.println(red);
  //Serial.println(green);
  //Serial.println(blue);
  //Serial.println("");
  //Serial.println(compare());
  //Serial.println("");
  for (int i = 0; i < 20; i++) {
    Serial.print(ins[i]);
    Serial.print("");
  }
  Serial.println("");
  delay(500);
}

void getsensor(){
  tcs.setInterrupt(false);  // turn on LED
  delay(60);  // takes 50ms to read
  tcs.getRGB(&red, &green, &blue);
  tcs.setInterrupt(true);  // turn off LED
}

int compare(){
  if(ranging(red, 89, 119) && ranging(green, 72, 102) && ranging(blue, 58, 88)){ //blue
    return (1);
  }
  else if(ranging(red, 136, 166) && ranging(green, 47, 77) && ranging(blue, 39, 79)){ //red
    return (2);
  }
  else if(ranging(red, 124, 154) && ranging(green, 63, 93) && ranging(blue, 31, 61)){ // yellow
    return (3);
  }
  else{
    return (0);
  }
}

void intoarray(int data){
  if (insstep < 20) {
    ins[insstep] = data;
    insstep++;
  }
}

bool ranging(float in, float min, float max){
  return (in >= min && in <= max);
}
