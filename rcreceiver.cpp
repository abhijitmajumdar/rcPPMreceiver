#include "rcreceiver.h"
#include <iostream>
#include <wiringPi.h>
#define nMovingAverage 30

static int lastTime = 0, dTime = 0;
static int channel[nChannels];
static int lastReadChannel[nChannels][nMovingAverage];
static int lastReadChannelIndexes[nChannels] = {0};
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
			if((dTime < 2100) && (dTime > 100))
			{
				lastReadChannel[counter][lastReadChannelIndexes[counter]++] = dTime;
				if(lastReadChannelIndexes[counter] >= nMovingAverage)
					lastReadChannelIndexes[counter] = 0;
			}
			counter++;
		}
}

void setup(void)
{
	wiringPiSetup();
	wiringPiISR (PPM_PIN, INT_EDGE_RISING, &pinChange);
}

void getData(int *vals)
{
	for(int j=0; j<nChannels;j++)
	{
		for(int i=0; i<nMovingAverage; i++)
			channel[j] += lastReadChannel[j][i];
		channel[j] /= nMovingAverage;
		vals[j] = (6*vals[j]+channel[j])/7;
	}
}
