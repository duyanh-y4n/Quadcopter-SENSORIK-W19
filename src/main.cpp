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

enum richtung_zustand { standart, vor, vor_brems, vor_halt, vor_halt_nach, 
                                  zurueck, zurueck_brems, zurueck_halt, zurueck_halt_nach,
                                  rechts, rechts_brems, rechts_halt, rechts_halt_nach, 
                                  links, links_brems, links_halt, links_halt_nach};
richtung_zustand richtung;
richtung_zustand richtung_next;

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

unsigned short auslenkung = 60;

unsigned int auslenkung_dauer = 400;
unsigned int halte_dauer = 500;
unsigned int brems_dauer = 100;

unsigned long letzte_umschalt = 0;

void setup(){
  quadcopter_hardware_init();
  quadcopter_software_init();
  quadcopter_Debug_Monitor_aktivieren(9600);
  richtung = standart;
}

void loop() {
  if (digitalRead(MODUS_WAHL_PIN)==MODUS_AUTO)
  {
    //Autobetrieb
    // quadcopter_Autobetrieb();
    
    digitalWrite(LED_BUILTIN, HIGH);

    // analogWrite(JOYSTICK_LINKS_X_PWM_PIN, REGLER_PWN_L_X_MITTEL);
    // analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, REGLER_PWN_L_Y_STABIL);
    // analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, REGLER_PWN_R_X_MITTEL);
    // analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, REGLER_PWN_R_Y_MITTEL);
    
 // Joystick Werte ablesen
    _joystick_l_x_pos = analogRead(JOYSTICK_LINKS_X_PIN);
    _joystick_l_y_pos = analogRead(JOYSTICK_LINKS_Y_PIN);

    // Joystick Werte im Bereich [1,255] quantisieren
    _l_x_pwm_wert = map(_joystick_l_x_pos, 0, 1023, 0, 255);
    _l_y_pwm_wert = map(_joystick_l_y_pos, 0, 1023, 0, 255);

    richtung_next = richtung;

// ============================= ANFANG SWITCH CASE ======================================

    switch (richtung)
    {

    case standart:
        _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
        _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
        letzte_umschalt = millis();
        richtung_next = vor;
    break;
// ============================= VOR ======================================

    case vor: // nach vorne
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL - auslenkung;
      if(millis()-letzte_umschalt > auslenkung_dauer) {
        letzte_umschalt = millis();
        richtung_next = vor_halt;
      }
    break;

    case vor_halt:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > 800) {
        letzte_umschalt = millis();
        richtung_next = vor_brems;
      }
    break;

    case vor_brems:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL + auslenkung;
      if(millis()-letzte_umschalt > brems_dauer) {
        letzte_umschalt = millis();
        richtung_next = vor_halt_nach;
      }
    break;

    case vor_halt_nach:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = zurueck;
      }
    break;

// ============================= ZURUECK ======================================    

    case zurueck: // nach vorne
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL + auslenkung;
      if(millis()-letzte_umschalt > auslenkung_dauer) {
        letzte_umschalt = millis();
        richtung_next = zurueck_halt;
      }
    break;

    case zurueck_halt:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = zurueck_brems;
      }
    break;

    case zurueck_brems:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL - auslenkung;
      if(millis()-letzte_umschalt > brems_dauer) {
        letzte_umschalt = millis();
        richtung_next = zurueck_halt_nach;
      }
    break;

    case zurueck_halt_nach:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = rechts;
      }
    break;

// ============================= RECHTS ======================================    

    case rechts: // nach vorne
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL - auslenkung;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > auslenkung_dauer) {
        letzte_umschalt = millis();
        richtung_next = rechts_halt;
      }
    break;

    case rechts_halt:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = rechts_brems;
      }
    break;

    case rechts_brems:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL + auslenkung;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > brems_dauer) {
        letzte_umschalt = millis();
        richtung_next = rechts_halt_nach;
      }
    break;

    case rechts_halt_nach:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = links;
      }
    break;

// ============================= LINKS ======================================

    case links: // 
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL + auslenkung;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > auslenkung_dauer) {
        letzte_umschalt = millis();
        richtung_next = links_halt;
      }
    break;

    case links_halt:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = links_brems;
      }
    break;

    case links_brems:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL - auslenkung;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > brems_dauer) {
        letzte_umschalt = millis();
        richtung_next = links_halt_nach;
      }
    break;

    case links_halt_nach:
      _r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      _r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > halte_dauer) {
        letzte_umschalt = millis();
        richtung_next = standart;
      }
    break;

    default:
      break;
    }

// ============================= ENDE SWITCH CASE ======================================
    analogWrite(JOYSTICK_LINKS_X_PWM_PIN, _l_x_pwm_wert);
    analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, _l_y_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, _r_x_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, _r_y_pwm_wert);
    richtung = richtung_next;


  } else
  {
    richtung = standart;
    digitalWrite(LED_BUILTIN, LOW);
    quadcopter_Manuellbetrieb();
  }
}
