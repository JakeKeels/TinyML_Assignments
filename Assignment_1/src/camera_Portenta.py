#Example script included in IDE.
#Basic script to show camera output.

import sensor, image, time

sensor.reset()                          # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE)  # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)       # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)         # Wait for settings take effect.

while(True):
    img = sensor.snapshot()         # Take a picture and return the image.
