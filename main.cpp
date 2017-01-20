#include <iostream>
#include <wiringPi.h>

#define INTPIN 7
#define channumber 6

using namespace std;

// On the TGY-iA6 receiver
// CH1 = Left-Right/Roll
// CH2 = Up-Down/Pitch
// CH3 = Throttle
// CH4 = Yaw
// CH5 = SWC
// CH6 = SWB

volatile int changeTime = 0, lastTime = 0;
volatile int channel[channumber];
volatile int lastReadChannel[channumber];

long pulseIn(int pin, bool state)
{
	while(digitalRead(pin) != state);
	long timeBegin = micros();
	while(digitalRead(pin) == state);
	return (micros()-timeBegin);
}

void printRC(int pin)
{
	if(pulseIn(pin, HIGH) > 3000) //If pulse > 3000 useconds
	{ 
	   for(int i = 0; i < channumber; i++) //Read the pulses of the channels
	   {
		 channel[i]=pulseIn(pin, HIGH);
	   }
	   for(int i = 0; i < channumber; i++) //Average the pulses
	   {
		 if((channel[i] > 2000) || (channel[i] <100))//If channel is out of range, change the value to the previous value
		 {
		  channel[i]= lastReadChannel[i]; 
		 }
		 else
		 { 
		 channel[i]=(lastReadChannel[i]+channel[i])/2; // else average the pulse with the current pulse
		 }
	   }
	   for(int i=0; i<channumber;i++)
	   {
		 cout<<channel[i]<<'\t';
	   }
	   cout<<"\n";
	}
}

int main(int argc, char **argv) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      cout<<"Unable to setup wiringPi\n";
      return 1;
  }
  cout<<"Setup done\n";

  // display counter value every second.
  while ( 1 )
  {
	  printRC(INTPIN);
  }

  return 0;
}
