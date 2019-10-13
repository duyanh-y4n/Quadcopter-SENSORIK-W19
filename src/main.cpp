#include <Arduino.h>
#include "quadcopter.h"

void setup(){
  quadcopter_hardware_init();
  quadcopter_software_init();
}

void loop() {
  if (digitalRead(modus_wahl_pin)==MODUS_AUTO)
  {
    quadcopter_Autobetrieb();
  } else
  {
    quadcopter_Manuellbetrieb();
  }
}
