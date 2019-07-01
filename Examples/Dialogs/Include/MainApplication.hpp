

#pragma once

// Include Plutonium
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class Layout1 : public pu::ui::Layout
{
    public:
        Layout1();
    private:
        // An easy way to keep objects is to have them as private pointer members
        pu::ui::elm::TextBlock *helloText;
};

// Define your application as a class too
class MainApplication : public pu::ui::Application
{
    public:
        MainApplication();
    private:
        // Layout instance
        Layout1 *layout1;
};