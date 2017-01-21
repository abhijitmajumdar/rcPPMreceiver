#ifndef _RCRECEIVER_H
#define _RCRECEIVER_H

// On the TGY-iA6 receiver
#define CH1 1 // Left-Right/Roll
#define CH2 2 // Up-Down/Pitch
#define CH3 3 // Throttle
#define CH4 4 // Yaw
#define CH5 5 // SWC
#define CH6 6 // SWB

#define PPM_PIN 7
#define nChannels 6

void setup(void);
void getData(int *vals);

#endif //_RCRECEIVER_H
