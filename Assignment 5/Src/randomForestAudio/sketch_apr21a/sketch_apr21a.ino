#include "Classifier.h"
#include <Arduino_LSM9DS1.h>

const int SAMPLES =  714; // number of samples
const int numSamples = 119;
const int accelerationThreshold =  2.5; // threshold of significant in G's
#define RED 22    
#define GREEN 23    
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
  pinMode(GREEN, OUTPUT);
}


void loop() {
  if (recordAudioSample()) {
    long int t1 = millis();
    int x = model.predict(features); //predict with your new features and print the outcome
    long int t2 = millis();
    Serial.println(t1-t2);
    if(x==0){
      analogWrite(BLUE, 0);
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      Serial.println("Stop");
      }
      else if(x==1){
      analogWrite(RED, 0);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 255);
      Serial.println("Go");
      }else if(x==2){
      analogWrite(RED, 0);
      analogWrite(BLUE, 255);
      analogWrite(GREEN, 0);
      Serial.println("Up");
      }else{
      analogWrite(RED, 255);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 180);  
      Serial.println("Down");
      }
        delay(500);
      //red fistbump, blue wave
  }
}

void onAudio() {
    mic.update();
}

/**
 * Read given number of samples from mic
 */
bool recordAudioSample() {
    if (mic.hasData() && mic.data() > SOUND_THRESHOLD) {

        for (int i = 0; i < SAMPLES; i++) {
            while (!mic.hasData())
                delay(1);

            features[i] = mic.pop() * GAIN;
        }

        return true;
    }

    return false;
}
