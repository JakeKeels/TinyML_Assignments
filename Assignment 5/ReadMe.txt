The assignment was accomplished by taking the completed models from previous assignments, the random forest models, then saving them as header files for the arduino to read.
The tensorflow models were more difficult, the original models were pruned using lowDensityPrune to remove 80% of nodes from the model, then the models were quantized.
This reduces the size of the models significantly and allows for the models to be run efficiently and quickly. 
The models only took 5ms to run on average.
The LEDs were used to show the output of the models. For the fistbump vs wave, it was red or blue.
For the audio data, red, blue, green and orange were used. This was all based off of the tensorflow, sklearn, and tflite libraries.