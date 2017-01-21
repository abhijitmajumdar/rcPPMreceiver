CC=g++
INCLUDE = -I/usr/local/include
CFLAGS = -pipe -O2 -Wall -W $(INCLUDE) -std=c++11
LDFLAGS = -L/usr/local/lib -L/usr/lib/arm-linux-gnueabihf
LDLIBS = -lwiringPi -lwiringPiDev -lwiringPiPca9685 -lRTIMULib -lpthread

all: mainExecutable

mainExecutable: main.o rcreceiver.o
	$(CC) -o mainExecutable.out main.o rcreceiver.o $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CC) -c -o main.o main.cpp $(CFLAGS)
	
rcreceiver.o: rcreceiver.cpp
	$(CC) -c -o rcreceiver.o rcreceiver.cpp $(CFLAGS)

clean:
	rm main.o rcreceiver.o mainExecutable.out
