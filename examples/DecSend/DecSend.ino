#include <RemoteControl.h>
RemoteControl RC;


void setup()
{
   RC.begin();
   Serial.begin(115200);
}

void loop()
{
  if(Serial.available())
  {
    uint32_t data =   0;
    char buf[6];
      buf[5] = '\0';
      Serial.readBytes(buf,5);
      
      data = atoi(buf);
      data = data * 1000;
      char b[4];
      b[3] = '\0';
      Serial.readBytes(b,3);
      data = data + atoi(b);
    Serial.println(data);
      RC.send(data);
      while(Serial.read()>0){}
  }
}

