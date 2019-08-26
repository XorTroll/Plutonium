#include <MainApplication.hpp>

// Implement all the layout/application functions here

Layout1::Layout1()
{
    // Create the textblock with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Hello world!");
    // Add the textblock to the layout's element container. IMPORTANT! this MUST be done, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);
}

MainApplication::MainApplication()
{
    // Create the layout (calling the constructor above)
    this->layout1 = Layout1::New();
    // Load the layout. In applications layouts are loaded, not added into a container (you don't select a added layout, just load it from this function)
    this->LoadLayout(this->layout1);
}