#include <iostream>
#include <wiringPi.h>
#include "rcreceiver.h"

using namespace std;

int main(int argc, char **argv) {
	int values[nChannels];
	setup();
	while ( 1 )
	{
		long time = micros();
		getData(values);
		cout<<micros()-time<<"\n";
		for(int i=0; i<nChannels;i++)
			cout<<values[i]<<'\t';
		cout<<"\n";
		delay(20);
	}
	return 0;
}
