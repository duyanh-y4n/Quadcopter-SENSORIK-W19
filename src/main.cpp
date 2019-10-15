/*! \mainpage QUADCOPTER SUPER COOL
 *
 * \section intro_sec EINLEITUNG
 * <img src="../images/quadcopter.jpg">
 * 
 * This is the introduction.
 *
 * \section install_sec INSTALLATION
 *
 * \subsection dev_env Entwicklungsumgebung
 * Platform: Arduino <br>
 * IDE: Visual Studio Code mit Platform.io Plugin <br>
 * Dokumentationswerkzeug: Doxygen <br>
 * \section help_sec Hilfe
 * 
 * <a href="graph_legend.html">Graphishe Legende der Diagrammen</a>
 *
 * etc...
 */

#include <Arduino.h>
#include "quadcopter.h"

void setup(){
  quadcopter_hardware_init();
  quadcopter_software_init();
  quadcopter_Debug_Monitor_aktivieren(9600);
}

void loop() {
  if (digitalRead(MODUS_WAHL_PIN)==MODUS_AUTO)
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
    quadcopter_aufhalten(1000);
    quadcopter_aufsetzen(500);
    // quadcopter_links_abbiegen(500);
    // quadcopter_rechts_abbiegen(500);
    delay(2000);

  } else
  {
    quadcopter_Manuellbetrieb();
  }
}
