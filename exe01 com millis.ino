
int botao=8, led=7;
unsigned int intervalo=1000;
unsigned int antMillis=0;
int valor=0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(botao, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  
  if(millis() - antMillis >= intervalo){
    antMillis=millis();
    if(valor){valor=0;digitalWrite(led,valor);}
    else {valor=1;digitalWrite(led,valor);}
    }
  if(digitalRead(botao)){digitalWrite(led,1); for(;;);}
  
  
  /*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second*/
  
}
