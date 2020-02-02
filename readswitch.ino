#define LED_BUILTIN D4
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(5,INPUT);
  //Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  bool sw = digitalRead(5);
  //Serial.println(sw);
  if(sw == 1){
    digitalWrite(LED_BUILTIN,1);
  }
  else{
    digitalWrite(LED_BUILTIN,0);
  }
}

