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

int16_t   ax_raw, ay_raw, az_raw = 0;

String r_x_buffer;
String r_y_buffer;
String empfang_string;
char empfang_char_array[15];

extern bool QUADCOPTER_MODUS;

extern bool DEBUG_MONITOR_AKTIVIEREN;

enum richtung_zustand { standart, vor, vor_brems, vor_halt, vor_halt_nach, 
                                  zurueck, zurueck_brems, zurueck_halt, zurueck_halt_nach,
                                  rechts, rechts_brems, rechts_halt, rechts_halt_nach, 
                                  links, links_brems, links_halt, links_halt_nach};
richtung_zustand richtung;
richtung_zustand richtung_next;

unsigned short auslenkung = 60;
unsigned int auslenkung_dauer = 400;
unsigned int halte_dauer = 500;
unsigned int brems_dauer = 100;

unsigned long letzte_umschalt = 0;

MPU6050 accelgyro;
I2Cdev  I2C_M;

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

    richtung = standart;
};


//TODO
void quadcopter_Debug_Monitor_aktivieren(unsigned long baudrate){
    DEBUG_MONITOR_AKTIVIEREN = true;
    Serial.begin(baudrate);
    //  Serial.print("Start debugging monitor at baud ");
    Serial.println(baudrate);
};

//TODO
void quadcopter_Debug_Monitor_deaktivieren(){
    DEBUG_MONITOR_AKTIVIEREN = false;
    Serial.end();
};

//TODO

void imu_setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  accelgyro.initialize();
  // verify connection
  uint8_t imu_id = accelgyro.getDeviceID();	
	delay(1000);
}

void serial_empfang_neigung() {
  if (Serial.available()) {
    digitalWrite(6, HIGH);
    empfang_string = Serial.readStringUntil('E');
    digitalWrite(6, LOW);
    empfang_string.toCharArray(empfang_char_array, empfang_string.length());
    r_x_buffer = strtok(empfang_char_array, "X");
    r_y_buffer = strtok(NULL, "Y");
    r_x_pwm_wert = byte(r_x_buffer.toInt());
    r_y_pwm_wert = byte(r_y_buffer.toInt());
  }

}

void quadcopter_neigung_betrieb() {
  digitalWrite(8, HIGH);
  accelgyro.getAcceleration(&ax_raw, &ay_raw, &az_raw);
  digitalWrite(8, LOW);
  Serial.println("data," + String(ax_raw) + "," + String(ay_raw) + "," + String(az_raw) + ",");
  if (ax_raw > 7000) {
    digitalWrite(7, HIGH);
  }
  // Joystick Werte ablesen
  joystick_l_x_pos = analogRead(JOYSTICK_LINKS_X_PIN);
  joystick_l_y_pos = analogRead(JOYSTICK_LINKS_Y_PIN);

  // Joystick Werte im Bereich [1,255] quantisieren
  l_x_pwm_wert = map(joystick_l_x_pos, 0, 1023, 0, 255);
  l_y_pwm_wert = map(joystick_l_y_pos, 0, 1023, 0, 255);

  serial_empfang_neigung();

  if (r_x_pwm_wert > 250) {
    digitalWrite(7, LOW);
  }

  analogWrite(JOYSTICK_LINKS_X_PWM_PIN, l_x_pwm_wert);
  analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, l_y_pwm_wert);
  analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, r_x_pwm_wert);
  analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, r_y_pwm_wert);
}

void quadcopter_Autobetrieb(){
    // Debug Monitor Anzeige
    quadcopter_println("__________________________________");
    quadcopter_println("Automodus start");
    quadcopter_println("----------------------------------");

    // LED Betriebsmodusanzeiger
    // digitalWrite(LED_BUILTIN, HIGH);

   // Joystick Werte ablesen
    joystick_l_x_pos = analogRead(JOYSTICK_LINKS_X_PIN);
    joystick_l_y_pos = analogRead(JOYSTICK_LINKS_Y_PIN);

    // Joystick Werte im Bereich [1,255] quantisieren
    l_x_pwm_wert = map(joystick_l_x_pos, 0, 1023, 0, 255);
    l_y_pwm_wert = map(joystick_l_y_pos, 0, 1023, 0, 255);

    richtung_next = richtung;

// ============================= ANFANG SWITCH CASE ======================================

    switch (richtung)
    {

    case standart:
        r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
        r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
        letzte_umschalt = millis();
        richtung_next = vor;
    break;
// ============================= VOR ======================================

    case vor: // nach vorne
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL - REGLER_AUSLENKUNG;
      if(millis()-letzte_umschalt > REGLER_AUSLENKUNGSDAUER) {
        letzte_umschalt = millis();
        richtung_next = vor_halt;
      }
    break;

    case vor_halt:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = vor_brems;
      }
    break;

    case vor_brems:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL + REGLER_AUSLENKUNG;
      if(millis()-letzte_umschalt > REGLER_BREMSDAUER) {
        letzte_umschalt = millis();
        richtung_next = vor_halt_nach;
      }
    break;

    case vor_halt_nach:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = zurueck;
      }
    break;

// ============================= ZURUECK ======================================    

    case zurueck: // nach vorne
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL + REGLER_AUSLENKUNG;
      if(millis()-letzte_umschalt > REGLER_AUSLENKUNGSDAUER) {
        letzte_umschalt = millis();
        richtung_next = zurueck_halt;
      }
    break;

    case zurueck_halt:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = zurueck_brems;
      }
    break;

    case zurueck_brems:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL - REGLER_AUSLENKUNG;
      if(millis()-letzte_umschalt > REGLER_BREMSDAUER) {
        letzte_umschalt = millis();
        richtung_next = zurueck_halt_nach;
      }
    break;

    case zurueck_halt_nach:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = rechts;
      }
    break;

// ============================= RECHTS ======================================    

    case rechts: // nach vorne
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL - REGLER_AUSLENKUNG;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_AUSLENKUNGSDAUER) {
        letzte_umschalt = millis();
        richtung_next = rechts_halt;
      }
    break;

    case rechts_halt:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = rechts_brems;
      }
    break;

    case rechts_brems:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL + REGLER_AUSLENKUNG;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_BREMSDAUER) {
        letzte_umschalt = millis();
        richtung_next = rechts_halt_nach;
      }
    break;

    case rechts_halt_nach:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = links;
      }
    break;

// ============================= LINKS ======================================

    case links: // 
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL + REGLER_AUSLENKUNG;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_AUSLENKUNGSDAUER) {
        letzte_umschalt = millis();
        richtung_next = links_halt;
      }
    break;

    case links_halt:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = links_brems;
      }
    break;

    case links_brems:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL - REGLER_AUSLENKUNG;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_BREMSDAUER) {
        letzte_umschalt = millis();
        richtung_next = links_halt_nach;
      }
    break;

    case links_halt_nach:
      r_x_pwm_wert = REGLER_PWN_R_X_MITTEL;
      r_y_pwm_wert = REGLER_PWN_R_Y_MITTEL;
      if(millis()-letzte_umschalt > REGLER_HALTEDAUER) {
        letzte_umschalt = millis();
        richtung_next = standart;
      }
    break;

    default:
      break;
    }

// ============================= ENDE SWITCH CASE ======================================
    analogWrite(JOYSTICK_LINKS_X_PWM_PIN, l_x_pwm_wert);
    analogWrite(JOYSTICK_LINKS_Y_PWM_PIN, l_y_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_X_PWM_PIN, r_x_pwm_wert);
    analogWrite(JOYSTICK_RECHTS_Y_PWM_PIN, r_y_pwm_wert);
    richtung = richtung_next; 

    // Debug Monitor Anzeige
    quadcopter_println("----------------------------------");
    quadcopter_println("Automodus fertig");
    quadcopter_println("__________________________________");
};


//TODO
void quadcopter_Manuellbetrieb(){
    // Debug Monitor Anzeige
    quadcopter_println("__________________________________");
    quadcopter_println("Manuellmodus start");
    quadcopter_println("----------------------------------");

    // LED Betriebsmodusanzeiger
    // digitalWrite(LED_BUILTIN, LOW);

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

    richtung = standart;

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
