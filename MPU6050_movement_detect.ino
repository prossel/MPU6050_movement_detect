
// Basic demo for accelerometer readings from Adafruit MPU6050
// Use vectors to determine a single global movement value

// Install library "Vector datatype" by RCmag with library manager

// Pierre Rossel 2023-01-11


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <Vector_datatype.h>
#include <vector_type.h>


Adafruit_MPU6050 mpu;

bool mustInit = true;
vec3_t accPrev;
float movement = 0;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Accelerometer global movement demo. v1.0");

  sensorInit();

  Serial.println("");
  delay(100);
  
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  vec3_t acc = { a.acceleration.x, a.acceleration.y, a.acceleration.z };
  float instantMove = 0;

  if (mustInit) {
    accPrev = acc;
    mustInit = false;
  } else {

    vec3_t vChange = acc - accPrev;
    instantMove = vChange.mag();
    movement += (instantMove - movement) * 0.05;
  
    accPrev = acc;
  }
  


  /* Print out the values */
//  Serial.print("Acceleration X: ");
//  Serial.print(a.acceleration.x);
//  Serial.print(", Y: ");
//  Serial.print(a.acceleration.y);
//  Serial.print(", Z: ");
//  Serial.print(a.acceleration.z);
//  Serial.print(" m/s^2");
//  Serial.print("\t");
  Serial.print(instantMove);
  Serial.print("\t");
  Serial.print(movement);
  
  Serial.println();
  //delay(500);
}
