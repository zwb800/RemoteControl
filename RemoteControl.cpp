#include "RemoteControl.h"

volatile boolean RemoteControl::ready;
uint16_t RemoteControl::timings[REMOTECONTROL_MAX_CHANGE+1];
volatile uint32_t RemoteControl::data;


void RemoteControl::begin()
{
	begin(0,3);
}


void RemoteControl::begin(int num,int pinSend)
{
	data = 0;
	ready = false;
	this->pinSend = pinSend;
	pinMode(this->pinSend,OUTPUT);
	
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

	if (length > 13000 && length <16000)//过滤掉过长或过短的脉冲
	{
		
		if (changeIndex == 1+REMOTECONTROL_MAX_CHANGE)//收集到正确的脉冲数 一共有50个脉冲 第一个同步脉冲 48个数据脉冲 最后一个同步脉冲
		{
			
			ready = receive();
		}

		changeIndex = 0;
	}

	if (changeIndex > REMOTECONTROL_MAX_CHANGE)//脉冲数超出 直接返回 等待下次长脉冲
	{
		changeIndex = 100;//附一个无效值
		return;
	}

	timings[changeIndex++] = length;
}

boolean RemoteControl::receive()
{
	int pulseWidth = timings[0] / 31;//脉冲宽度
	int t = TOLERANCE;
	int max1 = t + pulseWidth;
	int min1 = t - pulseWidth;
	int max2 = t + pulseWidth * 3;
	int min2 = t - pulseWidth * 3;

	data = 0;
	
	for (int i = 1; i < REMOTECONTROL_MAX_CHANGE; i+=2)
	{
		int t1 = timings[i];
		int t2 = timings[i+1];		
		
		
		if (t1 < max1 && t1 > min1 &&
			t2 < max2 && t2 > min2)
		{
			//0
		}
		else if (t1 < max2 && t1 > min2 &&
			t2 < max1 && t2 > min1)
		{
			//1
			data|=1;
		}
		else
		{
			//无效
			data = 0;
			break;
		}

		data = data << 1;
	}
	
	data = data >>1;
	
	return data > 0;
}

boolean RemoteControl::available()
{
	return ready;
}

uint32_t RemoteControl::getData()
{
	ready = false;
	return data;
}

void RemoteControl::send(String code)
{
	int pls = 460;
  for(int i=0;i<4;i++)
  {
	  sendSync(pls);
  
      int j = 0;
      char c = code[j++];
      
      while(c!='\0')
      {
          if(c=='0')
          {
             send0(pls);
          }
          else
          {
             send1(pls);
          }
          
          c = code[j++];
      }
	  
  }
}

void RemoteControl::send(uint32_t data)
{
	int len = 24;
	uint32_t data_hi = data >> 15;
	int pls = 460;
  
  for(int i=0;i<4;i++)
  {
	  sendSync(pls);
  
      for(int j= len - 15 - 1;j>-1;j--)
	  {
		  boolean c = (data_hi & (1<<j))>>j;
          if(c==0)
          {
             send0(pls);
          }
          else
          {
             send1(pls);
          }
      }

	  for(int j= 15 - 1;j>-1;j--)
	  {
		boolean c = (data & (1<<j))>>j;
		if(c==0)
        {
             send0(pls);
        }
        else
        {
           send1(pls);
        }
      }
  }
}

void RemoteControl::send0(int pls)
{
		digitalWrite(pinSend,HIGH);
		delayMicroseconds(pls);
		digitalWrite(pinSend,LOW);
		delayMicroseconds(pls*3);
}

void RemoteControl::send1(int pls)
{
		digitalWrite(pinSend,HIGH);
		delayMicroseconds(pls*3);
		digitalWrite(pinSend,LOW);
		delayMicroseconds(pls);
}

void RemoteControl::sendSync(int pls)
{
		digitalWrite(pinSend,HIGH);
		delayMicroseconds(pls);
		digitalWrite(pinSend,LOW);
		delayMicroseconds(pls*31);
}