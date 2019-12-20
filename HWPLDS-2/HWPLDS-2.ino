#include "FLOWRATE1.h"
#include "FLOWRATE2.h"
Flowrate1 f;
Flowrate2 ff;

int fr1, fr2;
void setup() {  // put your setup code here, to run once:
f.setup1();
ff.setup2();
}

void loop() {
    fr2 = ff.flr2_loop();
    fr1 = f.flr1_loop();
    Serial.print("Flowrate 2: ");
    Serial.print(fr2);   // Print the integer part of the variable
    Serial.print("L/min "); 
    Serial.print(" | ");            // Print tab space
    delay (750);
    Serial.print("Flowrate 1: ");
    Serial.print(fr1);    // Print the integer part of the variable
    Serial.println("L/min "); 
    delay (500);

}
