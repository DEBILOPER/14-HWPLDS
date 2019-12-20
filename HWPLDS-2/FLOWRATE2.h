/*
Liquid flow rate sensor -DIYhacking.com Arvind Sanjeev

Measure the liquid/water flow rate using this code. 
Connect Vcc and Gnd of sensor to arduino, and the 
signal line to arduino digital pin 2.
 
 */

byte statusLed1    = 13;
byte sensorInterrupt1 = 0;  // 0 = digital pin 2
byte sensorPin1       = 2;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor1 = 4.5;
volatile byte pulseCount1;  
float flowRate1;
unsigned int flowMilliLitres1;
unsigned long totalMilliLitres1;
unsigned long oldTime1;

class Flowrate2{
  public:
    void flr2_loop();
    static void pulseCount1er();
    void setup2();
  };


  
void Flowrate2::setup2()
{  
  // Initialize a serial connection for reporting values to the host
  Serial.begin(9600);
   
  // Set up the status LED line as an output
  pinMode(statusLed1, OUTPUT);
  digitalWrite(statusLed1, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin1, INPUT);
  digitalWrite(sensorPin1, HIGH);

  pulseCount1        = 0;
  flowRate1          = 0.0;
  flowMilliLitres1   = 0;
  totalMilliLitres1  = 0;
  oldTime1           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt1, pulseCount1er, FALLING);
}

/**
 * Main program loop
 */
void Flowrate2::flr2_loop()
{
   
   if((millis() - oldTime1) > 1000)    // Only process counters once per second
  { 
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt1);
        
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor1 to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate1 = ((1000.0 / (millis() - oldTime1)) * pulseCount1) / calibrationFactor1;
    
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime1 = millis();
    
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres1 = (flowRate1 / 60) * 1000;
    
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres1 += flowMilliLitres1;
      
    unsigned int frac;
    
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate1));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space

    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres1);
    Serial.println("mL"); 
    Serial.print("\t");       // Print tab space
    Serial.print(totalMilliLitres1/1000);
    Serial.print("L");
    

    // Reset the pulse counter so we can start incrementing again
    pulseCount1 = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt1, pulseCount1er, FALLING);
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
