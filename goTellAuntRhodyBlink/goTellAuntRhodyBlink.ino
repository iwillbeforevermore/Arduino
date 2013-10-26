int speakerPin = 7;
int led13 = 13;
int led12 = 12;
int length = 31;
char notes[] = {"e edc c d d edc g gfe e dcdec  "};
int beats[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int tempo = 100;

void playTone(int tone, int duration)
{
 for(long i = 0; i<duration*1000L; i+=tone*2)
 {
   digitalWrite(speakerPin, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speakerPin, LOW);
   delayMicroseconds(tone);
 } 
}

void playNote(char note, int duration)
{
 char names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'c'};
 int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956}; 
 for (int i = 0; i<7; i++)
 {
   if (names[i] ==note)
  {
    playTone(tones[i], duration);
  } 
 }
}

void setup()
{
  pinMode(speakerPin, OUTPUT);
  pinMode(led13, OUTPUT);
  pinMode(led12, OUTPUT);
}

void loop()
{
 for (int i = 0; i<length; i++)
 {
   if (notes[i] == ' ')
  {
    digitalWrite(led12, HIGH);
    delay (beats[i]*tempo);
    digitalWrite(led12, LOW);
       
  }
  else
  {
    digitalWrite(led13, HIGH);
    playNote(notes[i], beats[i]*tempo);
    digitalWrite(led13, LOW);
  }
  delay (tempo/2);
 } 
}
