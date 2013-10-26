int button2  = 2;
int val = 0;
int i = 0;

void setup()
{
 Serial.begin(9600);
 Serial.println("Hello World"); 
 pinMode(button2, INPUT);
}
void loop()
{
  val = digitalRead(button2);
  if (val == LOW)
  {
   Serial.println(i); 
   i++;
  }
  
  //delay(100);
}
