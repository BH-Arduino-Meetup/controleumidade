#include <SPI.h>
#include <Ethernet.h>

int leitura; 
int humidadeSolo = 0;
byte mac[] = { 0xAB, 0xCD, 0x12, 0x34, 0xFF, 0xCA };
EthernetServer server(80);
IPAddress ip(192,168,0,100);         
IPAddress gateway(192,168,0,1);    
IPAddress subnet(255, 255, 255, 0); 

void setup() 
{
  Ethernet.begin(mac, ip, gateway, subnet); 
  Serial.begin(9600);
  server.begin();
  Serial.print(" Servidor ativado em:");
  Serial.println(Ethernet.localIP());
  pinMode(A0,INPUT);
}
void loop()
{
  criaPaginaHTML();
  delay(2000);
}
void criaPaginaHTML()  
{
  leitura = analogRead(A0);
  humidadeSolo = (leitura);
  
  EthernetClient client = server.available();
  if (client)
  {
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");          
          client.println("Connection: close");
          client.println("Refresh: 0");  
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          if(humidadeSolo < 300)  
             client.println("Solo seco");
  
          if((humidadeSolo >= 300) && (humidadeSolo < 700))
             client.println("Relativamente umido");

          if ((humidadeSolo >= 700) && (humidadeSolo < 950))
             client.println("Bem umido");       
          
          client.println("</html>");
          break;
        }
        
        if (c == '\n') 
        {
          currentLineIsBlank = true;
        }else if (c != '\r'){         
          currentLineIsBlank = false;
        }
      }
    }    
    delay(1);    
    client.stop();    
  }
}
