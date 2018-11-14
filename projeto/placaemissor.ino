//código do emissor
#include <RH_ASK.h>
//#include<String>

#include <DHT_U.h>
#include <DHT.h>
 
#define sensorTemp 10
#define led 7

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
}

void loop() {

  // Aguarda 2 segundos entre as medicoes
  char  msg[15]; String str;
  PORTD ^=1<<7;
  delay(2000);
    
  // Leitura da umidade
  float h = dht.readHumidity();
  
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  
   if (isnan(h) || isnan(t))
  {
    //ATENÇÃO: enviar viar mensagem para o receptor
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    return;
  }
  
  
  str= String(h)+"/"+String(t);// concatena a temperatura e a humidade, separando-os por uma "/"
  str.toCharArray(msg, 15);//transforma a string num array de char 

  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.print("mensagen(temperatura/humidade) "); Serial.println(msg);
 
  
}
