int LED = D5;    
int buttonPin = D8;   
bool buttonState = 0;      
bool Mode = 0;            

void setup()
{
  pinMode(buttonPin, INPUT);    
  pinMode(LED , OUTPUT);
}

void loop()
{
  if (digitalRead(buttonPin)) 
  {
    if (!buttonState) 
    {
      buttonState = true;
      Mode = !Mode; 
    }
  }
  else buttonState = false;
  digitalWrite(LED , Mode); 
  delay(5);
}
