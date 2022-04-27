#include "quantModel.h"
#include <Arduino_LSM9DS1.h>
#include <TensorFlowLite.h>
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "Mic.h"
#define SAMPLES 64
#define GAIN (1.0f/50)
#define SOUND_THRESHOLD 1000

#define RED 22  
#define GREEN 23   
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
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

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
  if (recordAudioSample()) {
    input->data.f=features;
    long int t1 = millis();
    TfLiteStatus invoke_status = interpreter.Invoke();
    long int t2 = millis();
    Serial.println(t1-t2);
if (invoke_status != kTfLiteOk) {
  TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed\n");
  }
TfLiteTensor* output = interpreter.output(0);
Serial.println(output->data.f[1]);
//Serial.println(sizeof(output->data.f));
if(output->data.f[0]==0){
      analogWrite(BLUE, 0);
      analogWrite(RED, 255);
      analogWrite(GREEN, 0);
      Serial.println("Stop");
      }
      else if(output->data.f[0]==1){
      analogWrite(RED, 0);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 255);
      Serial.println("Go");
      }else if(output->data.f[0]==2){
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
