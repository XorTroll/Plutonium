#include <MainApplication.hpp>

// Implement all the layout/application functions here

Layout1::Layout1()
{
    // Create the textblock with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press X to answer my question.");
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
        if(Down & KEY_X) // If A is pressed, start with our dialog questions!
        {
            int opt = this->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
            if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
            {
                this->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true);
            }
            else
            {
                switch(opt)
                {
                    case 0: // "Yes" was selected
                        this->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true);
                        break;
                    case 1: // "No" was selected
                        this->CreateShowDialog("Answer", "Oh... Then I guess you won't have an iPod...", { "(damnit, he caught me)" }, true);
                        break;
                }
            }
        }
    });
}