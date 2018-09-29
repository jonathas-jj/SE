#define led 7
#define botao1 8
#define botao2 9
bool desliga=0;
unsigned int intervalob=100, intervalo=1000 ;
unsigned long int inib=0,inib2=0,inib3=0,ini=0,fim;
int valbot1=0;
int valbot2=0;
int range=0,acende=1,desligado=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,INPUT);
  pinMode(botao1,OUTPUT);
  pinMode(botao2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(!desliga){ 
    fim=millis();
    if((fim - ini) >intervalo){
       ini=millis();
       if(!desligado){ 
          digitalWrite(led,acende= !acende);
       }
    
     }
 }   
     valbot1=digitalRead(botao1);
     valbot2=digitalRead(botao2); 
     
     if(valbot1==1){
  
        if(millis()-inib > intervalob && intervalo>100){
          intervalo-=100;
          Serial.println(millis()-inib);// para vizualidar a saida
          valbot1=0;
          inib=millis();
          
          }
         if(millis()-inib < 500 && valbot2==1){
          intervalo=1000;
          ini=millis();
          inib=millis();
          desliga=!desliga;
          digitalWrite(led,0); 
          }
        
      }else inib=millis();
      
    if(valbot2==1 ){
  
        if(millis()-inib2 > intervalob ){
          intervalo+=100;
          Serial.println(millis()-inib2);
          valbot2=0;
          inib2=millis();
          }
          if(millis()-inib2 < 500 && valbot1==1){
          intervalo=1000;
          ini=millis();
          inib2=millis();
          desliga=!desliga;
          digitalWrite(led,0); 
          }
        
      }else inib2=millis(); 
} 
