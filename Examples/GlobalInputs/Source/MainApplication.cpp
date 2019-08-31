#include <MainApplication.hpp>

// Implement all the layout/application functions here

Layout1::Layout1()
{
    // Create the textblock with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press Plus or Minus, or touch the screen!");
    // Add the textblock to the layout's element container. IMPORTANT! this MUST be done, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);
}

MainApplication::MainApplication()
{
    // Create the layout (calling the constructor above)
    this->layout1 = Layout1::New();
    // Load the layout. In applications layouts are loaded, not added into a container (you don't select a added layout, just load it from this function)
    this->LoadLayout(this->layout1);
    // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
    // Using a lambda function here to simplify things
    this->SetOnInput([&](u64 Down, u64 Up, u64 Held, bool Touch)
    {
        if((Down & KEY_PLUS) || (Down & KEY_MINUS)) // If + or - is pressed...
        {
            // This is the proper way to exit the UI and finalize it correctly inside the UI itself (or other elements)
            this->Close();
        }
    });
}