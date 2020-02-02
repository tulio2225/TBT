#define LED D4   
#define buttonPin D5   
bool buttonState = 0;      
bool Mode = 0;            

void setup()
{
  pinMode(buttonPin, INPUT);    
  pinMode(LED , OUTPUT);
}

void loop()
{
  bool sw = digitalRead(buttonPin);
  if (sw == 1) 
  {
    if (buttonState == 0) 
    {
      Mode = !Mode;
      buttonState = 1; 
    }
  }
  else buttonState = false;
  digitalWrite(LED , Mode); 
  delay(5);
}
