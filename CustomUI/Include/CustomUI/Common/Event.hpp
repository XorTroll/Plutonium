
#pragma once
#include "Include.hpp"
#include "Basic.hpp"

namespace CustomUI
{
    enum class EventType
    {
        Initialize,
        Exit,
        KeyDown,
        KeyUp,
        KeyHeld,
        ChangedToHandHeld,
        ChangedToDocked,
        Draw,
        JoyConAttach,
        JoyConDetach,
    };

    class Event
    {
        public:
            Event(EventType CallingType);
            EventType getType();
            u64 keyDown();
            u64 keyUp();
            u64 keyHeld();
            OperationMode currentMode();
        private:
            EventType type;
    };
}