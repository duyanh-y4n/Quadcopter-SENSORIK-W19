#include "quadcopter.h"

//TODO
void quadcopter_hardware_init(){
    pinMode(modus_wahl_pin, INPUT_PULLUP);
    pinMode(l_x_pwm_pin, OUTPUT);
    pinMode(l_y_pwm_pin, OUTPUT);
    pinMode(r_x_pwm_pin, OUTPUT);
    pinMode(r_y_pwm_pin, OUTPUT);
};

void quadcopter_software_init(){
    QUADCOPTER_MODUS = MODUS_MANUEL;

    unsigned int joystick_l_x_pos = 0;
    unsigned int joystick_l_y_pos = 0;
    unsigned int joystick_r_x_pos = 0;
    unsigned int joystick_r_y_pos = 0;

    float l_x_tastgrad = 0.0;
    float l_y_tastgrad = 0.0;
    float r_x_tastgrad = 0.0;
    float r_y_tastgrad = 0.0;

    unsigned int l_x_pwm_wert = 0;
    unsigned int l_y_pwm_wert = 0;
    unsigned int r_x_pwm_wert = 0;
    unsigned int r_y_pwm_wert = 0;  
};

//TODO
void quadcopter_links_abbiegen(unsigned int Dauer){
    quadcopter_print("Biegt nach LINKS... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_rechts_abbiegen(unsigned int Dauer){
    quadcopter_println("Biegt nach RECHTS...");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_vorne(unsigned int Dauer){
    quadcopter_print("Fliegt nach VORNE... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_hinten(unsigned int Dauer){
    quadcopter_print("Fliegt nach HINTEN... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_rechts(unsigned int Dauer){
    quadcopter_print("fliegt nach RECHTS... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_links(unsigned int Dauer){
    quadcopter_print("Fliegt nach LINKS... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_oben(unsigned int Dauer){
    quadcopter_print("Fliegt nach OBEN... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_unten(unsigned int Dauer){
    quadcopter_print("Fliegt nach UNTEN... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_aufhalten(unsigned int Dauer){
    quadcopter_print("HALT AUF... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_aufsetzen(unsigned int Dauer){
    quadcopter_print("SETZT AUF... ");
    quadcopter_verzoegen(Dauer);
    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_verzoegen(unsigned int Dauer){
    delay(Dauer);
};

//TODO
void quadcopter_Debug_Monitor_aktivieren(unsigned long baudrate){
    DEBUG_MONITOR_AKTIVIEREN = true;
    Serial.begin(baudrate);
    Serial.print("Start debugging monitor at baud ");
    Serial.println(baudrate);
};

//TODO
void quadcopter_Debug_Monitor_deaktivieren(){
    DEBUG_MONITOR_AKTIVIEREN = false;
    Serial.end();
};

//TODO
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
        quadcopter_aufhalten(REGLER_HALTVERZOEGERUNG);
        quadcopter_nach_hinten(500);
        quadcopter_aufhalten(REGLER_HALTVERZOEGERUNG);
        quadcopter_nach_rechts(500);
        quadcopter_aufhalten(REGLER_HALTVERZOEGERUNG);
        quadcopter_nach_links(500);
        quadcopter_aufhalten(REGLER_HALTVERZOEGERUNG);
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

//TODO
void quadcopter_Manuellbetrieb(){
    quadcopter_println("__________________________________");
    quadcopter_println("Manuellmodus start");
    quadcopter_println("----------------------------------");
    if (QUADCOPTER_MODUS==MODUS_MANUEL)
    {
        quadcopter_print("Manuellmodus läuft ");
        for (size_t i = 0; i < 5; i++)
        {
            quadcopter_print(".");
            quadcopter_verzoegen(300);
        }
        quadcopter_println();
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

//TODO
void quadcopter_Modus_veraendern(bool Modus){
    QUADCOPTER_MODUS = Modus;
    if (Modus == MODUS_AUTO)
    {
        quadcopter_println("Automodus ist aktiv");
    } else
    {
        quadcopter_println("Manuellmodus ist aktiv");
    }
}
