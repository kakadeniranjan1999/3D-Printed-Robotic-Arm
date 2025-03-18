#include<Servo.h>
#define record_button 10
#define play_button 11
#define reset_button 12

int pot_1=A0;
int pot_2=A1;
int pot_3=A2;
int pot_4=A3;

int pos;
int motor_position;
int angles[8];
int flag=0;

int pot_1_val;
int pot_2_val;
int pot_3_val;
int pot_4_val;

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;

//Servo servo[4]={Servo1,Servo2,Servo3,Servo4};

//1=90,2=0,3=90,4=??
//check which side 0 (direction)
//if load on any motor then rearrange the position of motor supply

void setup() {
  Serial.begin(9600);
  pinMode(record_button,INPUT_PULLUP);
  pinMode(play_button,INPUT_PULLUP);
  pinMode(reset_button,INPUT_PULLUP);
  pinMode(pot_1,INPUT);
  pinMode(pot_2,INPUT);
  pinMode(pot_3,INPUT);
  pinMode(pot_4,INPUT);
  Servo1.attach(2);
  Servo2.attach(3);
  Servo3.attach(4);
  Servo4.attach(5);
  Servo5.attach(6);
}

void loop() {
  
//  if(flag!=2)
//  {
//    pot_1_val= analogRead(pot_1);
//    pot_1_val= map(pot_1_val, 0, 1023, 0, 180);
//    Servo1.write(pot_1_val);
//  
//    pot_2_val= analogRead(pot_2);
//    pot_2_val= map(pot_2_val, 0, 1023, 0, 180);
//    Servo2.write(pot_2_val);
//  
//    pot_3_val= analogRead(pot_3);
//    pot_3_val= map(pot_3_val, 0, 1023, 0, 180);
//    Servo3.write(pot_3_val);
//  
//    pot_4_val= analogRead(pot_4);
//    pot_4_val= map(pot_4_val, 0, 1023, 0, 180);
//    Servo4.write(pot_4_val);
//  }
  
  pot_1_val= analogRead(pot_1);
  pot_1_val= map(pot_1_val, 0, 1023, 0, 180);
  //Servo1.write(pot_1_val);
  rotate(Servo1,Servo1.read(),pot_1_val);

  pot_2_val= analogRead(pot_2);
  pot_2_val= map(pot_2_val, 0, 1023, 0, 180);
  //Servo2.write(pot_2_val);
  rotate(Servo2,Servo2.read(),pot_2_val);

  pot_3_val= analogRead(pot_3);
  pot_3_val= map(pot_3_val, 0, 1023, 0, 180);
  //Servo3.write(pot_3_val);
  rotate(Servo3,Servo3.read(),pot_3_val);

  pot_4_val= analogRead(pot_4);
  pot_4_val= map(pot_4_val, 0, 1023, 0, 180);
  //Servo4.write(pot_4_val);
  rotate(Servo4,Servo4.read(),pot_4_val);

  if(flag==0 && digitalRead(record_button)==1 && digitalRead(play_button)==0)
  {
    angles[0]=record(Servo1);
    angles[1]=record(Servo2);
    angles[2]=record(Servo3);
    angles[3]=record(Servo4);
    Serial.println("Initial Position Recorded");
    flag=1;
  }
  else if(flag==1 && digitalRead(record_button)==1 && digitalRead(play_button)==0)
  {
    angles[4]=record(Servo1);
    angles[5]=record(Servo2);
    angles[6]=record(Servo3);
    angles[7]=record(Servo4);
    Serial.println("Final Position Recorded");
    flag=2;
  }
  else if( flag==2 && digitalRead(record_button)==0 && digitalRead(play_button)==1)
  {
    Serial.println("Initiating Cycle...");
    delay(15);
    Serial.println("Moving to Home Position");
    rotate(Servo2,Servo2.read(),80);
    rotate(Servo3,Servo3.read(),70);
    rotate(Servo4,Servo4.read(),0);
    rotate(Servo1,Servo1.read(),90);
    Serial.println("Moving to Initial Position");
    rotate(Servo1,90,angles[0]);
    rotate(Servo3,70,angles[2]);
    rotate(Servo4,0,angles[3]);
    rotate(Servo2,80,angles[1]);
    Serial.println("Moving to Final Position");
    rotate(Servo2,angles[1],80);
    rotate(Servo1,angles[0],angles[4]);
    rotate(Servo3,angles[2],angles[6]);
    rotate(Servo4,angles[3],angles[7]);
    rotate(Servo2,80,angles[5]);
    Serial.println("Task Completed");
  }
  else if(digitalRead(reset_button)==1 && digitalRead(record_button)==0 && digitalRead(play_button)==0)
  {
    flag=0;
  }

}

int record(Servo measure)
{
  return measure.read();
}

void rotate(Servo motor,int current_angle,int req_angle)
{
  if(req_angle>current_angle)
  {
    for (pos =current_angle ; pos <= req_angle; pos += 1) 
    { 
      motor.write(pos);
      delay(15); 
    }
  }
  
  else if(req_angle<current_angle)
  {
    for (pos = current_angle; pos >= req_angle; pos -= 1)
    {
      motor.write(pos);          
      delay(15);
    }
  }
}
