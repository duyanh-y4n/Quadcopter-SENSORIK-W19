// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project

// Ausreißer definieren:
//    - Alles mit über ein G in eine Richtung
//    - Unterschied zwischen zwei aufeinander folgenden Werten von mehr als ein definierter Wert

#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>

#define ERDBESCHL_ROH 8192
#define MAX_SPRUNG 1024

// ------------ Globale Variablen für Rohdaten, Konvertierte Daten und Gefilterte Daten
int16_t   ax_raw, ay_raw, az_raw = 0;
int16_t   ax_raw_alt, ay_raw_alt, az_raw_alt = 0;
float     ax_g,   ay_g,   az_g = 0.0;
int16_t   dx_raw, dy_raw, dz_raw = 0;   // Drehratensensor
float     dx_degs, dy_degs, dz_degs = 0;  // Drehratensensor in deg/s
float     dx_winkel, dy_winkel, dz_winkel = 0;  // Winkel aus Integration der Drehrate

float gyro_faktor = float(500.0 / 32768.0);

float dauer = 0.0;
unsigned long last_timestamp = 0;
float     rollen_grad, nicken_grad = 0.0;

float kompl_alpha = 0.8;
float kompl_beta = 1- kompl_alpha;

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69

MPU6050 accelgyro;
I2Cdev  I2C_M;

// Ausreißer werden erkannt, wenn der Unterschied zw. zwei aufeinander folgenden Messwerten zu groß ist
// oder wenn auf einer Achse mehr als ein g gemessen wird
void filter_convert_data() {
  if (abs(ax_raw - ax_raw_alt) < MAX_SPRUNG) {
    ax_g = (float) ax_raw / 16384.0;
  } else {
    ax_g = (float) ax_raw_alt / 16384.0;
  }
  if (abs(ay_raw - ay_raw_alt) < MAX_SPRUNG) {
    ay_g = (float) ay_raw / 16384.0;
  } else {
    ay_g = (float) ay_raw_alt / 16384.0;
  }
  if (abs(az_raw - az_raw_alt) < MAX_SPRUNG) {
    az_g = (float) az_raw / 16384.0;
  } else {
    az_g = (float) az_raw_alt / 16384.0;
  }
  ax_g = constrain(ax_g, -1, 1);
  ay_g = constrain(ay_g, -1, 1);
  az_g = constrain(az_g, -1, 1);
}

void get_gyro_data(void) {
  accelgyro.getRotation(&dx_raw, &dy_raw, &dz_raw);
  dx_degs = (float(dx_raw)) * gyro_faktor;
  dy_degs = (float(dy_raw)) * gyro_faktor;
  dz_degs = (float(dz_raw)) * gyro_faktor;
  dx_winkel += dx_degs * dauer;
  dy_winkel += dy_degs * dauer;
  dz_winkel += dz_degs * dauer;
}

void get_accel_data(void) {
  static bool erster_durchlauf = true;

  // aktuelle Messdaten im Roh-Format einlesen
  accelgyro.getAcceleration(&ax_raw, &ay_raw, &az_raw);

  // im ersten Schleifendurchlauf werden die "alten" Messwerte gleich "aktuellen" initialisiert
  if(erster_durchlauf) {
    ax_raw_alt = ax_raw;
    ay_raw_alt = ay_raw;
    az_raw_alt = az_raw;
    erster_durchlauf = false;
  }

  // Filterung und Konvertierung erfolgt durch Vergleich aktueller und "alter" Messwerte
  filter_convert_data();

  // "alte" Messwerte aktualisieren
  ax_raw_alt = ax_raw;
  ay_raw_alt = ay_raw;
  az_raw_alt = az_raw;
}

void winkel_berechnen(float ax_g, float ay_g, float az_g) {
  nicken_grad = -(atan2(ay_g, az_g) * 57.3);
  rollen_grad = atan2((-ax_g), sqrt(ay_g * ay_g + az_g * az_g)) * 57.3;
}

void plot_data() {
  Serial.print(nicken_grad);
  Serial.print(",");
  Serial.println(-(dx_winkel));
}

void setup_imu() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  accelgyro.initialize();
  // verify connection
  uint8_t imu_id = accelgyro.getDeviceID();
  delay(1000);
}

void daten_senden_raspi() {
  Serial.println("data,"  + String(ax_raw) + "," + String(ay_raw) + "," + String(az_raw) + "," 
                          + String(dx_raw) + "," + String(dy_raw) + "," + String(dz_raw));
}

void setup() {
  
  Serial.begin(115200);

  setup_imu();
}

void komplFilt() {
  
}

void loop() 
{ 
  dauer = (float(millis() - last_timestamp)) / 1000.0;
  last_timestamp = millis();
  get_accel_data();
  get_gyro_data();
  winkel_berechnen(ax_g, ay_g, az_g);
//  plot_data();
  daten_senden_raspi();
}
