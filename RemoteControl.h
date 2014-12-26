/*
	RemoteControl.h ����ң�ؿ� ʹ��433 315ģ��ң��PT2262 EV1527

*/
#ifndef RemoteControl_h
#define RemoteControl_h

#include "Arduino.h"

#define REMOTECONTROL_MAX_CHANGE 49
#define TOLERANCE 100;

class RemoteControl
{
public:
	void begin();
	void begin(int num);
	boolean available();
	uint32_t getData();
private:
	static void interrupt();
	static boolean receive();
	static uint8_t timings[REMOTECONTROL_MAX_CHANGE];
	static volatile boolean ready;
	static volatile uint32_t data;
};
#endif
