/*
Pulse Sensor purple wire goes to Analog Pin 0.
Pulse Sensor sample aquisition and processing happens in the background via Timer 2 interrupt. 500Hz sample rate.
PWM on pins 3 and 11 will not work when using this code, because we are using Timer 2!
The following variables are automatically updated:
Signal :    int that holds the analog signal data straight from the sensor. updated every 2mS.
IBI  :      int that holds the time interval between beats. 2mS resolution.
BPM  :      int that holds the heart rate value, derived every beat, from averaging previous 10 IBI values.
QS  :       boolean that is made true whenever Pulse is found and BPM is updated. User must reset.
Pulse :     boolean that is true when a heartbeat is sensed then false in time with pin13 LED going out.
*/

#include <RFduinoBLE.h>

//  VARIABLES:
const int pulsePin = 2;        // Pulse Sensor purple wire connected to analog pin 1
const int ledPinGreen = 3;     
int ledState = LOW;

// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM = 0;               // used to hold the pulse rate
volatile int Signal = 0;            // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

void setup() 
{              
  pinMode(ledPinGreen, OUTPUT);
  interruptSetup(); // sets up to read Pulse Sensor signal every 2ms 
  
//  Serial.begin(115200);             // we agree to talk fast!
  Serial.begin(9600);
  
  RFduinoBLE.advertisementData = "heartrate";

  RFduinoBLE.begin();    // start the BLE stack
}

void loop() 
{
  sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true) // Quantified Self flag is true when arduino finds a heartbeat
  {        
    sendDataToProcessing('B',BPM);   // send heart rate with a 'B' prefix
    sendDataToProcessing('Q',IBI);   // send time between beats with a 'Q' prefix
    RFduinoBLE.send( BPM );
    QS = false;                      // reset the Quantified Self flag for next time   
  }
  delay( 20 );                             //  take a break
}

void sendDataToProcessing( char symbol, int data )
{
    Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
    Serial.println(data);                // the data to send culminating in a carriage return
}

