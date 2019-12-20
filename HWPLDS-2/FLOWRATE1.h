byte statusLed    = 13;
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;
float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;

class Flowrate1{
  public:
    int flr1_loop();
    static void pulseCounter();
    void setup1();
  };
  
void Flowrate1::setup1()
{  
  Serial.begin(9600);
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

int Flowrate1::flr1_loop()
{
   
   if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
    detachInterrupt(sensorInterrupt);

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    oldTime = millis();
    flowMilliLitres = (flowRate / 60) * 1000;
    totalMilliLitres += flowMilliLitres;
      
      unsigned int frac;
//      Serial.print(int(flowRate));  // Print the integer part of the variable
//      Serial.print("L/min ");       
//    Serial.print(totalMilliLitres);
//    Serial.println("mL"); 
 
    pulseCount = 0;
 
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    return int(flowRate);
  }
     
}

static void Flowrate1::pulseCounter()
{
  pulseCount++;
}
