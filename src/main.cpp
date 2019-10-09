#include <Arduino.h>
#include "quadcopter.h"

bool DEBUG_MONITOR_AKTIVIEREN = false;
bool QUADCOPTER_MODUS = MODUS_AUTO;

void test1();
void test2();
void test3();

void setup(){
  test1();
  test2();
  test3();
}

void loop() {

}

void test1(){
  quadcopter_Debug_Monitor_aktivieren(9600);
  quadcopter_println("Test 1 start");
  quadcopter_Modus_veraendern(MODUS_AUTO);
  quadcopter_Autobetrieb();
  quadcopter_Modus_veraendern(MODUS_MANUEL);
  quadcopter_Manuellbetrieb();
  quadcopter_println("Test 1 end");
};

void test2(){
  quadcopter_println("Test 2 start");
  quadcopter_Autobetrieb();
  quadcopter_Modus_veraendern(MODUS_MANUEL);
  quadcopter_println("Test 2 end");
};

void test3(){
  quadcopter_println("Test 3 start");
  quadcopter_Debug_Monitor_deaktivieren();
  quadcopter_Manuellbetrieb();
  quadcopter_println("Test 3 end");
};