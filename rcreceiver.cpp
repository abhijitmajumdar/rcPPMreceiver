#include "rcreceiver.h"
#include <iostream>
#include <wiringPi.h>

static int lastTime = 0, dTime = 0;
static int channel[nChannels];
static int lastReadChannel[nChannels];
static int counter = 0;

void pinChange(void)
{
	long tempTime = micros();
	dTime = tempTime - lastTime;
	lastTime = tempTime;
	if(dTime>3000)
		counter = 0;
	else
		if(counter<nChannels)
		{
			if((dTime > 2100) || (dTime <100))
				channel[counter] = lastReadChannel[counter];
			else
			{
				channel[counter] = (dTime+5*lastReadChannel[counter])/6;
				lastReadChannel[counter] = channel[counter];
				counter++;
			}
		}
}

void setup(void)
{
	wiringPiSetup();
	wiringPiISR (PPM_PIN, INT_EDGE_RISING, &pinChange);
}

void getData(int *vals)
{
	for(int i=0; i<nChannels;i++)
		vals[i] = channel[i];
}
