#include <Arduino.h>
#include "Nextion/Nextion.h"
#include "NextionControl.h"

int i = 0;

#define TX_PIN 23
#define RX_PIN 36

NexValue meter = NexValue("", 0, 100, true, 0, 3, "t0");

void setup() {
  nexInit();
  // put your setup code here, to run once:
}

void loop() {
  meter.evaluate(random(100));
  // put your main code here, to run repeatedly:
}