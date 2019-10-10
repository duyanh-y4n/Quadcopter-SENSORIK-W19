#include <Arduino.h>
/* Macros */
#define MODUS_AUTO true
#define MODUS_MANUEL false
extern bool DEBUG_MONITOR_AKTIVIEREN;
extern bool QUADCOPTER_MODUS;
#define QUADCOPTER_HALTVERZOEGERUNG 2000

/* Funktionsprototypen */
/* Grundfunktionen */
void quadcopter_links_abbiegen(unsigned int Verzoegerung);
void quadcopter_rechts_abbiegen(unsigned int Verzoegerung);
void quadcopter_nach_vorne(unsigned int Verzoegerung);
void quadcopter_nach_hinten(unsigned int Verzoegerung);
void quadcopter_nach_rechts(unsigned int Verzoegerung);
void quadcopter_nach_links(unsigned int Verzoegerung);
void quadcopter_nach_oben(unsigned int Verzoegerung);
void quadcopter_nach_unten(unsigned int Verzoegerung);
void quadcopter_aufhalten(unsigned int Verzoegerung);
void quadcopter_aufsetzen(unsigned int Verzoegerung);
void quadcopter_verzoegen(unsigned int Verzoegerung);
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