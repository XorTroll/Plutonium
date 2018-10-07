#include "Console.hpp"

CustomUI::CLI::Console::Console()
{
    gfxExit();
    gfxInitDefault();
    consoleInit(NULL);
}

void CustomUI::CLI::Console::log(string Text)
{
    cout << Text;
}

void CustomUI::CLI::Console::logLine(string Text)
{
    cout << Text << endl;
}

void CustomUI::CLI::Console::setColor(ConsoleColor Color)
{
    switch(Color)
    {
        case ConsoleColor::Black:
            cout << CONSOLE_BLACK;
            break;
        case ConsoleColor::Red:
            cout << CONSOLE_RED;
            break;
        case ConsoleColor::Green:
            cout << CONSOLE_GREEN;
            break;
        case ConsoleColor::Yellow:
            cout << CONSOLE_YELLOW;
            break;
        case ConsoleColor::Blue:
            cout << CONSOLE_BLUE;
            break;
        case ConsoleColor::Magenta:
            cout << CONSOLE_MAGENTA;
            break;
        case ConsoleColor::Cyan:
            cout << CONSOLE_CYAN;
            break;
        case ConsoleColor::White:
            cout << CONSOLE_WHITE;
            break;
    }
}

void CustomUI::CLI::Console::resetColor()
{
    cout << CONSOLE_RESET;
}

void CustomUI::CLI::Console::clear()
{
    consoleClear();
}

void CustomUI::CLI::Console::refresh()
{
    gfxFlushBuffers();
    gfxSwapBuffers();
}

void CustomUI::CLI::Console::exit()
{
    gfxExit();
}