
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class CustomLayout : public pu::ui::Layout {
    private:

        // An easy way to keep objects is to have them as private members
        // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
        pu::ui::elm::TextBlock::Ref helloText;

    public:

        CustomLayout();

        // Have ::Ref alias and ::New() static constructor
        PU_SMART_CTOR(CustomLayout)
};

// Define your application (can't instantiate base class, so need to make a derived one)
class MainApplication : public pu::ui::Application {
    private:

        // Layout instance
        CustomLayout::Ref layout;
    
    public:
        using Application::Application;
        PU_SMART_CTOR(MainApplication)

        // We need to define this, and use it to initialize everything
        void OnLoad() override;
};