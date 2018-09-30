#define led 7
#define botao1 8
#define botao2 9
bool desliga=0;
unsigned int intervalob=100, intervalo=1000 ;
unsigned long int inib=0,inib2=0,inib3=0,ini=0,fim;
int valbot1=0;
int valbot2=0;
int range=0,acende=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(botao1,INPUT);
  pinMode(botao2,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(!desliga){ 
    fim=millis();
    if((fim - ini) >intervalo){
       ini=millis(); 
          digitalWrite(led,acende= !acende);    
     }
 }   
     valbot1=digitalRead(botao1);
     valbot2=digitalRead(botao2); 
     
     if(valbot1==1){
  
        if(millis()-inib > intervalob && intervalo>100){//checa se o valor do botao está ativo por um intervalo de tempo e limita a velocidade máxima do pisca-pisca.(100ms)
          intervalo-=100;
          Serial.println(millis()-inib);// para vizualidar a saida
          valbot1=0;
          inib=millis();
          
          }
         if(millis()-inib < 500 && valbot2==1){//checa se o botao 2 foi pressionado junto apos o botao 1 em menos de 500ms.
          intervalo=1000;
          ini=millis();
          inib=millis();
          desliga=!desliga;
          digitalWrite(led,0); 
          }
        
      }else inib=millis();
      
    if(valbot2==1 ){
  
        if(millis()-inib2 > intervalob ){// checa se o valor do botao está ativo por um intervalo de tempo
          intervalo+=100;     
          Serial.println(millis()-inib2);//verificação
          valbot2=0;
          inib2=millis();
          }
          if(millis()-inib2 < 500 && valbot1==1){  //checa se o botao 1 foi pressionado junto apos o botao 2 em menos de 500ms.
          intervalo=1000;
          ini=millis();
          inib2=millis();
          desliga=!desliga;
          digitalWrite(led,0); 
          }
        
      }else inib2=millis(); 
} 
