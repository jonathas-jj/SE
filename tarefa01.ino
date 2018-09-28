#define led 7
#define botao1 8
#define botao2 9
unsigned int intervalo=1000;
int valbot1=0;
int valbot2=0;
int range=0,acende=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(led,INPUT);
  pinMode(botao1,OUTPUT);
  pinMode(botao2,OUTPUT);

}
void aceleraOuDesacelera(){
  range=0;
  valbot1=digitalRead(botao1);
  valbot2=digitalRead(botao2);

   while((valbot1==0 &&  valbot2==1)&&(valbot1==1 &&  valbot2==0) &&(range<500)){
      valbot1=digitalRead(botao1);
      valbot2=digitalRead(botao2);
      range++;
      delay(1);
    }

   if(valbot1==1 && valbot2==1){
     acende=!acende;
     intervalo=1000;
  }
  else if(valbot1==1 && intervalo>100){
    
       intervalo=intervalo-100;
       
    }
   else if( valbot2==1){
      intervalo=intervalo+100;     
    } 
  
  }
void loop() {
    
    digitalWrite(led,acende);
    delay(intervalo);
    aceleraOuDesacelera();
    
    digitalWrite(led,0);
    delay(intervalo);
    aceleraOuDesacelera();

  
 
   


      // put your main code here, to run repeatedly:
}
