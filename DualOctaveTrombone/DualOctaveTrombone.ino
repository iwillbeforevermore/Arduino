/**--------------------------------------------------
Dual Octave Trombone:
    By Jessica Chang, Spring 2013
This code was written for an "electric trombone".
  It uses a VEX ultrasonic sensor to detect the distance
  from the plunger to the sensor, a button to control
  the octave it is playing in, an LED for visual feedback
  and another button that acts as an "air valve" and 
  dictates when the instrument will sound. In addition,
  the code is written such that the tones are "snapped"
  to the closest half-step. Using the serial monitor,
  it is possible to observe both the letter of the note
  being played and the octave that it is in. 
**//**--------------------------------------------------**/


/**--------------------------------------------------
Pin assignments
**//**--------------------------------------------**/
int ledPin = 7;
int bumperPin = 2;
int speaker11 = 11;
int Trig_pin = 10;
int Echo_pin = 13;
int octavePin = 4;

/**--------------------------------------------------
Global Variables
**//**--------------------------------------------**/
int val = 0;
int octave = -1;
int duration;
int distance;
long hertz;

/**--------------------------------------------------
Setup of the pins; 
The inputs are the two buttons and the echo from the 
  ultrasonic sensor.
The outputs are the speaker, LED and trig from the 
  ultrasonic sensor.
The serial is also initialized.
**//**--------------------------------------------**/
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

/**--------------------------------------------------
The Loop:
The values for the air valve button and the octave button
  are read. If the air valve is pressed, then a tone will 
  be played. If the octave button is pressed, then the LED
  will illuminate as a visual aid for the player.
At the end of the loop, the distance of the plunger and the
  value of the corresponding raw hertz are refreshed.
**//**--------------------------------------------**/

void loop()
{
  val = digitalRead(bumperPin);
  octave = digitalRead(octavePin);
  octaveCheck();
  
  if(val == LOW)
  {
   playTone(snapToPitch(hertz, octave), 1000);
  } 

  getTheDistance();
  convertToHertz();
}

/**--------------------------------------------------
THE FUNCTIONS:
  void getTheDistance()
  void convertToHertz()
  void octaveCheck()
  long snapToPitch(long hertz, int octave)
  void playTone()
**//**--------------------------------------------**/



/** getTheDistance()
      This function calls the ultrasonic sensor
        to send out a ping and waits for it to 
        return. Then it sets the value of distance.
**/


void getTheDistance()
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig_pin, LOW);
  distance = pulseIn(Echo_pin,HIGH);
}

/** convertToHertz()
      This function sets the value of the variable
        hertz by mapping the value of distance out 
        to one between 256 and 523.
**/

void convertToHertz()
{
  hertz = map(distance, 256, 2048, 256, 523);
}

/** octaveCheck()
      This function checks the state of the octave
        button. If it is pressed, the LED lights up.
**/

void octaveCheck()
{
  if (octave == LOW)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
   digitalWrite(ledPin, LOW); 
  }
}

/** snapToPitch(long hertz, int octave)
      This function determines the pitch that is to
        be played by snapping the value of the variable
        hertz to the half-tone that is to be played.
        Using an array for the letters of the tones and 
        a parallel array for the exact pitch values of 
        those tones, it is determined which pitch is closest
        to the varible hertz. 
      If the octave button is pressed, the pitch values to
        be played will be doubled, raising the tone by one
        octave, and that value will be returned. Otherwise,
        the original pitch that was closest to the variable
        hertz is returned.
      If the hertz is too far away from the pitch tones
        (only if it is greater than 523), then "Out of range"
        will be printed and the highest pitch returned. This
        still takes into account the position of the octave
        button.
**/

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


/** playTone(int tone, int duration)
      This function actually calls the Piezo to play the 
        tone. It does so by toggling the value of the 
        speaker rapidly such that it is vibrating at the 
        number of times per minute (hertz) specified.
      The duration of the tone can be adjusted by the 
        parameter in the function's argument.
**/

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
