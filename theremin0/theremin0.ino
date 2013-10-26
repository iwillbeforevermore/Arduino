// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>

int Trig_pin =  13;   // pin for triggering pulse
int Echo_pin = 10;     // pin for recieving echo
int speakerPin = 11;
long duration;


void setup() 
{
  Serial.begin(9600);
  Serial.println ("Starting");
  pinMode(Trig_pin, OUTPUT);
  pinMode(Echo_pin, INPUT);
  pinMode(speakerPin, OUTPUT);
  
  
  //initialize Timer1
  cli();               //disable global interrupts
  TCCR1A = 0;          //set entire TCCR1A register to 0
  TCCR1B = 0;

  //enable Timer1 overflow interrupt:
  TIMSK1 = (1 << TOIE1);
  //set CS10 bit so timer runs at cloack speed:
  TCCR1B |= (1 << CS10);
  //senable global interrupts:
  sei();
}

ISR(Timer1_OVF_vect)
{
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);
  duration = pulseIn(Echo_pin,HIGH);
}



long distanceDetected(long duration)
{
  return duration / 29 / 2;
}

long convertedTone(long distance)
{
  return distance * 1000; 
}


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

void loop()
{
   //Serial.println("Duration:  ");
   //Serial.println(duration, DEC);
  playTone(convertedTone(duration), 1000);
}
