#include <RemoteControl.h>
RemoteControl RC;
void setup()
{
   RC.begin();
   Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
      char code[24];
      Serial.readBytes(code,24);
    
      while(Serial.read()>0){}
      RC.send(code);
  }
}
