#include <LiquidCrystal_I2C.h>
#include <PulseSensorPlayground.h>
int pulsePin = 0;

int blinkPin = 13;

int fadePin = 8;

int fadeRate = 0;

const int sensor = 1;

float tempc;

float vout;
PulseSensorPlayground pulseSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    pulseSensor.analogInput(pulsePin);
    pulseSensor.setThreshold(550);
    lcd.begin();
    lcd.backlight();
    pulseSensor.begin();

    pinMode(blinkPin, OUTPUT);

    pinMode(fadePin, OUTPUT);

    Serial.begin(115200);

    pinMode(sensor, INPUT);

    Serial.begin(9600);

}


void loop() {


    fadeRate = 255;

    serialOutputWhenBeatHappens();

    vout = analogRead(sensor);

    vout = (vout * 500) / 1023;

    tempc = vout;

    Serial.print("in DegreeC=");

    Serial.print("\t");

    Serial.print(tempc);

    Serial.println();

    lcd.setCursor(0, 1);
    lcd.print("temp in c:");

    lcd.print(tempc);

    delay(2000);


    ledFadeToBeat();

    delay(20);

}

void ledFadeToBeat() {

    fadeRate -= 15;

    fadeRate = constrain(fadeRate, 0, 255);

    analogWrite(fadePin, fadeRate);

}




void serialOutputWhenBeatHappens() {
    if (pulseSensor.sawStartOfBeat()) {


        Serial.print("BPM: ");
        int bpm = pulseSensor.getBeatsPerMinute();
        Serial.println(bpm);
        lcd.setCursor(0, 0);
        lcd.clear();

        lcd.print("BPM: ");

        lcd.print(bpm);
    } else {
        Serial.println("no beats found");

    }
    delay(20);
}
