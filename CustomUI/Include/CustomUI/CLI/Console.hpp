
#pragma once
#include "../Common/Include.hpp"

namespace CustomUI
{
    namespace CLI
    {
        enum ConsoleColor
        {
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Magenta,
            Cyan,
            White,
        };

        class Console
        {
            public:
                Console();
                void log(string Text);
                void logLine(string Text);
                void setColor(ConsoleColor Color);
                void resetColor();
                void clear();
                void refresh();
                void exit();
        };
    }
}