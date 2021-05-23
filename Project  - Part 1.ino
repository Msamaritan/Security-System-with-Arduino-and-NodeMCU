#include<Servo.h>
Servo servomotor;
int Position;
int irStatus;

void setup()
{
  servomotor.attach(3);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  pinMode(7,INPUT);
  
}

void loop()
{
  irStatus = digitalRead(7);
  
  if(digitalRead(7)==0){
  for(Position=0;Position<=90;Position++){
  servomotor.write(Position);
  delay(15);
  }
  }
    delay(1000);

    if(digitalRead(7)==0){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN,LOW);
    }
}
