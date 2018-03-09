# image_maze_solver
An autonomous bot using arduino for motor control and raspberry pi and a usb camera to solve a 3d maze using image processing.


How does it work?
  This is an autonomous bot to solve a 3d maze using image processing. I implemented this on a differential drive robot with a USB camera, raspberry pi and arduino. The raspberry pi processes the image and transmits the data serially to arduino which controls the motor.
  
Requirements :
  1. Raspberry pi
  2. Arduino
  3. Functioning differential drive robot.

How to use:
  Upload the motor utils code to the arduino, this listens to the raspberry pi serially and controlls the motor according to the switch case. Necessary comments are added in the arduino file to understand the code. Alter the motor pins if necessary. Refer tutorials on differential drives for problems in this.
  
  The camera utils code is to be uploaded on the raspberry pi. Preparing the raspberry pi is of utmost importance.
  Further instructions will be uploaded in the future.
   
