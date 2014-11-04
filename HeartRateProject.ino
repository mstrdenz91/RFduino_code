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

const int ledPinGreen = 3;
int ledState = LOW;

void setup() 
{
  //interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
  interruptSetup();
  pinMode(ledPinGreen, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:

}


