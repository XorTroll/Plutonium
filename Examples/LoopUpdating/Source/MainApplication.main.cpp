#include <MainApplication.hpp>

// Main entrypoint, call the app here
int main()
{
    // Create a smart pointer of our application (can be a regular instance)
    auto main = MainApplication::New();

    // Show -> start rendering in an "infinite" loop
    main->Show();

    // Exit (Plutonium will handle when the app is closed, and it will be disposed later)
    return 0;
}