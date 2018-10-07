#include <CustomUI/CustomUI.hpp>
using namespace CustomUI;
using namespace CustomUI::CLI;

int main()
{
    Console console;
    console.log("Hey, this is CustomUI!");
    console.logLine(" - we're still on the same line");
    console.logLine("Now we're on a new line!");
    console.setColor(ConsoleColor::Blue);
    console.logLine("Blue feels good!");
    while(appletMainLoop()) console.refresh();
    console.exit();
    return 0;
}