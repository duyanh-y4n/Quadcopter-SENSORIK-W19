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
    pinMode(MODUS_WAHL_PIN, INPUT_PULLUP);
    pinMode(JOYSTICK_LINKS_X_PWM_PIN, OUTPUT);
    pinMode(JOYSTICK_LINKS_Y_PWM_PIN, OUTPUT);
    pinMode(JOYSTICK_RECHTS_X_PWM_PIN, OUTPUT);
    pinMode(JOYSTICK_RECHTS_Y_PWM_PIN, OUTPUT);
    analogReference(EXTERNAL);
};

/**
 * @brief Software initialization: Variablen mit Standardwerte initialisieren
 * @addtogroup SOFTWARE_INIT
 */
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

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_ROTATION_VERTICAL_LINKS);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_rechts_abbiegen(unsigned int Dauer){
    quadcopter_println("Biegt nach RECHTS...");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_ROTATION_VERTICAL_RECHTS);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_vorne(unsigned int Dauer){
    quadcopter_print("Fliegt nach VORNE... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_HORIZONTAL_OUTPUT_PIN, REGLER_PWM_RECHTS);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_hinten(unsigned int Dauer){
    quadcopter_print("Fliegt nach HINTEN... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_ROTATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_HINTEN);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_rechts(unsigned int Dauer){
    quadcopter_print("fliegt nach RECHTS... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_HORIZONTAL_LR_OUTPUT_PIN, REGLER_PWM_RECHTS);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_links(unsigned int Dauer){
    quadcopter_print("Fliegt nach LINKS... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_HORIZONTAL_LR_OUTPUT_PIN, REGLER_PWM_RECHTS);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_oben(unsigned int Dauer){
    quadcopter_print("Fliegt nach OBEN... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_OBEN);
    // quadcopter_verzoegern(Dauer/2);
    // analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWN_L_Y_STABIL);
    quadcopter_verzoegern(Dauer/2);
    

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_nach_unten(unsigned int Dauer){
    quadcopter_print("Fliegt nach UNTEN... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_UNTEN);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_aufhalten(unsigned int Dauer){
    quadcopter_print("HALT AUF... ");

    // Output Analogsignal zur RCU
    analogWrite(JOYSTICK_LINKS_X_PWM_PIN, REGLER_PWN_L_X_MITTEL);
    analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, REGLER_PWN_L_Y_STABIL);
    analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, REGLER_PWN_R_X_MITTEL);
    analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, REGLER_PWN_R_Y_MITTEL);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_aufsetzen(unsigned int Dauer){
    quadcopter_print("SETZT AUF... ");

    // Output Analogsignal zur RCU
    analogWrite(PWM_TRANSLATION_VERTICAL_OUTPUT_PIN, REGLER_PWM_UNTEN);
    quadcopter_verzoegern(Dauer);

    quadcopter_print("Fertig (nach ");
    quadcopter_print(Dauer);
    quadcopter_println(" ms)");
};

//TODO
void quadcopter_verzoegern(unsigned int Dauer){
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
    quadcopter_aufhalten(REGLER_HALTEDAUER);
    quadcopter_nach_hinten(500);
    quadcopter_aufhalten(REGLER_HALTEDAUER);
    quadcopter_nach_rechts(500);
    quadcopter_aufhalten(REGLER_HALTEDAUER);
    quadcopter_nach_links(500);
    quadcopter_aufhalten(REGLER_HALTEDAUER);
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

    // Joystick Werte ablesen
    joystick_l_x_pos = analogRead(JOYSTICK_LINKS_X_PIN);
    joystick_l_y_pos = analogRead(JOYSTICK_LINKS_Y_PIN);
    joystick_r_x_pos = analogRead(JOYSTICK_RECHTS_X_PIN);
    joystick_r_y_pos = analogRead(JOYSTICK_RECHTS_Y_PIN);

    // Joystick Werte im Bereich [1,255] quantisieren
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
    analogWrite(JOYSTICK_LINKS_X_PWM_PIN, l_x_pwm_wert);
    analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, l_y_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, r_x_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, r_y_pwm_wert);

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
