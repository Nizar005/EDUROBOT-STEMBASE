#include <Wire.h>
#include "Adafruit_TCS34725.h"

int ins[20]; // instruction model
int insstep = 0;  //instructions step
float red, green, blue; //sensor value

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);

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
    Serial.print(" ");
  }
  delay(5000);
}

void getsensor(){
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED
}

int compare(){
  if(ranging(red, 210, 230) && ranging(green, 25, 40) && ranging(blue, 25, 40)){
    return (1);
  }
  else if(ranging(red, 70, 90) && ranging(green, 80, 100) && ranging(blue, 60, 80)){
    return (2);
  }
  else if(ranging(red, 80, 100) && ranging(green, 70, 90) && ranging(blue, 60, 80)){
    return (3);
  }
  else{
    return (0);
  }
}

void intoarray(int data){
  if (insstep < 50) {
    ins[insstep] = data;
    insstep++;
  }
}



bool ranging(float in, float max, float min){
  return (in >= max && in <= min);
}
