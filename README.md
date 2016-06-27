<h2> Controle de umidade utilizando o Blynk e Arduíno </h2>

Este projeto é o candidato vencedor para ser construído durante o Meetup do dia 25/06/2016. Basicamente a ideia é ter duas hastes medindo o valor de resistividade si, quanto menos umidade, menor o valor da saída do sensor. Seguindo as idéias deste <a href="http://seeedstudio.com/wiki/Grove_-_Moisture_Sensor">link</a> e deste <a href="http://pt.slideshare.net/saibhaskar/design-development-of-water-monitoring-systems-by-using-arduino-and-sensors">link</a> resolvemos separar os níveis de umidade em 3:
<ul>
	<li>Sensor no solo seco - Quando o sensor capta valores analógicos de 0 a 300, ou de 0 a 33%</li>
	<li>Sensor no solo úmido - Quando o sensor capta valores analógicos de 300 a 700, ou entre 33% e 66%</li>
	<li>Sensor em água - Quando o sensor capta valores analógicos de 700 a 950 ou 66% até 100%</li>
</ul>
Para apenas captar a umidade, o sistema precisa apenas de um arduíno, e um conjunto de dois sensores que são encontrados na internet com o <a href="https://www.google.com.br/#q=sensor+de+umidade+higr%C3%B4metro">nome de Higrômetro</a>.  O esquema é super tranquilo de montar, e segue abaixo:

<img class="alignnone size-full wp-image-3169" src="https://cezarantsouza.files.wordpress.com/2016/06/esquema-umidade-solo.jpg" alt="esquema-umidade-solo" width="640" height="510" />

Neste esquema, estamos utilizando a entrada analógica do Arduíno A0. O cabo preto recebe o valor de GND e o vermelho o valor de 5v. A haste não possui polaridade, então não há risco. O código para ler a entrada analógica também é bastante simples:

```javascript
int leitura;
int humidadeSolo = 0;

void setup()
{
Serial.begin(9600);
pinMode(A0,INPUT);
}

void loop()
{
leitura = analogRead(A0);
humidadeSolo = (leitura);

if(humidadeSolo < 300) 
   Serial.println(" Solo bem umido"); 

if((humidadeSolo >= 300) && (humidadeSolo < 700)) 
  Serial.println(" Relativamente umido"); 

if((humidadeSolo >= 700) && (humidadeSolo < 1024))
  Serial.println(" Solo seco");
}
```

<h2>Blynk</h2>
O próximo passo é adicionarmos o Blynk ao projeto. Após instalar no seu smartphone, crie um projeto.

<img class=" size-full wp-image-3198 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/1.png" alt="1" width="540" height="960" />

No ato de criação do projeto, aproveite para enviar para o seu email o valor da autenticação, você vai precisar dele mais tarde. Basta clicar no botão "email"

<img class=" size-full wp-image-3203 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/2.png" alt="2" width="540" height="960" />

Logo após, adicione um componente Push ao seu projeto.

<img class=" size-full wp-image-3206 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/3.png" alt="3" width="540" height="960" />

E depois adicione um Display  LCD. Irá lhe custar 400 créditos no programa, caso não tenha você irá precisar mostrar o resultado de outra forma.

<img class=" size-full wp-image-3211 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/4.png" alt="4" width="540" height="960" />

A única configuração que eu recomendo realizar no push, é colocá-lo com alta prioridade.

<img class=" size-full wp-image-3215 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/5.png" alt="5" width="540" height="960" />

No display, eu recomendo colocar o PIN como V1 e marcar como Advanced.

<img class=" size-full wp-image-3218 aligncenter" src="https://cezarantsouza.files.wordpress.com/2016/06/6.png" alt="6" width="540" height="960" />

Ok, agora basta você baixar a Library do<a href="https://github.com/blynkkk/blynk-library"> Blynk no Github </a>, adicionar o arquivo zip na sua IDE e inserir o código abaixo.

```javascript
#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
#include <SimpleTimer.h>

int leitura;
int humidadeSolo = 0;
SimpleTimer timer;
WidgetLCD lcd(V1);
char auth[] = &quot;suaChaveDeAuthAqui&quot;;

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
   Serial.println(" Solo bem umido"); 

if((humidadeSolo >= 300) && (humidadeSolo < 700)) 
  Serial.println(" Relativamente umido"); 

if((humidadeSolo >= 700) && (humidadeSolo < 1024))
  Serial.println(" Solo seco");
  
}

void loop()
{
Blynk.run();
timer.run();
}
```
[Link](https://www.youtube.com/embed/vsYdiL4_l8c) do sensor funcionando na prática.
