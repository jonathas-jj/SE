#include <VirtualWire.h>

//tarefa03 - Montei um pequeno esquema - Usando um sensor Piezzo, um rádio emissor ( alguma informação),
//um led e um potenciômetro(para regular a sensibilidade do piezzo) - que percebe vibrações através piezzo, 
//pisca o led  e envia alguma informação.

#define led 7 //pino 7
#define pot A0  //porta analógica potenciômetro
#define sensorPiezzo  A1 //porta analógica sensor piezzo


int valorPot1=0,valorPot2=0,valorPie=0; 
int sensibilidadePiezo=0;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

  vw_set_tx_pin(9); //Define o pino 9 do Arduino como o pino de dados do transmissor
  vw_setup(2000); //define a velocidade de transmissão em bits/sec
  
  //setar os registradores ddr

  
 DDRD|=1<<7;//define led output na porta B canal 7


 ADMUX |= (1<<REFS0 ); //escoolhe a referencia Vcc como a padrão.
 ADCSRA |= 0b10000000;//(1<<ADEN);//habilita a conversão

 DIDR0=0b000011;// GPIO desabilita a entradas digitais dos pinos A0 e A1 para economizar energia;
 

}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Aguarda o envio de dados
}

void loop() {

  ADMUX &= 11111110;// seleciona o canal A0
  ADCSRA |= (1<<ADSC);//começa a conversão
  while(ADCSRA & 1<<ADSC);//n sai do loop Enquanto n terminar a conversão
 
  valorPot1=0;
  valorPot1=ADCL;
  valorPot1=(ADCH<<8)+valorPot1;

  if(valorPot1>(valorPot2+3) || valorPot1<(valorPot2-3)){  // só muda o estado da váriavel quando é o mudadi o valor do potenciômetro.
    valorPot2=valorPot1; 
     sensibilidadePiezo=map (valorPot1,0,1023,5,100);//mapeia o valor retirado do potenciometro pra um numero entre 5 e 70
    Serial.println("valor do potenciometro:");
    Serial.println(sensibilidadePiezo);
  } 
  
  ADMUX |= 00000001;//muda o canal para o A1
  ADCSRA |= (1<<ADSC);//começa a conversão
 
  while(ADCSRA & 1<<ADSC);//n sai do loop Enquanto n terminar a conversão
  valorPie=0;
  valorPie=ADCL;
  valorPie=(ADCH<<8)+valorPie;

  
  
  if(valorPie>sensibilidadePiezo){//configura a sensibilidade do piezzo , tirada do potenciometro.
  
    PORTD|= 1<<7; //GPIO acende o led
    Serial.println(valorPie);
    
    send("Mensagem");
    
    Serial.println("Mensagem enviada");
    
   } 
    
  PORTD &= ~(1<<7);//GPIO apaga o led
  
  //enviar via rádio.
  


}
