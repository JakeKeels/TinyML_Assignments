#include "quantModel.h"
#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
const int SAMPLES =  714; // number of samples
const int numSamples = 119;
const int accelerationThreshold =  2.5; // threshold of significant in G's
#define RED 22     
#define BLUE 24     
const int tensor_arena_size = 4 * 1024;
uint8_t tensor_arena[tensor_arena_size];
tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;
const tflite::Model* model = ::tflite::GetModel(g_model);
tflite::AllOpsResolver resolver;
tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, tensor_arena_size, error_reporter);
 TfLiteTensor* input = interpreter.input(0);




float features[SAMPLES];
//Eloquent::ML::Port::Classifier model; //clf is your model instance


void setup() {
  Serial.begin(115200);
  while (!Serial);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  PDM.onReceive(onAudio);
  mic.begin();
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  if (model->version() != TFLITE_SCHEMA_VERSION) {
  TF_LITE_REPORT_ERROR(error_reporter,
      "Model provided is schema version %d not equal "
      "to supported version %d.\n",
      model->version(), TFLITE_SCHEMA_VERSION);
}
interpreter.AllocateTensors();

  TfLiteTensor* input = interpreter.input(0);

}


void loop() {
  if (recordSample()) {
    input->data.f=features;
    long int t1 = millis();
    TfLiteStatus invoke_status = interpreter.Invoke();
    long int t2 = millis();
    
if (invoke_status != kTfLiteOk) {
  TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed\n");
  }
TfLiteTensor* output = interpreter.output(0);
Serial.println(output->data.f[1]);
//Serial.println(sizeof(output->data.f));
if(output->data.f[0]==0){
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
