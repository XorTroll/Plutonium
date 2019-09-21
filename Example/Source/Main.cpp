#include <MainApplication.hpp>

/*

// If you would like to initialize and finalize stuff before or after Plutonium, you can use libnx's userAppInit/userAppExit

extern "C" void userAppInit()
{
    // Initialize stuff
}

extern "C" void userAppExit()
{
    // Cleanup/finalize stuff
}

*/

// Main entrypoint
int main()
{
    // First create our renderer, where one can customize SDL or other stuff's initialization.
    auto renderer = pu::ui::render::Renderer::New(SDL_INIT_EVERYTHING, pu::ui::render::RendererInitOptions::RendererNoSound, pu::ui::render::RendererHardwareFlags);

    // Create our main application from the renderer
    auto main = MainApplication::New(renderer);

    // Prepare out application. This MUST be called or Show() will exit and nothing will be rendered.
    main->Prepare();

    // Show -> start rendering in an "infinite" loop
    // If wou would like to show with a "fade in" from black-screen to the UI, use instead ->ShowWithFadeIn();
    main->Show();

    // Exit homebrew (Plutonium will handle all disposing of UI and renderer/application, don't worry!

    return 0;
}