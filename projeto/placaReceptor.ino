// placa que vai receber e comparar os dados vindos ,via rádio, da placa com o receptor 
// Essa placa também conterá um modulo bluetooth que se comunicará com um smartphone enviando informações sobre os dois 
//código do emissor
#include <RH_ASK.h>

#include <DHT_U.h>
#include <DHT.h>

 
#define sensorTemp 10
#define LED 4 //pino 7 = porta E5

RH_ASK driver(2000, 11, 12); // define o transmissor na porta 12 e o receptor na porta 11; velocidade de transmissao 2000 bits/seg.

#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

// Definicoes do sensor : pino e tipo. É uma classe.
DHT dht(sensorTemp, DHTTYPE);

void setup() {
  
  Serial.begin(9600); 
  DDRH=1<<LED;
  // Iniclaiza o sensor DHT (sensor de temperatura e humidade)
  dht.begin();
  //testa o modulo de  transmissão/recepção
    if (!driver.init()) Serial.println("Falha no inicio da recepção RF");
}
float charPraFloat(char *c, int ini, int fim ){
  char aux[fim-ini];int j=0;
  for(int i=ini;i<fim;i++){
       aux[j]=c[i];
       j++;
      }
  return atof(aux);
  }
void loop() {


  // Aguarda 2 segundos entre as medicoes
  PORTH ^=1<<LED;
  delay(2000);
 
  // Leitura da umidade
  float h = dht.readHumidity();
  
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  
   if (isnan(h) || isnan(t))//se nao ler um número
  {
   
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    return;
  }
  float t_emissor,h_emissor;
  char *aux;
  uint8_t buf[11]; //declara um buffer (de tamanhoRH_ASK_MAX_MESSAGE_LEN) para armazenar a mensagem 
  uint8_t buflen = sizeof(buf); //tamanho da mensagem
  uint8_t i; //contador  de caracteres do buffer
  aux=(char*)buf;
  
    if (driver.recv(buf, &buflen)) { // se recebeu uma mensagem
      
      t_emissor= charPraFloat(aux, 6, 10);//corta a mensagem e converte pra float
      h_emissor=charPraFloat(aux, 0, 4);//corta a mensagem e converte pra float
     
     /* if( ((t_emissor-t)> 10.0) ||  ((t_emissor-t) < -10.0) ){
       
        Serial.println("Atenção!");
        Serial.println("Temperaturas dos ambientes incongruentes!");
        
        }
       if( ((h_emissor-h)> 10.0) ||  ((h_emissor-h) < -10.0) ){
       
        Serial.println("Atenção!");
        Serial.println("humidades dos ambientes incongruentes!");
        }*/
         
         
      Serial.print("Temperatura emissor/receptor:"); Serial.print(t_emissor);Serial.print("°C/");Serial.print(t);Serial.println("°C");
      Serial.print("Humidade emissor/receptor:"); Serial.print(h_emissor);Serial.print("%/");Serial.print(h);Serial.println("%");
     
      
    }else{
      Serial.println("Nenhuma Mensagem recebida do trasmissor");
      Serial.print("Temperatura receptor:"); Serial.print(t);Serial.println("°C");
      Serial.print("Humidade receptor:"); Serial.print(h);Serial.println("%");
      }
      
      
    
    
  
}
