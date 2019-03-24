#include <MainApplication.hpp>

// Main entrypoint, call the app here
int main()
{
    // Create the application
    MainApplication *amain = new MainApplication();
    // Show it. This function will finalize when the application's "Close()" function is called.
    amain->Show();
    // IMPORTANT! free the application to destroy allocated memory and to finalize graphics.
    delete amain;
    // Exit
    return 0;
}