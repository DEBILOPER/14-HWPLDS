byte statusLed1    = 13;
byte sensorInterrupt1 = 0;  // 0 = digital pin 2
byte sensorPin1       = 3;

float calibrationFactor1 = 4.5;
volatile byte pulseCount1;  
float flowRate1;
unsigned int flowMilliLitres1;
unsigned long totalMilliLitres1;
unsigned long oldTime1;

class Flowrate2{
  public:
    float flr2_loop();
    static void pulseCount1er();
    void setup2();
  };


  
void Flowrate2::setup2()
{  
  Serial.begin(9600);
  pinMode(statusLed1, OUTPUT);
  digitalWrite(statusLed1, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin1, INPUT);
  digitalWrite(sensorPin1, HIGH);

  pulseCount1        = 0;
  flowRate1          = 0.0;
  flowMilliLitres1   = 0;
  totalMilliLitres1  = 0;
  oldTime1           = 0;

  attachInterrupt(sensorInterrupt1, pulseCount1er, FALLING);
}

float Flowrate2::flr2_loop()
{
   
   if((millis() - oldTime1) > 1000)    // Only process counters once per second
  { 

    detachInterrupt(sensorInterrupt1);

    flowRate1 = ((1000.0 / (millis() - oldTime1)) * pulseCount1) / calibrationFactor1;

    oldTime1 = millis();

    flowMilliLitres1 = (flowRate1 / 60) * 1000;
    
    totalMilliLitres1 += flowMilliLitres1;
      
    unsigned int frac;
   
//    Serial.print(int(flowRate1));  // Print the integer part of the variable
//    Serial.print("L/min");
//    Serial.print(" | ");       // Print tab space
    
    pulseCount1 = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt1, pulseCount1er, FALLING);
    return flowRate1;
  }
 
}

/*
Insterrupt Service Routine
 */
static void Flowrate2::pulseCount1er()
{
  // Increment the pulse counter
  pulseCount1++;
}
