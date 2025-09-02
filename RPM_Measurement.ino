#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD Setup: I2C address 0x27 is common. Change to 0x3F if needed.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions
const int potPin     = A0;   // Potentiometer to control speed
const int in1        = 8;    // L298N IN1
const int in2        = 9;    // L298N IN2
const int enA        = 10;   // L298N ENA (PWM)
const int encoderPin = 2;    // Encoder output (interrupt)

// Encoder & RPM variables
volatile unsigned int pulseCount = 0;
unsigned int lastCount = 0;
unsigned long lastMillis = 0;

const int pulsesPerRevolution = 20; // ← Change based on your encoder disc's number of slots

void setup() {
  // Serial for debugging (optional)
  Serial.begin(9600);

  // LCD Init
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RPM Meter Ready");

  // Motor Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  // Set motor direction (forward)
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Encoder setup
  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderPin), countPulse, RISING);

  // Timing
  lastMillis = millis();
}

void loop() {
  // Read potentiometer and map to PWM value (0–255)
  int potValue = analogRead(potPin);
  int pwmValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(enA, pwmValue);

  // RPM Calculation every 1 second
  if (millis() - lastMillis >= 1000) {
    noInterrupts();  // Pause interrupt while reading
    unsigned int currentCount = pulseCount;
    pulseCount = 0;
    interrupts();

    // Calculate RPM = (pulses / pulsesPerRev) * (60 sec / 1 min)
    float rpm = (currentCount / (float)pulsesPerRevolution) * 60.0;

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PWM: ");
    lcd.print(pwmValue);
    lcd.setCursor(0, 1);
    lcd.print("RPM: ");
    lcd.print((int)rpm);

    // Debug output
    Serial.print("PWM: ");
    Serial.print(pwmValue);
    Serial.print("  RPM: ");
    Serial.println((int)rpm);

    lastMillis = millis();
  }
}

// Interrupt function
void countPulse() {
  pulseCount++;
}

