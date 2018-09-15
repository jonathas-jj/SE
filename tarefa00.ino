int led = 7, botao = 8; 
void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(botao,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int i=0;
   i=digitalRead(botao);
   digitalWrite(led,i);
   
  
}
