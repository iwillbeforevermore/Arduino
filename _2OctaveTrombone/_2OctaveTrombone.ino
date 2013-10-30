int ledPin = 7;
int bumperPin = 2;
int speaker11 = 11;
int Trig_pin = 10;
int Echo_pin = 13;
int octavePin = 4;
int val = 0;
int octave = -1;
int duration;
int distance;
long hertz;
int pos = -1;

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
   playTone(snapToPitch(hertz, octave), 1000);
  } 

  if (octave == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
   digitalWrite(ledPin, LOW); 
  }

  getTheDistance();
  convertToHertz(distance);
}



void getTheDistance()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig_pin, LOW);
  distance = pulseIn(Echo_pin,HIGH);
}

void convertToHertz(long duration)
{
  hertz = map(distance, 256, 2048, 256, 523);
}

long snapToPitch(long hertz, int octave)
{
    String names[] = {"C", "b", "a#", "a", "g#", "g", "f#", "f", "e", "d#", "d", "c#", "c"};
  int tones[] = {262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523};
  for (int i = 0; i<12; i++)
  {
    if (hertz <= ((tones[i]+tones[i+1])/2))
   {
     Serial.println(names[i] + octave);
     if (octave == HIGH)
     {
       return tones[i];
     }
     else if (octave == LOW)
     {
       return (2*tones[i]);
     }
   } 
  }
  Serial.println("out of range");
  if (octave == HIGH)
  {
    return 523;
  }
  return (2*523);
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
