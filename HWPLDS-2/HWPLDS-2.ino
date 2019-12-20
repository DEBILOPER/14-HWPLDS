#include "FLOWRATE1.h"
#include "FLOWRATE2.h"
Flowrate1 f;
Flowrate2 ff;

void setup() {
  // put your setup code here, to run once:
f.setup1();
ff.setup2();
}

void loop() {
  // put your main code here, to run repeatedly:
 ff.flr2_loop();
 delay (750);
 f.flr1_loop();
 delay (500);

}
