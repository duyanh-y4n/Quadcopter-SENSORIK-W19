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

unsigned short sequenz_nr = 0;


unsigned int _joystick_l_x_pos;
unsigned int _joystick_l_y_pos;
unsigned int _joystick_r_x_pos;
unsigned int _joystick_r_y_pos;

float _l_x_tastgrad;
float _l_y_tastgrad;
float _r_x_tastgrad;
float _r_y_tastgrad;

unsigned int _l_x_pwm_wert;
unsigned int _l_y_pwm_wert;
unsigned int _r_x_pwm_wert;
unsigned int _r_y_pwm_wert;




bool QUADCOPTER_MODUS;
bool DEBUG_MONITOR_AKTIVIEREN;

void setup(){
  quadcopter_hardware_init();
  quadcopter_software_init();
  quadcopter_Debug_Monitor_aktivieren(9600);
}

void loop() {
  if (digitalRead(MODUS_WAHL_PIN)==MODUS_AUTO)
  {
    QUADCOPTER_MODUS = MODUS_AUTO;
    digitalWrite(LED_BUILTIN, HIGH);
    //Autobetrieb
    quadcopter_Autobetrieb();
    
  } else
  {
    QUADCOPTER_MODUS = MODUS_MANUEL;
    digitalWrite(LED_BUILTIN, LOW);
    quadcopter_Manuellbetrieb();
  }
}
