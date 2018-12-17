#include <X113647Stepper.h>

// Pinler
// Calisiyor
int step1[]={4,5,6,7};
static const int STEPS_PER_REVOLUTION = 32 * 64;

tardate::X113647Stepper Stepper1(
  STEPS_PER_REVOLUTION,
  4, 5, 6, 7
);

int sumotor1[]={9,10};
int sumotor2[]={11,12};


int ledControl[]={17,18};
int ldr[]={A0,A1};
int ledWarning[]={19,20};

int button[]={2,3};


void setup() {
  // put your setup code here, to run once:
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(sumotor1[i], OUTPUT);
  }
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(sumotor2[i], OUTPUT);
  }
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(button[i], INPUT);
  }
  pinMode(19,OUTPUT);
  Stepper1.setSpeed(4);
}

void runDC(int pin1, int pin2, int runTime){
  // turn on the motor
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  
  //let the motor run
  delay(runTime);
  
  //turn off the motor
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}



void loop() {
  // put your main code here, to run repeatedly:
  
    if(digitalRead(2)==HIGH){
      runDC(sumotor1[0], sumotor1[1], 12000);
      Stepper1.step(7*STEPS_PER_REVOLUTION/10);
      digitalWrite(19,HIGH);
      delay(100);
      Stepper1.step(-7*STEPS_PER_REVOLUTION/10); 
      delay(35000);     
      digitalWrite(19,LOW);
      runDC(sumotor2[0], sumotor2[1], 19000);
      delay(500);
      
}
  if(digitalRead(3)==HIGH){
    
      runDC(sumotor1[0], sumotor1[1], 12000);
      Stepper1.step(-5*STEPS_PER_REVOLUTION/10);
      digitalWrite(19,HIGH);
      delay(100);
      Stepper1.step(5*STEPS_PER_REVOLUTION/10);  
      delay(35000);    
      digitalWrite(19,LOW);
      runDC(sumotor2[0], sumotor2[1], 19000);
      delay(500);
   
  }
}
