/*****************************************************************
Fusee a l'eau EspaceLab 
Author    : Julio-Cesar Torres 
Date      : 20 november 2015 
Objective : Control water rocket parachute and write parameters 
            read by sensors (temperature, humidity, altitude, 
            pression). 

Servo parts inspired by:  
    Sweep
    by BARRAGAN <http://barraganstudio.com> 
    This example code is in the public domain.

    
*****************************************************************/
//1. Include libraries 
#include <Servo.h>

//2. Definitions 
#define PIN_LED_ACTV  2 
#define PIN_SERVO     9 
#define PIN_LM35      A0 

#define LM_FAT_MULT   0.09765625

//3. Global variable definitions 
//Servo variables
Servo myServo; 
int posServo = 0; 

//Temperature variable - LM35
float temp; 

//Barometric variables - BMP085
float pressure = 0.0f;
float altitude = 0.0f; 

//Accelerometer variables
int free_fall  = 0; 

void setup(){
  //4. MController / sensors / pins / modules initialization 
  Serial.begin(9600); 
  analogReference(INTERNAL); 
  
  //Pins
  pinMode(PIN_LED_ACTV, OUTPUT); 
  pinMode(PIN_SERVO,    OUTPUT); 
  pinMode(PIN_LM35,     INPUT); 
  
  // Servo init
  myServo.attach(PIN_SERVO); 
  
  // 
  Serial.flush(); 
}

void loop(){
  //5. Measure
  temp = getTempLM35C(PIN_LM35);
  Serial.print("Temperature lue: ");
  Serial.print(temp); 
  Serial.println(" C");
  temp = getTempLM35F(PIN_LM35); 
  Serial.print("Temperature lue: "); 
  Serial.print(temp); 
  Serial.println(" F"); 
  
  //6. Send information 

  //write register. 
  openParachute();
  
  //7. Sleep mode 
  cleanup(); 
  delay(1000);  
}

void cleanup(){
  temp = 0.0f;
}


/*
  Uses a servo motor to open the parachute lock and deploy it. 
  Depends on : Servo motor
*/
void openParachute(){
  delay(5000);                                      //utiliser le t de y=0.5gt*t 
  for(posServo=0; posServo < 180; posServo += 90){  //goes from 0 to 180 degrees in steps of 90 degrees
    myServo.write(posServo);                        //tells servo to go to position pos 
    delay(5000);                                    //waits 5 sec for the servo to reach position ???  15ms... 
  }
}

/*
  Reads sensor LM35 attached in pin <addr> and returns the 
  temperature in celsius degrees. 
  Depends on : Sensor LM35 
*/
float getTempLM35C(byte addr){
  return toCelsius(analogRead(addr)); 
}

/*
  Converts the voltage read in the sensors terminals into 
  temperature in celsius degrees. 
  Depends on : Sensor LM35 
*/
float toCelsius(int voltage){
  return voltage * LM_FAT_MULT; 
}

/*
  Reads the sensor attached to pin <addr> and returns the 
  temperature in fahrenheit degrees. 
  Depends on : Sensor LM35 
*/
float getTempLM35F(byte addr){
  return ((getTempLM35C(addr) * 1.8) + 32); 
}


