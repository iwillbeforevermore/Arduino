int led13 = 13;

void setup ()
{
 pinMode(led13, OUTPUT);
}

void loop()
{
 digitalWrite(led13, HIGH);
 delay (1000);
 digitalWrite(led13, LOW);
 delay (100); 
}
