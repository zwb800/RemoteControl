#include <RemoteControl.h>
RemoteControl RC;
void setup()
{
    RC.begin();
    Serial.begin(9600);
    pinMode(13,OUTPUT);
}

void loop()
{
    if(RC.available())
    {
        Serial.println(RC.getData());
    }
}
