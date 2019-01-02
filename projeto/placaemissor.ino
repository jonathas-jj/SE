#include <DHT_U.h>

//código do emissor
#include <RH_ASK.h>


#include <DHT.h>
 
#define sensorTemp 10
#define led 7
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
 
Adafruit_SSD1306 dsp(-1);//cria o objeto do display para i2c 




RH_ASK driver(2000, 11, 12); // define o transmissor na porta 12 e o receptor na porta 11; velocidade de transmissao 2000 bits/seg.

#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

// Definicoes do sensor : pino e tipo. É uma classe.
DHT dht(sensorTemp, DHTTYPE);


 
void setup() {
  
  Serial.begin(9600); 
 

  DDRD=1<<7;
  // Iniclaiza o sensor DHT
  dht.begin();
  //testa o modulo de  transmissão/recepção
    if (!driver.init()) Serial.println("init failed");


  dsp.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicia o display com endereco padrao
  dsp.clearDisplay();//limpa a tela
 
 
  dsp.setTextColor(WHITE);//define o texto para branco (no display ficara azul)
 
  dsp.setTextSize(1);//define o tamanho do texto
  dsp.println("Sistemas Embarcados");//escreve na tela a mensagem
 
  dsp.setTextSize(3);
  dsp.println("2018");
  dsp.display();//mostra as alteracoes no display, sem isso nao ira mostrar nada!!
  delay(1000);
  dsp.clearDisplay();
}

void loop() {
  
  // Aguarda 2 segundos entre as medicoes
  char  msg[15]; String str;
  PORTD ^=1<<7; // acende e aoaga o led
  delay(2000);
    
  // Leitura da umidade
  float h = dht.readHumidity();
  
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  
   if (isnan(h) || isnan(t))
  {
    //ATENÇÃO: enviar viar mensagem para o receptor
    imprimeNaTela(t,h);
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    
    return;
  }
  imprimeNaTela(t,h);
  //começa a desenhar no OLED
  
  str= String(h)+"/"+String(t);// concatena a temperatura e a humidade, separando-os por uma "/"
  str.toCharArray(msg, 15);//transforma a string num array de char 
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.print("mensagen(temperatura/humidade) "); Serial.println(msg);
  
    
 
}
void imprimeNaTela(float t , float h){
  dsp.clearDisplay();
  
   dsp.setTextColor(WHITE);
   dsp.setTextSize(2);
   String str ="dsa" ;
   dsp.print("Temp:");
   dsp.println(t);
   dsp.setTextSize(1);
   dsp.print("Humidade: ");
   dsp.println(h);
   dsp.setCursor(0, 0);
   dsp.display();//mostra na tela 
  
  }
