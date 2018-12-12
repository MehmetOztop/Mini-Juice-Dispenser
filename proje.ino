#include <X113647Stepper.h>

// Pinler

int step1[]={1,2,3,4};
int step2[]={5,6,7,8};
static const int STEPS_PER_REVOLUTION = 32 * 64;

tardate::X113647Stepper Stepper1(
  STEPS_PER_REVOLUTION,
  step1[0], step1[1], step1[2], step1[3]
);

tardate::X113647Stepper Stepper2(
  STEPS_PER_REVOLUTION,
  step2[0], step2[1], step2[2], step2[3]
);

int sumotor1[]={9,10,11};
int sumotor2[]={12,13,14};

int mixer[]={14,15,16};

int ledControl[]={17,18};
int ldr[]={A0,A1};
int ledWarning[]={19,20};

int button[]={21,22};


void setup() {
  // put your setup code here, to run once:
  for (int i = 0 ; i < 3 ; i++)
  {
   pinMode(sumotor1[i], OUTPUT);
  }
  for (int i = 0 ; i < 3 ; i++)
  {
   pinMode(sumotor2[i], OUTPUT);
  }
  for (int i = 0 ; i < 3 ; i++)
  {
   pinMode(mixer[i], OUTPUT);
  }
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(ledControl[i], OUTPUT);
  }
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(ledWarning[i], OUTPUT);
  }
  for (int i = 0 ; i < 2 ; i++)
  {
   pinMode(button[i], INPUT);
  }
}

void runDC(int en, int pin1, int pin2, int runTime){
  // turn on the motor
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  
  // set the speed
  analogWrite(en, 200);
  
  //let the motor run
  delay(runTime);
  
  //turn off the motor
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

bool checkPowder(int btn) {
  if(btn== button[0]){
    digitalWrite(ledControl[0], HIGH);
    delay(500);
    if(analogRead(ldr[0]) < 100){
      digitalWrite(ledWarning[0], LOW);
      return true;
      digitalWrite(ledControl[0], LOW);
    }
    else{
      digitalWrite(ledWarning[0], HIGH);
      return false;
      digitalWrite(ledControl[0], LOW);
      for (int i = 0 ; i < 10 ; i++)
      {
       digitalWrite(ledWarning[0], LOW);
       delay(500);
       digitalWrite(ledWarning[0], HIGH);
      }
    }
  }
  else if(btn== button[1]){
    digitalWrite(ledControl[1], HIGH);
    delay(500);
    if(analogRead(ldr[1]) < 100){
      digitalWrite(ledWarning[1], LOW);
      return true;
      digitalWrite(ledControl[1], LOW);
    }
    else{
      digitalWrite(ledWarning[1], HIGH);
      return false;
      digitalWrite(ledControl[1], LOW);
      for (int i = 0 ; i < 10 ; i++)
      {
       digitalWrite(ledWarning[1], LOW);
       delay(500);
       digitalWrite(ledWarning[1], HIGH);
      }
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button[0])==HIGH){
    if(checkPowder(button[0])){
      runDC(sumotor1[0], sumotor1[1], sumotor1[2], 5000);
      Stepper1.step(STEPS_PER_REVOLUTION);
      delay(5000);      
      Stepper1.step(-STEPS_PER_REVOLUTION);
      runDC(mixer[0], mixer[1], mixer[2], 5000);
      runDC(sumotor2[0], sumotor2[1], sumotor2[2], 5000);
    }   
  }
  else if(digitalRead(button[1])==HIGH){
    if(checkPowder(button[1])){
      runDC(sumotor1[0], sumotor1[1], sumotor1[2], 5000);
      Stepper2.step(STEPS_PER_REVOLUTION);
      delay(5000);      
      Stepper2.step(-STEPS_PER_REVOLUTION);
      runDC(mixer[0], mixer[1], mixer[2], 5000);
      runDC(sumotor2[0], sumotor2[1], sumotor2[2], 5000);
    }   
  }
}
