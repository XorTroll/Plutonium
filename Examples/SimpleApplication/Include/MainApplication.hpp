
#pragma once
#include <pu/Plutonium>

class Layout1 : public pu::Layout
{
    public:
        Layout1();
    private:
        pu::element::TextBlock *helloText;
};

class MainApplication : public pu::Application
{
    public:
        MainApplication();
    private:
        Layout1 *layout1;
};