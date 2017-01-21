#include <iostream>
#include <wiringPi.h>
#include "rcreceiver.h"

using namespace std;

int main(int argc, char **argv) {
	int values[nChannels];
	setup();
	while ( 1 )
	{
		getData(values);
		for(int i=0; i<nChannels;i++)
			cout<<values[i]<<'\t';
		cout<<"\n";
		delay(100);
	}
	return 0;
}
