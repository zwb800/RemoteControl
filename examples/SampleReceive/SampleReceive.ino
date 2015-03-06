#include <RemoteControl.h>
RemoteControl RC;
void setup()
{
    RC.begin();
    Serial.begin(115200);
}

void loop()
{
    if(RC.available())
    {
        Serial.println(RC.getData());
    }
}
