
int led = 22;           // the PWM pin the LED is attached to
float brightness = 0;   // how bright the LED is
int degrees = 0;        //Integer for going through loop

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 22 to be output
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  //Resets loop if counter goes past a full circle
  if(++degrees > 365){
      degrees = 0;
    }
  //Converts degrees to radians, then into the sin wave.
  brightness = sin(radians(degrees));
  //Adds one to get positive value, then multiplies by half max LED brightness, since value is from 0-2.
  brightness = (brightness +1)*127.5;
  //Changes LED, then waits 20ms
  analogWrite(led, brightness);
  delay(20);
}
