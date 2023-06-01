#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();


const int AirValue = 3039; //you need to replace this value with Value_1 
const int WaterValue = 1119; //you need to replace this value with Value_2 
int intervals = (AirValue - WaterValue)/3; 
int soilMoistureValue; 
float umidade;
void setup() { 
  Serial.begin(9600);
  Serial.println("Eletronica Analogica");
  matrix.begin(0x70);
  pinMode(4, OUTPUT); // Configura o pino 4 como saída LED AMARELO
  pinMode(15, OUTPUT); // Configura o pino 15 como saída LED  BRANCO
  pinMode(5, OUTPUT); // Configura o pino 5 como saída LED VERDE  
  
} 
void loop() { 

soilMoistureValue = analogRead(13); //put Sensor insert into soil 
umidade = 100 - ((soilMoistureValue - WaterValue) * 100 / (AirValue - WaterValue));
if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals)) 
{ 
      // print a string message
    matrix.print(umidade);
    matrix.writeDisplay();
    delay(500);
    digitalWrite(5, HIGH); // Desliga o LED verde
    digitalWrite(15, HIGH); // Desliga o LED branco
    digitalWrite(4, HIGH); // Liga o LED amarelo

} 
else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue 
< (AirValue - intervals)) 
{
       // print a string message
    matrix.print(umidade);
    matrix.writeDisplay();
    delay(500);
    digitalWrite(5, HIGH); // Desliga o LED verde 
    digitalWrite(4, LOW); // Desliga o LED amarelo
    digitalWrite(15, HIGH); // Liga o LED Branco
} 
else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals)) 
{ 
  
digitalWrite(15, LOW); // Desliga o LED branco
digitalWrite(4, HIGH); // Desliga o LED amarelo
digitalWrite(5, LOW); // Liga o LED Verde
// print a string message
matrix.print(umidade);
matrix.writeDisplay();
delay(500);
} 
} 