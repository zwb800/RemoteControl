/*
	RemoteControl.h 无线遥控库 使用433 315模块遥控PT2262 EV1527

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
	void begin(int num,int pinSend);
	boolean available();
	uint32_t getData();
	void send(String code);
	void send(uint32_t data);
private:
	static void interrupt();
	static boolean receive();
	static uint16_t timings[1+REMOTECONTROL_MAX_CHANGE];
	static volatile boolean ready;
	static volatile uint32_t data;
	void send0(int pls);
	void send1(int pls);
	void sendSync(int pls);
	int pinSend;
};
#endif
