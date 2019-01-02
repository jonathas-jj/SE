    // placa que vai receber e comparar os dados vindos ,via rádio, da placa com o receptor 
// Essa placa também conterá um modulo bluetooth que se comunicará com um smartphone enviando informações sobre os dois 
//código do emissor

#include <stdio.h>

//biblioteca toone
 #define piezoPin 3 

 
//biblioteca display
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Definição de transmissão
#define BAUD (F_CPU/16/9600-1)

//biblioteca radiohead
#include <RH_ASK.h>

//biblioteca sensor de temperatura
#include <DHT_U.h>
#include <DHT.h>
 
#define sensorTemp 10
#define LED 4 //pino 7 = porta E5

RH_ASK driver(2000, 11, 12); // define o transmissor na porta 12 e o receptor na porta 11; velocidade de transmissao 2000 bits/seg.

#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

// Definicoes do sensor : pino e tipo. É uma classe.
DHT dht(sensorTemp, DHTTYPE);

// declarações e definições pro display

#define OLED_MOSI  38
#define OLED_CLK   40
#define OLED_DC    34
#define OLED_CS    32
#define OLED_RESET 36

Adafruit_SSD1306 dsp(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// buffer de recebimento de rádio

uint8_t buflen = 11 ; //tamanho da mensagem
int enviados=0; // dados enviados
uint8_t buf[11]; //declara um buffer (de tamanhoRH_ASK_MAX_MESSAGE_LEN) para armazenar a mensagem 
String msg;    
int tamanhoMsg; 


void setup() {
  
  Serial.begin(9600); 
  // aloca dinamicamente a mensagem
 
  enviados=0;
  cli();
  UBRR0H = BAUD >> 8;
  UBRR0L = BAUD;
  /* Enable transmitter */
   UCSR0A = 0;
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
  UCSR0C |= (1<<UCSZ01) | (1 <<UCSZ00);
  UCSR0B |= (1<<RXCIE0) |
  (1<<TXCIE0) ;
  
  sei();
  

  
  DDRH=1<<LED;
  // Iniclaiza o sensor DHT (sensor de temperatura e humidade)
  dht.begin();
  //testa o modulo de  transmissão/recepção
    if (!driver.init()); //Serial.println("Falha no inicio da recepção RF");

  dsp.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicia o display com endereco padrao
  dsp.clearDisplay();//limpa a tela
 
 
  dsp.setTextColor(WHITE);//define o texto para branco (no display ficara azul)
 
  dsp.setTextSize(1);//define o tamanho do texto
  dsp.println("Sistemas Embarcados");//escreve na tela a mensagem
 
  dsp.setTextSize(3);
  dsp.println("2018");
  dsp.display();//mostra as alteracoes no display, sem isso nao ira mostrar nada!!
  //delay(1000);
  dsp.clearDisplay();
   msg="";
  tamanhoMsg=0;
  
}




  
void loop() {
  
  
  // Aguarda 2 segundos entre as medicoes
  PORTH ^=1<<LED;
  delay(2000);
  
  
  tamanhoMsg=0;
  // Leitura da umidade
  float h = dht.readHumidity();
  
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();
  
   if (isnan(h) || isnan(t))//se nao ler um número
  {
    
   // Serial.println("Falha ao ler dados do sensor DHT !!!");
    imprimeNaTela(0,0);
    return;
  }
  imprimeNaTela(t,h);
  
  float t_emissor,h_emissor;
  
  
  uint8_t i; //contador  de caracteres do buffer
  


  if (driver.recv(buf, &buflen)) { // se recebeu uma mensagem
       
     
         
         tamanhoMsg=msg.length();  
       
        t_emissor= charPraFloat((char *)buf, 6, 10);//corta a mensagem e converte pra float
        h_emissor=charPraFloat((char *)buf, 0, 4);//corta a mensagem e converte pra float

        if((t-t_emissor)>5 || ((t-t_emissor)< -5)){
          encheMensagem(t,h,2);
          tone(piezoPin, 220, 200);
        }else{
           encheMensagem(t,h,1);
        }
        UDR0=msg[0];
         
        
    
     
      
    }else{
       encheMensagem(t,h,0);
       tamanhoMsg=msg.length();  
       UDR0=msg[0];
         
    
      
      }
      
      
 
  
}


//Enche mensagem a ser enviada via bluetooth
void encheMensagem(float temperatura, float humidade, int flag){
   if(flag==2) {
       msg="ATENÇÃO! DISCREPANCIA ENTRE AS MEDIDAS DE TEMPERATURA \n";
       msg+=" Temperatura emissor/receptor: "+String(charPraFloat((char *) buf, 6, 10 ),DEC)+" / "+String(temperatura,DEC) + "\n";
       msg=msg + " Humidade emissor/receptor: "+String(charPraFloat((char *) buf, 0, 4 ),DEC)+" / "+String(humidade,DEC) + "\n";
    }else if(flag==1){
      
     msg=" Temperatura emissor/receptor: "+String(charPraFloat((char *) buf, 6, 10 ),DEC)+" / "+String(temperatura,DEC) + "\n";
     msg=msg + " Humidade emissor/receptor: "+String(charPraFloat((char *) buf, 0, 4 ),DEC)+" / "+String(humidade,DEC) + "\n";
    }else if(flag==0){
      msg="Nenhuma Mensagem recebida do trasmissor\nTemperatura receptor:"+String(temperatura,DEC)+" Humidade receptor:"+String(humidade,DEC)+"\n";
      }
  
  }

 //decodifica mensagem recebida via rádio. 
float charPraFloat(char *c, int ini, int fim ){
  char aux[fim-ini];int j=0;
  for(int i=ini;i<fim;i++){
       aux[j]=c[i];
       j++;
      }
  return atof(aux);
  }


ISR (USART0_TX_vect) {
   enviados++;
   if(enviados>=tamanhoMsg){enviados=0;return;}
    UDR0 = msg[enviados];
            
    
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
