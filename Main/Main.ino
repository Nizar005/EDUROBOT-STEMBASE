#include <Wire.h>
#include "Adafruit_TCS34725.h"


int ins[20]; // instruction model
int insstep = 0;  //instructions step
float red, green, blue; //sensor value

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);

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
  if(digitalRead(14) == 0){
    getsensor();
    delay(100);
    intoarray(compare());
    Serial.println(red);
    Serial.println(green);
    Serial.println(blue);
    Serial.println("");
    Serial.println(compare());
    Serial.println("");
    for (int i = 0; i < 20; i++) {
      Serial.print(ins[i]);
      Serial.println("");
    }
    Serial.println("");
    delay(500);
  }
}

void getsensor(){
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED
}

int compare(){
  if(ranging(red, 52, 82) && ranging(green, 100, 130) && ranging(blue, 73, 103)){
    return (1);
  }
  else if(ranging(red, 196, 226) && ranging(green, 26, 56) && ranging(blue, 27, 57)){
    return (2);
  }
  else if(ranging(red, 163, 193) && ranging(green, 43, 73) && ranging(blue, 36, 66)){
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
