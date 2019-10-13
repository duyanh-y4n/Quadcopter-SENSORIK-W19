#include "quadcopter.h"

unsigned int joystick_l_x_pos;
unsigned int joystick_l_y_pos;
unsigned int joystick_r_x_pos;
unsigned int joystick_r_y_pos;

float l_x_tastgrad;
float l_y_tastgrad;
float r_x_tastgrad;
float r_y_tastgrad;

unsigned int l_x_pwm_wert;
unsigned int l_y_pwm_wert;
unsigned int r_x_pwm_wert;
unsigned int r_y_pwm_wert;

bool QUADCOPTER_MODUS;

bool DEBUG_MONITOR_AKTIVIEREN;

//TODO
void quadcopter_hardware_init(){
    pinMode(modus_wahl_pin, INPUT_PULLUP);
    pinMode(l_x_pwm_pin, OUTPUT);
    pinMode(l_y_pwm_pin, OUTPUT);
    pinMode(r_x_pwm_pin, OUTPUT);
    pinMode(r_y_pwm_pin, OUTPUT);
    analogReference(EXTERNAL);
};

void quadcopter_software_init(){
    DEBUG_MONITOR_AKTIVIEREN = false;
    QUADCOPTER_MODUS = MODUS_MANUEL;

    joystick_l_x_pos = 0;
    joystick_l_y_pos = 0;
    joystick_r_x_pos = 0;
    joystick_r_y_pos = 0;

    l_x_tastgrad = 0.0;
    l_y_tastgrad = 0.0;
    r_x_tastgrad = 0.0;
    r_y_tastgrad = 0.0;

    l_x_pwm_wert = 0;
    l_y_pwm_wert = 0;
    r_x_pwm_wert = 0;
    r_y_pwm_wert = 0;  
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
    QUADCOPTER_MODUS = MODUS_AUTO;

    // Debug Monitor Anzeige
    quadcopter_println("__________________________________");
    quadcopter_println("Automodus start");
    quadcopter_println("----------------------------------");

    // LED Betriebsmodusanzeiger
    digitalWrite(LED_BUILTIN, HIGH);

    // Autobetriebssequenz
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

    // Debug Monitor Anzeige
    quadcopter_println("----------------------------------");
    quadcopter_println("Automodus fertig");
    quadcopter_println("__________________________________");
};

//TODO
void quadcopter_Manuellbetrieb(){
    QUADCOPTER_MODUS = MODUS_MANUEL;

    // Debug Monitor Anzeige
    quadcopter_println("__________________________________");
    quadcopter_println("Manuellmodus start");
    quadcopter_println("----------------------------------");

    // LED Betriebsmodusanzeiger
    digitalWrite(LED_BUILTIN, LOW);

    // Poti Werte ablesen
    joystick_l_x_pos = analogRead(l_x_pin);
    joystick_l_y_pos = analogRead(l_y_pin);
    joystick_r_x_pos = analogRead(r_x_pin);
    joystick_r_y_pos = analogRead(r_y_pin);

    // Poti Werte im Bereich [1,255] quantisieren
    l_x_pwm_wert = map(joystick_l_x_pos, 0, 1023, 0, 255);
    l_y_pwm_wert = map(joystick_l_y_pos, 0, 1023, 0, 255);
    r_x_pwm_wert = map(joystick_r_x_pos, 0, 1023, 0, 255);
    r_y_pwm_wert = map(joystick_r_y_pos, 0, 1023, 0, 255);

    // Tastgrad auswerten
    l_x_tastgrad = (float)joystick_l_x_pos / 1024.0;
    l_y_tastgrad = (float)joystick_l_y_pos / 1024.0;
    r_x_tastgrad = (float)joystick_r_x_pos / 1024.0;
    r_y_tastgrad = (float)joystick_r_y_pos / 1024.0;

    // Output Analogsignal zur RCU
    analogWrite(l_x_pwm_pin, l_x_pwm_wert);
    analogWrite(l_y_pwm_pin, l_y_pwm_wert);
    analogWrite(r_x_pwm_pin, r_x_pwm_wert);
    analogWrite(r_y_pwm_pin, r_y_pwm_wert);

    // Debug Monitor Anzeige
    quadcopter_println( "Links  X  "      + String(l_x_pwm_wert) 
      + "\t \t" +   "Links  Y  "      + String(l_y_pwm_wert) 
      + "\t \t" +   "Rechts X  "      + String(r_x_pwm_wert)
      + "\t \t" +   "Rechts Y  "      + String(r_y_pwm_wert));
    quadcopter_println("----------------------------------");
    quadcopter_println("Manuellmodus fertig");
    quadcopter_println("__________________________________");
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
