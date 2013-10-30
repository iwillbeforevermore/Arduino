//this is a comment
int ledPin = 7;
int bumperPin = 2;
int speaker11 = 11;
int Trig_pin = 10;
int Echo_pin = 13;
int octavePin = 4;
int val = 0;
int octave = -1;
int iVal =0;
int duration;

void setup()
{
 pinMode(ledPin, OUTPUT);
 pinMode(speaker11, OUTPUT);
 pinMode(bumperPin, INPUT); 
 pinMode(octavePin, INPUT);
 pinMode(Trig_pin, OUTPUT);
 pinMode(Echo_pin, INPUT); 
 Serial.begin(9600);
}

void loop()
{
  val = digitalRead(bumperPin);
  octave = digitalRead(octavePin);
  
  if(val == LOW)
  {
   digitalWrite(ledPin, HIGH);
   playTone(snapToPitch(convertToHertz(duration), octave), 1000);
  } 
  else
  {
   digitalWrite(ledPin, LOW);
  }  
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);
  Serial.println (octave);
}

long convertToHertz(long duration)
{
  //Serial.println (map(duration, 256, 2048, 261, 523));
  return map(duration, 256, 2048, 256, 523);
}

long snapToPitch(long init, int octave)
{
  String names[] = {"C", "b", "a#", "a", "g#", "g", "f#", "f", "e", "d#", "d", "c#", "c"};
  int tones1[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523};
  int tones2[] = {523, 554, 587, 622, 659, 698, 739, 783, 830, 880, 932, 987, 1046};
  for (int i = 0; i<12; i++)
  {
    if (init <= ((tones1[i]+tones1[i+1])/2))
   {
     Serial.println(names[i]);
     if (octave == LOW)
     {
       return tones1[i];
     }
   }
   else if (init <= ((tones2[i]+tones2[i+1])/2))
   {
     Serial.println(names[i]);
     if (octave == HIGH)
     {
       return tones2[i];
     }
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
