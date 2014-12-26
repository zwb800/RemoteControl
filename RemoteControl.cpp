#include "RemoteControl.h"

volatile boolean RemoteControl::ready;
uint8_t RemoteControl::timings[REMOTECONTROL_MAX_CHANGE];
volatile uint32_t RemoteControl::data;


void RemoteControl::begin()
{
	begin(0);
}


void RemoteControl::begin(int num)
{
	data = 0;
	ready = false;

	attachInterrupt(num, interrupt, CHANGE);
}

void RemoteControl::interrupt()
{
	static uint8_t changeIndex = 0;
	static unsigned long lastTime = 0;

	if (ready)
	{
		return;
	}

	unsigned long now = micros();
	unsigned int length = now - lastTime;
	lastTime = now;

	if (length > 8000 && length <20000)//���˵���������̵�����
	{
		if (changeIndex == REMOTECONTROL_MAX_CHANGE)//�ռ�����ȷ��������
		{
			ready = receive();
		}

		changeIndex = 0;
	}

	if (changeIndex >= REMOTECONTROL_MAX_CHANGE)//���������� ֱ�ӷ��� �ȴ��´γ�����
	{
		changeIndex = 1000;//��һ����Чֵ
		return;
	}

	timings[changeIndex++] = length;
}

boolean RemoteControl::receive()
{
	uint8_t pulseWidth = timings[0] / 31;//������
	uint8_t max1 = TOLERANCE + pulseWidth;
	uint8_t min1 = TOLERANCE - pulseWidth;
	uint8_t max2 = TOLERANCE + pulseWidth * 3;
	uint8_t min2 = TOLERANCE - pulseWidth * 3;

	for (int i = 0; i < REMOTECONTROL_MAX_CHANGE; i+=2)
	{
		uint8_t t1 = timings[i];
		uint8_t t2 = timings[i+1];		

		if (t1 < max1 && t1 > min1 &&
			t2 < max2 && t2 > min2)
		{
			//0
		}
		else if (t1 < max2 && t1 > min2 &&
			t2 < max1 && t2 > min1)
		{
			//1
			data |= 1;
		}
		else
		{
			//��Ч
			data = 0;
			break;
		}

		data = data << 1;
	}

	return data > 0;
}

boolean RemoteControl::available()
{
	return ready;
}

uint32_t RemoteControl::getData()
{
	return data;
}