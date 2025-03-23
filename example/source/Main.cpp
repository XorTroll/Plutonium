#include <MainApplication.hpp>

/*

// If you would like to initialize and finalize stuff before or after Plutonium, you can use libnx's userAppInit/userAppExit

extern "C" void userAppInit() {
    // Initialize stuff
}

extern "C" void userAppExit() {
    // Cleanup/finalize stuff
}

*/

int main() {
    // First create our renderer, where one can customize SDL2 or other stuff's initialization
    auto renderer_opts = pu::ui::render::RendererInitOptions(SDL_INIT_EVERYTHING, pu::ui::render::RendererHardwareFlags);
    renderer_opts.UseImage(pu::ui::render::ImgAllFlags);

    // For text rendering, just use the system shared font (including all types, thus supporting multiple symbols)
    renderer_opts.SetPlServiceType(PlServiceType_User);
    renderer_opts.AddDefaultAllSharedFonts();

    // Player input: accept only input from Player 1, whether it is handheld or a regular controller
    renderer_opts.SetInputPlayerCount(1);
    renderer_opts.AddInputNpadStyleTag(HidNpadStyleSet_NpadStandard);
    renderer_opts.AddInputNpadIdType(HidNpadIdType_Handheld);
    renderer_opts.AddInputNpadIdType(HidNpadIdType_No1);

    auto renderer = pu::ui::render::Renderer::New(renderer_opts);

    // Create our main application from the renderer
    auto main = MainApplication::New(renderer);

    // Load the application. This MUST be called or Show() will exit and nothing will be rendered
    const auto rc = main->Load();
    if(R_FAILED(rc)) {
        diagAbortWithResult(rc);
    }

    // Show: start rendering in an "infinite" loop
    // If wou would like to show with a "fade in" from black-screen to the UI, use instead ShowWithFadeIn();
    main->Show();

    // Plutonium will handle all disposing of UI and renderer/application when Close is called

    return 0;
}
