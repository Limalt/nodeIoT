// Limalt.io
// EmonLib setup Arduino Nano AtMega 328
// Send data from serial- to ESP8266-Module
// Autor: Euler Alves
// Aug 2015 v.1.0.1

#include "EmonLib.h"
                  
EnergyMonitor currentAC;  //  Instance 

unsigned long timeReg;
#define timeSend 30000
unsigned long comparador = 0;
int kwhora = 0;
float potseg = 0;
int counter = 0;
float consumo = 0;

void setup()
{ 
  Serial.begin(9600);
  
//Current: input pin, calibration.
   currentAC.current(A0, 14.48);
//---------------------------------------------------            
}
  
void loop()
{
//Calculates: Power (Irms * Vac) and adjusted offset
  float Irms = (currentAC.calcIrms(1480)-0.065); 
    float pot = Irms*119.5;
//----------------------------------------------------  
  
// It checks that the value per second of Power
   potseg += pot / 3600.0;

//----------------------------------------------------
//Consume= estimated monetary value (R$) and power (Watts) 
   if (potseg >= 1) {          
       potseg = potseg - 1.000;
        counter ++;      
   } 
   if ( counter >= 1000)  {
       counter = counter - 1000.00;
        kwhora++;
   }
    if (kwhora >= 1){
//Calculates monetary factor and taxes
        consumo = kwhora * 0.69651852 ; 
      // Serial.println(consumo); //Verificação
    }
//-----------------------------------------------------   
// Adjust "Delay" for one second (delay + exec)
       timeReg = millis();
       //Serial.println(timeReg);
//------------------------------------------------------
     
//Tread - execute "timeSend" set to send 
//would be port for the ESP module8266 (nodeMCU firmware)
       if ( millis()- comparador >= timeSend){
              Serial.println (Irms);
              comparador = millis();
        } 
//------------------------------------------------------        
// seconde adjust for 1Watt                 
      delay(752.3);  
//------------------------------------------------------
}

