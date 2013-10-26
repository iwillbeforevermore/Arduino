int Trig_pin = 10;
int Echo_pin = 13;
int speaker11 = 11;
long duration;

void setup()
{
 Serial.begin(9600);
 Serial.println("Hello World");

 pinMode(Trig_pin, OUTPUT);
 pinMode(Echo_pin, INPUT); 
 pinMode(speaker11, OUTPUT);
}

void loop()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);
  
  playTone(distanceDetected(duration), 100);
  
  Serial.println(distanceDetected(duration));
  //delay(10);
}

long distanceDetected(long duration)
{
  return duration  / 2;
}

void playTone(int tone, int duration)
{
 for(long i = 0; i<duration*1000L; i+=tone*2)
 {
   digitalWrite(speaker11, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speaker11, LOW);
   delayMicroseconds(tone);
 } 
}
