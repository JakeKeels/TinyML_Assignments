#include "Classifier.h"
#include <Arduino_LSM9DS1.h>

const int SAMPLES =  714; // number of samples
const int numSamples = 119;
const int accelerationThreshold =  2.5; // threshold of significant in G's
#define RED 22     
#define BLUE 24     

float features[SAMPLES];
Eloquent::ML::Port::Classifier model; //clf is your model instance


void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
}


void loop() {
  if (recordSample()) {
    int x = model.predict(features); //predict with your new features and print the outcome
    if(x==0){
      analogWrite(BLUE, 0);
      analogWrite(RED, 255);
      Serial.println("Fistbump");
      }
      else{
      analogWrite(RED, 0);
      analogWrite(BLUE, 255);
      Serial.println("Wave");
        }
        delay(500);
      //red fistbump, blue wave
  }
}

int samplesRead = numSamples;
 
bool recordSample() {
  float aX, aY, aZ, gX, gY, gZ;

  // wait for significant motion
  while (samplesRead == numSamples) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(aX, aY, aZ);

      // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
    }
  }
  while (samplesRead < numSamples) {
    int offset = 6*samplesRead;
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      features[offset] = aX;
      features[offset+1] = aY;
      features[offset+2] = aZ;
      features[offset+3] = gX;
      features[offset+4] = gY;
      features[offset+5] = gZ;
      //Serial.println(offset);
      
      samplesRead++;
      
    }
  }
}
