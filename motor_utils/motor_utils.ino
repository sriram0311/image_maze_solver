/*motor utilities code for 12V DC motor using L298N driver.
 * Fix the input voltage to the driver at 12V
 * Right motor - IN1 and IN2 ; Left motor IN3 and IN4
 */

#include<math.h>


// connect motor controller pins to Arduino digital pins
// motor one
int enA = 3;
int in1 = 5;
int in2 = 6;
// motor two
int enB = 9;
int in3 = 10;
int in4 = 11;
float rps = 1;                        //calibrate during the competition to ensure accuracy
float circumference = 21.99;  //calibrate

float dist = 0;
int flag = 0;
bool end_flag = false;


void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1,HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 160);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 160);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}

int forward(float dist)
{
  float time;
  time = (dist/(rps*circumference))*1000;
  Serial.println(time);
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  analogWrite(enA, 160);
  analogWrite(enB, 160);
  delay(time);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  return 1;
}

int reverse(float dist)
{
  float time;
  time = (dist/(rps*circumference))*1000;
  Serial.println(time);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 160);
  analogWrite(enB, 160);
  delay(time);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
}

int pivot_right()
{
  
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enA, 160);
  analogWrite(enB, 160);
  delay(850);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  return 1;
}

int pivot_left()
{
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  analogWrite(enA, 160);
  analogWrite(enB, 160);
  delay(850);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  return 1;
}

int u_turn()
{
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  analogWrite(enA, 160);
  analogWrite(enB, 160);
  delay(1700);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  return 1;
}

int stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  
  return 1;
}





void loop()
{
  Serial.flush();
  switch(Serial.read())
  {
  case '1':
      Serial.println("forward");
      flag = forward(32);
      if(flag==1)
      break;
  case '2':
      Serial.println("right");
      flag = pivot_right();
      if(flag==1)
      break;
   case '3':
       Serial.println("left");
       flag = pivot_left();
       if(flag==1)
       break;
   case '0':
        Serial.println("Stop");
        flag = stop();
        if(flag==1)
        break;
    case '7':
         Serial.println("u_turn");
         flag = u_turn();
         if(flag==1)
          break;
    default:
        Serial.println("unkown input");
        
  }
  delay(1000);
}
