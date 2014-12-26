#include <RemoteControl.h>
RemoteControl RC;
void setup()
{
    RC.begin();
    Serial.begin(9600);
}

void loop()
{
    if(RC.available())
    {
        Serial.println(RC.getData(),BIN);
    }
}
