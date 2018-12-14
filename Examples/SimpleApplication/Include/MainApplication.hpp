
#pragma once
#include <pn/pn.hpp>

class Layout1 : public pn::Layout
{
    public:
        Layout1();
    private:
        pn::fw::TextBlock *helloText;
};

class MainApplication : public pn::Application
{
    public:
        MainApplication();
    private:
        Layout1 *layout1;
};