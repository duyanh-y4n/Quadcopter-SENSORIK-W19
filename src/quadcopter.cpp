#include "quadcopter.h"

void quadcopter_links_abbiegen(unsigned int Verzoegerung){
    quadcopter_print("Biegt nach LINKS... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_rechts_abbiegen(unsigned int Verzoegerung){
    quadcopter_println("Biegt nach RECHTS...");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_vorne(unsigned int Verzoegerung){
    quadcopter_print("Fliegt nach VORNE... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_hinten(unsigned int Verzoegerung){
    quadcopter_print("Fliegt nach HINTEN... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_rechts(unsigned int Verzoegerung){
    quadcopter_print("fliegt nach RECHTS... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_links(unsigned int Verzoegerung){
    quadcopter_print("Fliegt nach LINKS... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_oben(unsigned int Verzoegerung){
    quadcopter_print("Fliegt nach OBEN... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_nach_unten(unsigned int Verzoegerung){
    quadcopter_print("Fliegt nach UNTEN... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_aufhalten(unsigned int Verzoegerung){
    quadcopter_print("HALT AUF... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_aufsetzen(unsigned int Verzoegerung){
    quadcopter_print("SETZT AUF... ");
    quadcopter_verzoegen(Verzoegerung);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Verzoegerung);
    quadcopter_println(" ms)");
};

void quadcopter_verzoegen(unsigned int Verzoegerung){
    delay(Verzoegerung);
};

void quadcopter_Debug_Monitor_aktivieren(unsigned long baudrate){
    DEBUG_MONITOR_AKTIVIEREN = true;
    Serial.begin(baudrate);
    Serial.print("Start debugging monitor at baud ");
    Serial.println(baudrate);
};

void quadcopter_Debug_Monitor_deaktivieren(){
    DEBUG_MONITOR_AKTIVIEREN = false;
};

void quadcopter_Autobetrieb(){
    quadcopter_println("__________________________________");
    quadcopter_println("Automodus start");
    quadcopter_println("----------------------------------");
    if (QUADCOPTER_MODUS==MODUS_AUTO)
    {
        quadcopter_aufsetzen(500);
        quadcopter_nach_oben(500);
        quadcopter_aufhalten(500);
        quadcopter_nach_vorne(500);
        quadcopter_aufhalten(2000);
        quadcopter_nach_hinten(500);
        quadcopter_aufhalten(2000);
        quadcopter_nach_rechts(500);
        quadcopter_aufhalten(2000);
        quadcopter_nach_links(500);
        quadcopter_aufhalten(2000);
        quadcopter_aufsetzen(500);
        quadcopter_println("----------------------------------");
        quadcopter_println("Automodus fertig");
        quadcopter_println("__________________________________");
    }
    else{
        quadcopter_println("----------------------------------");
        quadcopter_println("FEHLER! noch in Manuellmodus");
        quadcopter_println("__________________________________");
    }
};

void quadcopter_Manuellbetrieb(){
    quadcopter_println("__________________________________");
    quadcopter_println("Manuellmodus start");
    quadcopter_println("----------------------------------");
    if (QUADCOPTER_MODUS==MODUS_MANUEL)
    {
        quadcopter_println("----------------------------------");
        quadcopter_println("Manuellmodus fertig");
        quadcopter_println("__________________________________");
    }
    else{
        quadcopter_println(" ----------------------------------");
        quadcopter_println("FEHLER! noch in Automodus");
        quadcopter_println("__________________________________");
    }
};
void quadcopter_Modus_veraendern(bool Modus){
    QUADCOPTER_MODUS = Modus;
}
