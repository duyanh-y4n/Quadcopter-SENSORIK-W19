/** \file */

#include <Arduino.h>
/***********************************************
 *  MACROS UND PROJEKTPARAMETERN 
***********************************************/

/* Modus Macros*/
#define MODUS_AUTO true
#define MODUS_MANUEL false

/* Betriebsparameter*/
/** \defgroup TRANSLATIONSBEWEGUNGSPARAMETERN Bewegungsparameter - Translation
 * \brief PWM-Werte der Translationsbewegungen beim automatischen Betrieb für jeden Achse des Joystick
  * @{
 */
#define REGLER_HALTEDAUER 2000
#define REGLER_PWM_OBEN 125
#define REGLER_PWM_UNTEN 110
#define REGLER_PWM_RECHTS 130
#define REGLER_PWM_LINKS 125
#define REGLER_PWM_VORNE 125
#define REGLER_PWM_HINTEN 125
#define REGLER_PWM_HALT 125
/** @} */

/** \defgroup ROTATIONSBEWEGUNGSPARAMETERN Bewegungsparameter - Rotation
 * \brief PWM-Werte der Translationsbewegungen beim automatischen Betrieb für jeden Achse des Joystick
  * @{
 */
#define REGLER_PWM_ROTATION_VERTICAL_RECHTS 130
#define REGLER_PWM_ROTATION_VERTICAL_LINKS 125
#define REGLER_PWM_ROTATION_HORIZONTAL_RECHTS 130
#define REGLER_PWM_ROTATION_HORIZONTAL_LINKS 125
/** @} */

/** \defgroup STARTZUSTANDSPARAMETERN Bewegungsparameter - Start Zustand
 * \brief PWM-Werte des Startzustands für jeden Achse des Joystick
  * @{
 */
#define REGLER_PWN_L_X_MITTEL 125
#define REGLER_PWN_L_Y_MITTEL 125
#define REGLER_PWN_R_X_MITTEL 125
#define REGLER_PWN_R_Y_MITTEL 125
/** @} */

/** \defgroup STABILZUSTANDSPARAMETERN Bewegungsparameter - Stabil Zustand
 * \brief PWM-Werte des stabilen Zustands für jeden Achse des Joystick
  * @{
 */
#define REGLER_PWN_L_X_STABIL 125
#define REGLER_PWN_L_Y_STABIL 125
#define REGLER_PWN_R_X_STABIL 125
#define REGLER_PWN_R_Y_STABIL 125
/** @} */


//TODO:
/* Hardware Initializationsparameter */
/** \defgroup HARWARE_INIT Hardware Initializationsparameter 
 * \brief Pins der Modulen des MCU vorbereiten
  * @{
 */
#define l_y_pin A0        // Links  Y -- Grün   
#define l_x_pin A1        // Links  X -- Weiß     -- Mitte: 126
#define r_x_pin A2        // Rechts X -- Blau     -- Mitte: 127
#define r_y_pin A3        // Rechts Y -- Braun    -- Mitte: 130

#define l_y_pwm_pin 3     // Links  Y -- Grün
#define l_x_pwm_pin 9     // Links  X -- Weiß
#define r_x_pwm_pin 10    // Rechts     X -- Blau
#define r_y_pwm_pin 11    // Rechts Y -- Braun

#define modus_wahl_pin 5  // Status des Kippschalters
/** @} */

/* Software Initializationsparameter */
/* Hardware Initializationsparameter */
/** \defgroup SOFTWARE_INIT Software Initializationsparameter 
 * \brief Macro für Software-implementation
  * @{
 */
//! Pins für OBEN-UNTEN Translationsbewegeung
#define PWM_TRANSLATION_VERTICAL_OUTPUT_PIN l_y_pwm_pin 
//! Pins für VORWÄRTS-RÜCKWÄRTS Translationsbewegeung
#define PWM_TRANSLATION_HORIZONTAL_OUTPUT_PIN l_x_pwm_pin 
//! Pins für LINKS-RECHTS Translationsbewegeung
#define PWM_TRANSLATION_HORIZONTAL_LR_OUTPUT_PIN r_x_pwm_pin 
//! Pins für ABBIEGUNGSWINKEL LINKS-RECHTS Rotationsbewegeung um vertikalen Achse
#define PWM_ROTATION_VERTICAL_OUTPUT_PIN r_y_pwm_pin 
/** @} */

/***********************************************
 *  FUNKTIONSPROTOTYP
***********************************************/
/* Initialization */
void quadcopter_hardware_init();
void quadcopter_software_init();

/* Grundfunktionen */
void quadcopter_links_abbiegen(unsigned int Dauer);
void quadcopter_rechts_abbiegen(unsigned int Dauer);
void quadcopter_nach_vorne(unsigned int Dauer);
void quadcopter_nach_hinten(unsigned int Dauer);
void quadcopter_nach_rechts(unsigned int Dauer);
void quadcopter_nach_links(unsigned int Dauer);
void quadcopter_nach_oben(unsigned int Dauer);
void quadcopter_nach_unten(unsigned int Dauer);
void quadcopter_aufhalten(unsigned int Dauer);
void quadcopter_aufsetzen(unsigned int Dauer);
void quadcopter_verzoegern(unsigned int Dauer);
void quadcopter_Modus_veraendern(bool Modus);

/* Betriebfunktionen */
// Serial Monitor zum debuggen vorbereiten
void quadcopter_Debug_Monitor_aktivieren(unsigned long baudrate);
void quadcopter_Debug_Monitor_deaktivieren();
#define quadcopter_print(input) if(DEBUG_MONITOR_AKTIVIEREN) Serial.print(input);
#define quadcopter_println(input) if(DEBUG_MONITOR_AKTIVIEREN) Serial.println(input);

// Hauptbetrieb
void quadcopter_Autobetrieb();
void quadcopter_Manuellbetrieb();