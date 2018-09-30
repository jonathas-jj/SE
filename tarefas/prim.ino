int botao = 9; int led=7;
void setup() {
  // put your setup code here, to run once:
  
  pinMode(led,OUTPUT);
  pinMode(botao,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   int apertado=digitalRead(botao); 
   
   delay(100);
   digitalWrite(led,1);
   delay(100);
   digitalWrite(led,0);

  if(apertado) { digitalWrite(led,apertado);for(;;){apertado=digitalRead(botao); if(apertado)break;}}

  
  //delay(100);
}
