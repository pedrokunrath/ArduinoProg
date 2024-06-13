#include <Adafruit_LiquidCrystal.h>

int cm = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  Serial.begin(9600);
}


long retornaDistancia(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return 0.01723 * pulseIn(echoPin, HIGH);
}


void loop()
{
  cm = retornaDistancia(7, 7);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Uhuul");
  lcd_1.setCursor(1, 1);
  lcd_1.print("                ");
  lcd_1.setCursor(1, 1);
  lcd_1.print(cm);
  Serial.print(cm);
  Serial.println("cm");
  delay(500); // Wait for 100 millisecond(s)
}