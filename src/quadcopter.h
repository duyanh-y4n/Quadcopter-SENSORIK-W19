/** @file */

#include <Arduino.h>
/***********************************************
 *  MACROS UND PROJEKTPARAMETERN 
***********************************************/

/* Modus Macros*/
/**
 * @brief 
 * @addtogroup HAUPTBETRIEB 
 * @{
 */
#define MODUS_AUTO true
#define MODUS_MANUEL false
/** @} */

/* Betriebsparameter*/

/** @ingroup GRUNDFUNKTIONEN
 * @defgroup ALLG_PARAMETERN Bewegungsparameter - Zeitvariablen und Bewegungsauslenkung
 * @brief Zeitvaiablen und Bewegungsauslenkung beim Autobetrieb
  * @{
 */
#define REGLER_HALTEDAUER 500
#define REGLER_BREMSDAUER 100
#define REGLER_AUSLENKUNGSDAUER 400
#define REGLER_AUSLENKUNG 60
/** @} */

/** @ingroup GRUNDFUNKTIONEN
 * @defgroup TRANSLATIONSBEWEGUNGSPARAMETERN Bewegungsparameter - Translation
 * @brief PWM-Werte (im Bereich [0:255]) der Translationsbewegungen beim automatischen Betrieb für jeden Achse des Joysticks
  * @{
 */
#define REGLER_PWM_OBEN 130
#define REGLER_PWM_UNTEN 110
#define REGLER_PWM_RECHTS 132
#define REGLER_PWM_LINKS 122
#define REGLER_PWM_VORNE 135
#define REGLER_PWM_HINTEN 125
#define REGLER_PWM_HALT 125 //! unused
/** @} */

/** @ingroup GRUNDFUNKTIONEN
 * @defgroup ROTATIONSBEWEGUNGSPARAMETERN Bewegungsparameter - Rotation
 * @brief PWM-Werte (im Bereich [0:255]) der Translationsbewegungen beim automatischen Betrieb für jeden Achse des Joysticks
  * @{
 */
#define REGLER_PWM_ROTATION_VERTICAL_RECHTS 130
#define REGLER_PWM_ROTATION_VERTICAL_LINKS 125
#define REGLER_PWM_ROTATION_HORIZONTAL_RECHTS 130
#define REGLER_PWM_ROTATION_HORIZONTAL_LINKS 125
/** @} */

/** @ingroup GRUNDFUNKTIONEN
 * @defgroup STARTZUSTANDSPARAMETERN Bewegungsparameter - Start Zustand
 * @brief PWM-Werte (im Bereich [0:255]) des Startzustands für jeden Achse des Joysticks
  * @{
 */
#define REGLER_PWN_L_X_MITTEL 126
#define REGLER_PWN_L_Y_MITTEL 125 //egal
#define REGLER_PWN_R_X_MITTEL 127
#define REGLER_PWN_R_Y_MITTEL 130
/** @} */

/** @ingroup GRUNDFUNKTIONEN
 * @defgroup STABILZUSTANDSPARAMETERN Bewegungsparameter - Stabil Zustand
 * @brief PWM-Werte (im Bereich [0:255]) des stabilen Zustands für jeden Achse des Joysticks
  * @{
 */
#define REGLER_PWN_L_X_STABIL 125
#define REGLER_PWN_L_Y_STABIL 117
#define REGLER_PWN_R_X_STABIL 125
#define REGLER_PWN_R_Y_STABIL 125
/** @} */


//TODO:
/** @defgroup HARDWARE_INIT Hardware Initialization
 * @brief Pins der Modulen des MCUs vorbereiten
  * @{
 */
#define JOYSTICK_LINKS_Y_PIN A0        // Links  Y -- Grün   
#define JOYSTICK_LINKS_X_PIN A1        // Links  X -- Weiß     -- Mitte: 126
#define JOYSTICK_RECHTS_X_PIN A2       // Rechts X -- Blau     -- Mitte: 127
#define JOYSTICK_RECHTS_Y_PIN A3       // Rechts Y -- Braun    -- Mitte: 130

#define JOYSTICK_LINKS_Y_PWM_PIN 3     // Links  Y -- Grün
#define JOYSTICK_LINKS_X_PWM_PIN 9     // Links  X -- Weiß
#define JOYSTICK_RECHTS_X_PWM_PIN 10   // Rechts X -- Blau
#define JOYSTICK_RECHTS_Y_PWM_PIN 11   // Rechts Y -- Braun

#define MODUS_WAHL_PIN 5  // Status des Kippschalters
/** @} */

/** @defgroup SOFTWARE_INIT Software Initialization
 * @brief Macro und Werte für Software-implementation
  * @{
 */
//! Pins für OBEN-UNTEN Translationsbewegeung
#define PWM_TRANSLATION_VERTICAL_OUTPUT_PIN JOYSTICK_LINKS_Y_PWM_PIN 
//! Pins für VORWÄRTS-RÜCKWÄRTS Translationsbewegeung
#define PWM_TRANSLATION_HORIZONTAL_OUTPUT_PIN JOYSTICK_RECHTS_Y_PWM_PIN 
//! Pins für LINKS-RECHTS Translationsbewegeung
#define PWM_TRANSLATION_HORIZONTAL_LR_OUTPUT_PIN JOYSTICK_RECHTS_X_PWM_PIN 
//! Pins für ABBIEGUNGSWINKEL LINKS-RECHTS Rotationsbewegeung um vertikalen Achse
#define PWM_ROTATION_VERTICAL_OUTPUT_PIN JOYSTICK_LINKS_X_PWM_PIN 
/** @} */

/***********************************************
 *  FUNKTIONSPROTOTYP
***********************************************/
/**
 * @brief Hardware initialization: Pinsmode und Konfigurationen für alle Modulen des MCUs
 * @ingroup HARDWARE_INIT
 * */
void quadcopter_hardware_init();

/**
 * @brief Hardware initialization: Pinsmode und Konfigurationen für alle Modulen des MCUs
 * @ingroup SOFTWARE_INIT
 * */
void quadcopter_software_init();

/** @defgroup GRUNDFUNKTIONEN Grundfunktionen des Autobetriebs
 * @brief Funktionen zur Steuerung der Bewegung des Quadcopters
  * @{
 */
/**
 * @brief Rotationsbewegung um vertikalen Achse (Gierung)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_links_abbiegen(unsigned int Dauer);

/**
 * @brief Rotationsbewegung um vertikalen Achse (Gierung)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_rechts_abbiegen(unsigned int Dauer);

/**
 * @brief Translationsbewegung nach vorne (Nicken)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_vorne(unsigned int Dauer);

/**
 * @brief Translationsbewegung nach hinten (Nicken)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_hinten(unsigned int Dauer);

/**
 * @brief Translationsbewegung entlang horizontalen Achse (Rollen und Bewegen)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_rechts(unsigned int Dauer);

/**
 * @brief Translationsbewegung entlang horizontalen Achse (Rollen und Bewegen)
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_links(unsigned int Dauer);

/**
 * @brief Translationsbewegung entlang vertikalen Achse 
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_oben(unsigned int Dauer);

/**
 * @brief Translationsbewegung entlang vertikalen Achse
 * 
 * @param Dauer Dauer der Bewegung in ms 
 */
void quadcopter_nach_unten(unsigned int Dauer);

/**
 * @brief in der Luft stabil liegen
 * 
 * @param Dauer Dauer des stabilen Zustands in ms 
 */
void quadcopter_aufhalten(unsigned int Dauer);

/**
 * @brief langam runter fahren und aufsetzen
 * 
 * @param Dauer max. Dauer der Bewegung in ms 
 */
void quadcopter_aufsetzen(unsigned int Dauer);

/**
 * @brief alle Prozess zeitlich verzögern
 * 
 * @param Dauer Dauer der Verzögerung in ms 
 */
void quadcopter_verzoegern(unsigned int Dauer);
/** @} */

/** @defgroup DEBUG_MONITOR Debug Monitor
 * @brief Ultilities zum Deguggen des MCUs per Serial-Monitor
  * @{
 */

/**
 * @brief Debug Serialmonitor aktivieren 
 * 
 * @param baudrate Serialbaudrate
 */
void quadcopter_Debug_Monitor_aktivieren(unsigned long baudrate);

/**
 * @brief Debug Serialmonitor deaktivieren 
 * 
 * @param baudrate Serialbaudrate
 */
void quadcopter_Debug_Monitor_deaktivieren();

/**
 * @brief Ausgabe auf Debugmonitor
 * 
 */
#define quadcopter_print(input) if(DEBUG_MONITOR_AKTIVIEREN) Serial.print(input);

/**
 * @brief Ausgabe auf Debugmonitor
 * 
 */
#define quadcopter_println(input) if(DEBUG_MONITOR_AKTIVIEREN) Serial.println(input);
/** @} */

/** @defgroup HAUPTBETRIEB Hauptbetrieb des Quadcopters
 * @brief Autobetriebsmodus und Manuellbetriebsmodus <br>
 * <b>Flussdiagram des Hauptbetrieb: </b><br>
 * <img src="../images/Flussdiagramm-arduino.png">
  * @{
 */

/**
 * @brief Autobetrieb des Quadcopters (als FSM implementiert) <br>
 * <b>Flussdiagram:</b> <br>
 * <img src="../images/Autobetrieb.png"> <br>
 * <br><b>FSM-Diagram:</b> <br>
 * <img src="../images/FSM-Autobetrieb.png"> <br> 
 */
void quadcopter_Autobetrieb();

/**
 * @brief Manuellbetrieb des Quadcopters <br>
 * <b>Flussdiagram:</b> <br>
 * <img src="../images/Manuellbetrieb.png">
 * 
 */
void quadcopter_Manuellbetrieb();

/**
 * @brief software zwingende Modusänderung (zwischen auto und manuell. Betrieb)
 * @param Modus 
 */
void quadcopter_Modus_veraendern(bool Modus);
/** @} */