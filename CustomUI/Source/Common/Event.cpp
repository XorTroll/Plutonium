#include "Event.hpp"

extern u64 idown;
extern u64 iup;
extern u64 iheld;

CustomUI::Event::Event(CustomUI::EventType CallingType)
{
    this->type = CallingType;
    if((CallingType == EventType::KeyDown) || (CallingType == EventType::KeyUp) || (CallingType == EventType::KeyHeld)) hidScanInput();
}

CustomUI::EventType CustomUI::Event::getType()
{
    return this->type;
}

u64 CustomUI::Event::keyDown()
{
    return idown;
}

u64 CustomUI::Event::keyUp()
{
    return iup;
}

u64 CustomUI::Event::keyHeld()
{
    return iheld;
}

CustomUI::OperationMode CustomUI::Event::currentMode()
{
    return (OperationMode)appletGetOperationMode();
}