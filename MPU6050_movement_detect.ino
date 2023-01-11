
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
float averageMovement = 0;
float averagePeak = 0;

float satiety = 0;
float deltaTime = 0;
unsigned long ms = 0;
unsigned long lastMs = 0;

void setup(void) {

  
  Serial.begin(115200);

  Serial.print("Raw\tAvg\tPeak\tSatiety");
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Accelerometer global movement demo. v1.0");

  sensorInit();

  Serial.println("");
  delay(100);
  
  
}

void loop() {

  // Time management
  ms = millis();
  deltaTime = (ms - lastMs) / 1000.0;
  lastMs = ms;


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

    // some kind of average value
    averageMovement += (instantMove - averageMovement) * 0.01;

    // Average peak
    averagePeak -= 0.01;
    averagePeak = max(averagePeak, averageMovement);

    // Movement increase satiety
    float satietyIncreaseSpeed = 20;
    satiety += instantMove * satietyIncreaseSpeed * deltaTime;

    // Upper limit of satietey
    satiety = min(1000, satiety);

    // Time decrease satiety
    float satietyDecreaseSpeed = 10; // unités / seconde
    satiety = max(0, satiety - satietyDecreaseSpeed * deltaTime);
    
    // TODO: Handle the satiety levels to trigger things
    

  
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
  Serial.print("instantMove:");
  Serial.print(instantMove);
  Serial.print("\t");
  Serial.print("averageMovement:");
  Serial.print(averageMovement);
  Serial.print("\t");
  Serial.print("averagePeak:");
  Serial.print(averagePeak);
  Serial.print("\t");
  Serial.print("satiety:");
  Serial.print(satiety);
  
  Serial.println();
  //delay(500);
}
