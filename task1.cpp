#include <Arduino.h>
#include "task1.h"
#include "events.h"

void task1()
{
    enum class TaskState
    {
        INIT,
        WAIT_COMMANDS
    };
    static TaskState taskState = TaskState::INIT;

    switch (taskState)
    {
    case TaskState::INIT:
    {
        Serial.begin(115200);
        taskState = TaskState::WAIT_COMMANDS;
        break;
    }
    case TaskState::WAIT_COMMANDS:
    {
        if (Serial.available() > 0)
        {
            int dataRx = Serial.read();
            if (dataRx == 'u')
            {
                Serial.print("Boton1\n");
                buttonEvt.trigger = true;
                buttonEvt.whichButton = BUTTONS::Boton1;
            }
            if (dataRx == 'd')
            {
                Serial.print("Boton2\n");
                buttonEvt.trigger = true;
                buttonEvt.whichButton = BUTTONS::Boton2;
            }
        }
        break;
    }
    default:
    {
    }
    }
}
