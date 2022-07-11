/*

Control a Continuous Servo Motor with a Rotary Encoder

Controls:
 - Hold the Button to turn ON/OFF Servo
 - Push the Button while ON to stop the Servo 
 - Turn the Encoder to define speed & direction of the Servo Motor


                          Made with ♥ by WaGi-Coding aka. Taki7o7

*/


//-----------------------------------------------------------------------------------------------------
//----------------------------------------- CONFIG ----------------------------------------------------
//-----------------------------------------------------------------------------------------------------

#define outputA 2 //CLK
#define outputB 3 //DT
#define PinSW 4 //Button

 #include "Servo.h"
int servoPin = 9; // Use a Pin supporting PWM~



int trimmedCenter = 1438; // Normally 1500 is center, test with which value your servo stays in place
int minMaxChange = 300; // min/max range eg 1438 - 300 == min, 1438 + 300 == max
int stepSize = 10; // higher is less precise, lower is more precise

//-----------------------------------------------------------------------------------------------------



int aState;
int aLastState;  
Servo myServo = Servo();
void setup()
{ 
  Serial.println("STARTING!");
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  pinMode(PinSW, INPUT_PULLUP);
  
  //myServo.attach(servoPin);
  //myServo.writeMicroseconds(trimmedCenter);
  digitalWrite(LED_BUILTIN, LOW);
  
  //Serial.begin(9600); // begin serial monitor
  
  aLastState = digitalRead(outputA);   
} 

int value = 0;
bool isOn = false;
bool triggered = false;
int lastBtn = 0;
int holdCount = 0;
void loop()
{
  int btn = !digitalRead(PinSW);
  if (!btn) {
    holdCount = 0;
  }
  if (!btn) {
    triggered = true;
  }
  if (btn && btn == lastBtn) {
    holdCount++;

    if(holdCount >= 5000 && triggered){
      triggered = false;
      holdCount = 0;
      if (!isOn) {
        isOn = true;
        digitalWrite(LED_BUILTIN, HIGH);
        value = 0;
        myServo.attach(servoPin);
        myServo.writeMicroseconds(trimmedCenter);
      }
      else {
        myServo.detach();
        digitalWrite(LED_BUILTIN, LOW);
        isOn = false;
      }
    }
  }
  
  if (btn && !lastBtn && isOn) {
    value = 0;
    myServo.attach(servoPin);
    myServo.writeMicroseconds(trimmedCenter);
    delay(250);    
  }
  
  lastBtn = btn;

  if (!btn && isOn) {
    aState = digitalRead(outputA);
    if (aState != aLastState){     
      if (digitalRead(outputB) != aState) { 
        //UP
        value += 10;
        value = constrain(value, minMaxChange * -1, minMaxChange);
        myServo.attach(servoPin);
        myServo.writeMicroseconds(trimmedCenter + value);
      }
      else {
        //DOWN
        value -= 10;
        value = constrain(value, minMaxChange * -1, minMaxChange);
        myServo.attach(servoPin);
        myServo.writeMicroseconds(trimmedCenter + value);
      }
    } 
    aLastState = aState;
  }
}
