# manual watering

We want to be able to monitor all sensor values in real time but also be able to manually start the watering process on pots we decide it is needed. For this, we have connected our arduino leonardo to raspberry pi with usb cable and we are going to implement serial communication with commands for all of the stuff needed. Generally we'll try to reuse as much code as possible, but here are some changes we have introduced:
  
  - we have one more file which will store all functions related to drawing text and imgs on the LCD
  
  - we have variables for raw sensor measurements
  
  - since we are not watering at certain percent to certain percent anymore, we need new way for measuring the volume of water supplied - we are going to use seconds