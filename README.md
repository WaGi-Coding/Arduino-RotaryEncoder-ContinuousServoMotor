# Arduino-RotaryEncoder-ContinuousServoMotor
Control a Continuous Servo Motor with a Rotary Encoder

Controls:
 - Hold the Button to turn ON/OFF Servo
 - Push the Button while ON to stop the Servo 
 - Turn the Encoder to define speed & direction of the Servo Motor


PS: It's not using servo.write(degrees) but servo.writeMicroseconds(val), so you can trim it better, that it actually will stay still if stopped but not detached, see code config
