#include <Arduino.h>
/***********************************************
 *  MACROS UND PROJEKTPARAMETERN 
***********************************************/

/* Modus Macros*/
#define MODUS_AUTO true
#define MODUS_MANUEL false

/* Betriebsparameter*/
#define REGLER_HALTVERZOEGERUNG 2000
#define REGLER_PWM_OBEN 125
#define REGLER_PWM_UNTEN_STABIL 110
#define REGLER_PWM_RECHTS 130
#define REGLER_PWM_LINKS 125
#define REGLER_PWM_VORNE 125
#define REGLER_PWM_HINTEN 125
#define REGLER_PWM_HALT_STABIL 117

//TODO:
/* Hardware Initializationsparameter */
#define l_y_pin A0        // Links  Y -- Grün   
#define l_x_pin A1        // Links  X -- Weiß     -- Mitte: 126
#define r_x_pin A2        // Rechts X -- Blau     -- Mitte: 127
#define r_y_pin A3        // Rechts Y -- Braun    -- Mitte: 130

#define l_y_pwm_pin 3     // Links  Y -- Grün
#define l_x_pwm_pin 9     // Links  X -- Weiß
#define r_x_pwm_pin 10    // Rechts     X -- Blau
#define r_y_pwm_pin 11    // Rechts Y -- Braun

#define modus_wahl_pin 5  // Status des Kippschalters

/* Software Initializationsparameter */

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
void quadcopter_verzoegen(unsigned int Dauer);
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