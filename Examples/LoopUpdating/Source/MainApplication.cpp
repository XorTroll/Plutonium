#include <MainApplication.hpp>

// Implement all the layout/application functions here
// This variable needs to be global, but it can be a member of a class too (easier to define it here tho)
s32 count = 0;

Layout1::Layout1()
{
    // Create the textblock (that text is a placeholder tho)
    this->sampleText = pu::ui::elm::TextBlock::New(300, 300, "Count: ");
    // Add the textblock to the layout's element container. IMPORTANT! this MUST be done, having them as members is not enough (just a simple way to keep them)
    this->Add(this->sampleText);
}

// This will be executed each loop, before rendering data
void Layout1::Update()
{
    // Increase the number
    count++;
    // Update the number's text
    this->sampleText->SetText("Count: " + std::to_string(count));
}

MainApplication::MainApplication()
{
    // Create the layout (calling the constructor above)
    this->layout1 = Layout1::New();
    // Add the loop function to the application via std::bind
    this->AddThread(std::bind(&Layout1::Update, this->layout1));
    // Load the layout. In applications layouts are loaded, not added into a container (you don't select a added layout, just load it from this function)
    this->LoadLayout(this->layout1);
}