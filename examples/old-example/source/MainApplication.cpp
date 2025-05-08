#include <MainApplication.hpp>

// Implement all the layout/application functions here

extern MainApplication::Ref g_MainApplication;

CustomLayout::CustomLayout() : Layout::Layout() {
    // Create the TextBlock instance with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press X to answer my question");
    
    // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);

    // Set a function when input is caught. This input handling will be the first one to be handled (before Layout or any Elements)
    // Using a lambda function here to simplify things
    // You can use member functions via std::bind() C++ wrapper
    this->SetOnInput([&](const u64 keys_down, const u64 keys_up, const u64 keys_held, const pu::ui::TouchPoint touch_pos) {
        if(keys_down & HidNpadButton_A) {
            this->helloText->SetText("Hello world!"); // Change the text of the TextBlock instance
        }
        else if(keys_down & HidNpadButton_B) {
            this->helloText->SetText("Bye bye world!"); // Change the text of the TextBlock instance
        }
        else if(keys_down & HidNpadButton_Y) {
            this->helloText->SetText("I am a Plutonium application!"); // Change the text of the TextBlock instance
        }

        // If X is pressed, start with our dialog questions!
        if(keys_down & HidNpadButton_X) {
            int opt = g_MainApplication->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
            // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
            if((opt == -1) || (opt == -2))  {
                g_MainApplication->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
            }
            else {
                // Otherwise, opt will be the index of the options we passed to the dialog
                switch(opt) {
                    // "Yes!" was selected
                    case 0:  {
                        g_MainApplication->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true); // Same here ^
                        break;
                    }
                    // "No..." was selected
                    case 1: {
                        // Create a toast
                        auto toast_text = pu::ui::elm::TextBlock::New(0, 0, "Well, I don't like apples either.");
                        toast_text->SetColor(pu::ui::Color::FromHex("#FFFFFFFF")); // Set the text color to white
                        toast_text->SetFont(pu::ui::GetDefaultFont(pu::ui::DefaultFontSize::Small)); // Set the font to the default one
                        auto toast = pu::ui::ly::Toast::New(toast_text, pu::ui::Color::FromHex("#0055FFFF"), 3000); // 3 seconds
                        toast->SetBaseAlpha(150); // Set the base alpha to 150 (somewhat transparent)
                        g_MainApplication->AddLayer(toast); // Add the toast to the application (it will be shown in the next frame and automatically removed after 3 seconds)
                        break;
                    }
                }
            }
        }
        // If + is pressed, exit application
        else if(keys_down & HidNpadButton_Plus) {
            g_MainApplication->Close();
        }
    });
}

void MainApplication::OnLoad() {
    // Create the layout (calling the smart constructor above)
    this->layout = CustomLayout::New();

    // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
    // Simply explained: loading layout = the application will render that layout in the very next frame
    this->LoadLayout(this->layout);
}
