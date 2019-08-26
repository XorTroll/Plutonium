
#pragma once

// Include Plutonium
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class Layout1 : public pu::ui::Layout
{
    public:
        Layout1();
        // Plutonium's macro to define a constructor static function for smart pointers
        // Would be similar to: static std::shared_ptr<Layout1> Layout1::New()
        PU_SMART_CTOR(Layout1)
    private:
        // An easy way to keep objects is to have them as private members
        pu::ui::elm::TextBlock::Ref helloText;
};

// Define your application as a class too
class MainApplication : public pu::ui::Application
{
    public:
        MainApplication();
        // Same macro as Layout1
        PU_SMART_CTOR(MainApplication)
    private:
        // Layout instance
        Layout1::Ref layout1;
};