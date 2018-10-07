#include "Event.hpp"

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
    return hidKeysDown(CONTROLLER_P1_AUTO);
}

u64 CustomUI::Event::keyUp()
{
    return hidKeysUp(CONTROLLER_P1_AUTO);
}

u64 CustomUI::Event::keyHeld()
{
    return hidKeysHeld(CONTROLLER_P1_AUTO);
}

CustomUI::OperationMode CustomUI::Event::currentMode()
{
    return (OperationMode)appletGetOperationMode();
}