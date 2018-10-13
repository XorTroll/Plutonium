#include <CustomUI/CustomUI.hpp>
using namespace CustomUI;
using namespace CustomUI::GUI;

int main()
{
    Color mainw_accent = { 51, 153, 255, 255 };
    Color mainw_text = { 10, 10, 10, 255 };
    Color mainw_border = { 33, 33, 33, 255 };
    Color mainw_background = { 255, 255, 255, 255 };
    WindowDesign mainw_design = { Background(mainw_background), mainw_accent, mainw_text, mainw_border };
    Window mainw("Hello from CustomUI GUI!", mainw_design);
    vector<ControlInfo> page1_controls = 
    {
        {
            { Button::Dark::Home },
            "Go to Home Menu",
        },
        {
            { Button::Dark::Capture },
            "Take a screenshot",
        },
        {
            { Button::Dark::ProController },
            " ← this is a Pro Controller!",
        }
    };
    Page page1("Test page");
    page1.setControls(page1_controls);
    function<void(CustomUI::Event)> page1_onevent = [&](CustomUI::Event event)
    {
        switch(event.getType())
        {
            case EventType::Draw:
                page1.drawRectangle(200, 220, 120, 120, { 255, 255, 0, 255 });
                break;
            case EventType::ChangedToDocked:
                mainw.setFooter("Now we're docked");
                break;
            case EventType::ChangedToHandHeld:
                mainw.setFooter("Now we're handheld");
                break;
            case EventType::JoyConAttach:
                mainw.setFooter("JoyCon(s) attached");
                break;
            case EventType::JoyConDetach:
                mainw.setFooter("JoyCon(s) detached");
                break;
            case EventType::KeyHeld:
                if(event.keyHeld() & KEY_A) mainw.setFooter("A button held");
                break;
            case EventType::KeyDown:
                if(event.keyDown() & KEY_A) mainw.setFooter("A button down");
                break;
            case EventType::KeyUp:
                if(event.keyUp() & KEY_A) mainw.setFooter("A button up");
                break;
        }
    };
    page1.onEvent(page1_onevent);
    mainw.addPage(page1);
    mainw.show();
}