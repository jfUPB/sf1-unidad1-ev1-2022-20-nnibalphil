#include <Arduino.h>
#include "task2.h"
#include "events.h"

void task2()
{
    enum class TaskState
    {
        INIT,
        WAIT_PRESS,
        WAIT_STABLE,
        WAIT_RELEASE
    };
    static TaskState taskState = TaskState::INIT;
    static uint8_t lastButtonPressed;
    static uint32_t initStableTime;

    const uint8_t Boton1_PIN = 12;
    const uint8_t Boton2_PIN = 13;
    const uint32_t STABLE_TIME = 100;

    switch (taskState)
    {
    case TaskState::INIT:
    {
        pinMode(Boton1_PIN, INPUT_PULLUP);
        pinMode(Boton2_PIN, INPUT_PULLUP);
        taskState = TaskState::WAIT_PRESS; 
        break;
    }
    case TaskState::WAIT_PRESS:
    {
        if(digitalRead(Boton1_PIN) == LOW){
            lastButtonPressed = Boton1_PIN;
            initStableTime = millis();
            taskState = TaskState::WAIT_STABLE;
        }
        if(digitalRead(Boton2_PIN) == LOW){
            lastButtonPressed = Boton2_PIN;
            initStableTime = millis();
            taskState = TaskState::WAIT_STABLE;
        }

        break;
    }
    case TaskState::WAIT_STABLE:
    {
        if(digitalRead(lastButtonPressed) != LOW){
            taskState = TaskState::WAIT_PRESS;
        }
        else if ( (millis() - initStableTime) > STABLE_TIME){
            if(lastButtonPressed == Boton1_PIN) buttonEvt.whichButton = BUTTONS::Boton1;
            else if(lastButtonPressed == Boton2_PIN) buttonEvt.whichButton = BUTTONS::Boton2;
            buttonEvt.trigger = true;
            printf("Button pressed: %d\n", lastButtonPressed);
            taskState = TaskState::WAIT_RELEASE;
        }
        break;
    }
    case TaskState::WAIT_RELEASE:{
        if(digitalRead(lastButtonPressed) == HIGH){
            taskState = TaskState::WAIT_PRESS;
        }
        break;
    }

    default:
    {
    }
    }
}
