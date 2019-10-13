#include <Arduino.h>
#include "quadcopter.h"

void setup(){
  quadcopter_hardware_init();
  quadcopter_software_init();
  quadcopter_Debug_Monitor_aktivieren(9600);
}

void loop() {
  if (digitalRead(modus_wahl_pin)==MODUS_AUTO)
  {
    //Autobetrieb
    // quadcopter_Autobetrieb();
    
    //TEST Reglerwert
    quadcopter_nach_oben(500);
    // quadcopter_nach_unten(500);
    // quadcopter_nach_vorne(500);
    // quadcopter_nach_hinten(500);
    // quadcopter_nach_links(500);
    // quadcopter_nach_rechts(500);
    // quadcopter_aufhalten(1000);
    // quadcopter_aufsetzen(500);
    // quadcopter_links_abbiegen(500);
    // quadcopter_rechts_abbiegen(500);

  } else
  {
    quadcopter_Manuellbetrieb();
  }
}
