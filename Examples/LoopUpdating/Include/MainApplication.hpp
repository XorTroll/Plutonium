
#pragma once

// Include Plutonium
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class Layout1 : public pu::Layout
{
    public:
        Layout1();
        void Update();
    private:
        // An easy way to keep objects is to have them as private pointer members
        pu::element::TextBlock *sampleText;
};

// Define your application as a class too
class MainApplication : public pu::Application
{
    public:
        MainApplication();
    private:
        // Layout instance
        Layout1 *layout1;
};