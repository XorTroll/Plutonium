
#pragma once
#include "Background.hpp"
#include "Controls.hpp"
#include "../Common/Event.hpp"

namespace CustomUI
{
    namespace GUI
    {
        class Window;

        class Page
        {
            public:
                Page(string Name);
                void setName(string Name);
                string getName();
                void setControls(vector<ControlInfo> Controls);
                vector<ControlInfo> getControls();
                void onEvent(function<void(Event)> Callback);
                function<void(Event)> getEventCallback();
                Window *getParent();
                void setParent(Window *Main);
                void drawPixel(u32 X, u32 Y, Color PixelColor);
                void drawRectangle(u32 X, u32 Y, u32 Width, u32 Height, Color RectangleColor);
                void drawImage(string Path, u32 X, u32 Y);
                void drawImageChroma(string Path, u32 X, u32 Y, Color ChromaKey);
            private:
                Window *wptr;
                bool drawset;
                function<void(Event)> cevent;
                string name;
                vector<ControlInfo> ctrls;
        };

        struct WindowDesign
        {
            Background Main;
            Color Accent;
            Color Text;
            Color Border;
        };

        class Window
        {
            public:
                Window();
                Window(string Footer);
                Window(WindowDesign Design);
                Window(string Footer, WindowDesign Design);
                Window(vector<Page> Pages);
                Window(vector<Page> Pages, WindowDesign Design);
                Window(string Footer, vector<Page> Pages, WindowDesign Design);
                void setFooter(string Footer);
                string getFooter();
                void addPage(Page NewPage);
                Page getCurrentPage();
                vector<Page> getPages();
                void setSectionWidth(u32 Width);
                u32 getSectionWidth();
                void setAutoExit(bool AutoExit);
                bool hasAutoExit();
                void initialize();
                void draw();
                void pause();
                void resume();
                bool isPaused();
                void show();
                void exit();
                bool isInitialized();
                void setExitKeys(vector<u64> Keys);
                vector<u64> getExitKeys();
            private:
                vector<u64> kexit;
                bool winit;
                bool cont;
                bool aexit;
                bool pagemenu;
                bool controlmenu;
                u32 sectionw;
                u32 cpageidx;
                string footer;
                WindowDesign wdes;
                vector<Page> pages;
        };
    }
}