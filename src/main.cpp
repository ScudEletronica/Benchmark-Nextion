#include <Arduino.h>
#include "Nextion/Nextion.h"
#include "NextionControl.h"

#define TX_PIN 23
#define RX_PIN 36

NexValue meter = NexValue(0, 3, "t0");
NexValue meter1 = NexValue("Velocidade", 0, 100, 2, 0, 4, "t1");
NexValue meter2 = NexValue("RPM", 0, 200, 0, 6, 0, "t2");
NexValue meter3 = NexValue("Bateria", 0, 15, 1, 0, 5, "t3");
NexValue meter4 = NexValue("Temperatura", 0, 100, 1);

unsigned long previousMillis = 0UL;
unsigned long interval = 1000UL;
unsigned long currentMillis = 0UL;

const char* randomM(char* txt){
  long r = random(-1, 5);
  if (r == -1) return "R";
  else if (r == 0) return "N";
  else {
    sprintf(txt,"%d", r);
    return txt;
  }
}

double fRand(double fMin, double fMax)
{
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

void setup() {
  nexInit(RX_PIN, TX_PIN);
  page0.show();
  // put your setup code here, to run once:
}

void loop() {
  char txt[10];
  meter.evaluate(randomM(txt));
  meter1.evaluate(fRand(0, 100));
  meter2.evaluate(random(0, 200));
  meter3.evaluate(fRand(0, 15));
  
  if(currentMillis - previousMillis > interval) {
    meter4.evaluate(fRand(100, 200));
    unsigned long newMillis = millis();
    if (newMillis - currentMillis > interval) {
      previousMillis = newMillis;
      currentMillis = newMillis;
    }
  } else {
    currentMillis = millis();
    meter4.evaluate(fRand(0, 100));
  }
  // put your main code here, to run repeatedly:
}