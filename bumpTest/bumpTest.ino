int ledPin = 7;
int bumperPin = 2;
int speakerPin = 11;
int val = 0;
int iVal =0;

void setup()
{
 pinMode(ledPin, OUTPUT);
 pinMode(speakerPin, OUTPUT);
 pinMode(bumperPin, INPUT); 
 Serial.begin(9600);
}

void loop()
{
  val = digitalRead(bumperPin);
  if(val == LOW)
  {
   digitalWrite(ledPin, HIGH);
   tone(speakerPin, 440);
  } 
  else
  {
   digitalWrite(ledPin, LOW);
   noTone(speakerPin); 
  }
  Serial.println(val);
  //delay(1000);
  
}
