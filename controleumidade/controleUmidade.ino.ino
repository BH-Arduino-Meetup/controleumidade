#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>

int leitura; 
int humidadeSolo = 0;
SimpleTimer timer;
WidgetLCD lcd(V1);
char auth[] = "suaChaveDeAuthAqui";

void setup()
{
  Serial.begin(9600);  
  pinMode(A0,INPUT);
  Blynk.begin(auth);
  timer.setInterval(2000L, myTimerEvent);
}
void myTimerEvent()
{ 
  lcd.clear();
  leitura = analogRead(A0);
  humidadeSolo = (leitura / 4);
    
  if(humidadeSolo < 300) 
   Serial.println(" Solo seco"); 

if((humidadeSolo >= 300) && (humidadeSolo < 700)) 
  Serial.println(" Relativamente umido"); 

if((humidadeSolo >= 700) && (humidadeSolo < 950))
  Serial.println(" Bem umido");
   
}
void loop()
{
  Blynk.run();         
  timer.run();
}
