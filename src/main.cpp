/*! \mainpage QUADCOPTER SUPER COOL
 *
 * \section intro_sec EINLEITUNG
 * <img src="../images/quadcopter.jpg">
 * 
 * Projekt im Fach Sensorik für Autonome Systeme <br>
 * Wintersemester 2019/20 <br>
 * Betreuer: Prof. Dr.-Ing. Jörg Dahlkemper Prof. Dr. Dahlkemper
 * 
 * \section team_sec TEAM-MITGLEDERN
 * Pham Duy Anh <br>
 * Karl Gritz <br>
 * Dmitrij Gileles <br>
 *
 * \section increment_sec PROJECTSINKREMENTE
 * <b>Inkrement 1: Mikrocontroller-gesteuerte Fernbedienung des Quadrocopters <br></b>
 * Dokumentation über die Hauptbetrieb des Quadrocopters sind
 * <a href="group___h_a_u_p_t_b_e_t_r_i_e_b.html">hier </a>
 * zu sehen.<br>
 * Stand: 15. Oktober 2019<br><br>
 * <b>Inkrement 2: Quadrocoptersteuerung über Raspberry Pi <br></b>
 * <b>Inkrement 3: Robuste Lagesteuerung durch Sensordatenfusion<br></b>
 * <b>Inkrement 4: Betriebszustandsmonitoring<br></b>
 * 
 * \section install_sec INSTALLATION
 * Dieser Projekt wird mithilfe der folgenden Werkzeugen entwickelt:
 *
 * \subsection dev_env Entwicklungsumgebung
 * <b>Platform</b>: Arduino <br>
 * <b>IDE</b>: Visual Studio Code mit Platform.io Plugin <br>
 * <b>Dokumentationswerkzeug</b>: Doxygen <br>
 * \section help_sec Hilfe
 * 
 * <a href="graph_legend.html">Graphishe Legende der Diagrammen</a>
 *
 * etc...
 */

#include <Arduino.h>
#include "quadcopter.h"

bool QUADCOPTER_MODUS;
bool DEBUG_MONITOR_AKTIVIEREN;

void setup(){
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  quadcopter_hardware_init();
  quadcopter_software_init();
  imu_setup();
  Serial.begin(115200);
  Serial.setTimeout(10);
  //quadcopter_Debug_Monitor_aktivieren(115200);
}

void loop() {
  if (digitalRead(MODUS_WAHL_PIN)==MODUS_AUTO)
  {
    QUADCOPTER_MODUS = MODUS_AUTO;
    digitalWrite(LED_BUILTIN, HIGH);
    //Autobetrieb
    quadcopter_neigung_betrieb();
    
  } else
  {
    QUADCOPTER_MODUS = MODUS_MANUEL;
    digitalWrite(LED_BUILTIN, LOW);
    quadcopter_Manuellbetrieb();
  }
}
