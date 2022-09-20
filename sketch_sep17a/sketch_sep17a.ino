#define USE_ARDUINO_INTERRUPTS true
#define DEBUG true
#include <LiquidCrystal_I2C.h>
#include <PulseSensorPlayground.h>
int pulsePin = 0;

int blinkPin = 13;

int fadePin = 8;

int fadeRate = 0;

const int sensor = A1;

float tempc;

float vout;
PulseSensorPlayground pulseSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile int BPM;

int Signal;

volatile int IBI = 600;

volatile boolean QS = false;

static boolean serialVisual = true;

void setup() {
    pulseSensor.analogInput(pulsePin);
    pulseSensor.setThreshold(550);
    lcd.begin();
    lcd.backlight();
    pulseSensor.begin();

    pinMode(blinkPin, OUTPUT);

    pinMode(fadePin, OUTPUT);

    Serial.begin(115200);

    interruptSetup();

    pinMode(sensor, INPUT);

    Serial.begin(9600);

}


void loop() {

    QS = true;
    if (QS == true)

    {


        fadeRate = 255;

        serialOutputWhenBeatHappens();

        QS = false;

        vout = analogRead(sensor);

        vout = (vout * 500) / 1023;

        tempc = vout;

        Serial.print("in DegreeC=");

        Serial.print("\t");

        Serial.print(tempc);

        Serial.println();

        lcd.setCursor(0,1);
        lcd.print("temp in c:");

        lcd.print(tempc);

        delay(2000);

    }

    ledFadeToBeat();

    delay(20);

}

void ledFadeToBeat()

{

    fadeRate -= 15;

    fadeRate = constrain(fadeRate, 0, 255);

    analogWrite(fadePin, fadeRate);

}

void interruptSetup()

{


    int TCCR2A = 0x02;

    int TCCR2B = 0x06;

    int OCR2A = 0X7C;

    int TIMSK2 = 0x02;

    sei();

}


void serialOutputWhenBeatHappens()

{
    if (serialVisual == true && pulseSensor.sawStartOfBeat())

    {


        Serial.print("BPM: ");

        Serial.println(pulseSensor.getBeatsPerMinute());
        lcd.setCursor(0,0);
        lcd.clear();

        lcd.print("BPM: ");

        lcd.print(BPM);
    } else

    {
        Serial.println("no beats found");

    }
    delay(20);
}

void sendDataToSerial(char symbol, int data)

{

    Serial.print(symbol);

    Serial.println(data);

}
