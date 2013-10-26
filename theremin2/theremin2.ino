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
  
  //playTone(convertToHertz(duration), 1000);
  playTone(snapToPitch(convertToHertz(duration)), 1000);
  //Serial.println(snapToPitch(convertToHertz(duration)));
  
  //Serial.println(convertToHertz(duration));
  delay(10);
}

long convertToHertz(long duration)
{
  //Serial.println (map(duration, 256, 2048, 261, 523));
  return map(duration, 256, 2048, 256, 523);
}

long snapToPitch(long init)
{
  String names[] = {"C", "b", "a#", "a", "g#", "g", "f#", "f", "e", "d#", "d", "c#", "c"};
  int tones[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523};
  for (int i = 0; i<12; i++)
  {
    if (init <= ((tones[i]+tones[i+1])/2))
   {
     Serial.println(names[i]);
     return tones[i];
   } 
  }
  Serial.println("out of range");
  return 523;
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
