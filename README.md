# mobileDrivingBluetoothControlledRobot

Mobile robot was created on Arduino platform, having 2 motors, double H-brigde and Bluetooth module can be fully controlled by an Android application. Robot has also autonomous mode which utilizes 3 ultrasonic sensors that are installed.
- Every 10ms interruptions from timer1 are called to read data from Bluetooth. Data received from Bluetooth is an array of 5 1-Byte Numbers.
- First number is a start bit and set to 255 from the BT app when the data is being transferred.
- Second is 0, 1 or 2 and sets a driving mode.
- Third to fifth numbers can range from 0 to 250 and are responsibble for direction and speed of motors.
- In the loop section of code requested mode is set and appropriate driving function is started.
