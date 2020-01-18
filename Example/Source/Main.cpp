#include <pu/sdl2/sdl2_System.hpp>
#include <pu/ui/ui_Application.hpp>
#include <pu/ui/ui_Types.hpp>

#include <thread>

namespace custom {

    class Rectangle : public pu::ui::Object {

        PU_CLASS_PROPERTY_GS(x, s32, X)
        PU_CLASS_PROPERTY_GS(y, s32, Y)
        PU_CLASS_PROPERTY_GS(w, u32, Width)
        PU_CLASS_PROPERTY_GS(h, u32, Height)
        PU_CLASS_PROPERTY_GS(clr, pu::ui::Color, Color)

        public:
            Rectangle(s32 x, s32 y, u32 w, u32 h, pu::ui::Color clr) : x(x), y(y), w(w), h(h), clr(clr) {}

            virtual pu::ui::PositionAndSize GetPositionAndSize() override {
                return { this->x, this->y, this->w, this->h };
            }

            virtual void Render(pu::render::Renderer &renderer) override {
                SDL_SetRenderDrawColor(renderer.renderer, clr.r, clr.g, clr.b, clr.a);
                SDL_Rect rect = {};
                rect.x = this->x;
                rect.y = this->y;
                rect.w = this->w;
                rect.h = this->h;
                SDL_RenderFillRect(renderer.renderer, &rect);
            }

    };

}

#define log(fmt, ...) { \
    char buf[0x800] = {0}; \
    sprintf(buf, fmt, ##__VA_ARGS__); \
    svcOutputDebugString(buf, strlen(buf)); \
}

void another_thread(void *arg) {
    srand(time(nullptr));
    auto app = pu::ui::GetApplication();
    while(true) {
        hidScanInput();
        auto lyt = app->GetByName<pu::ui::Layout>("MainLayout");
        auto obj = lyt->GetByName<custom::Rectangle>("Rect1");
        auto clr = pu::ui::Color::FromRGBA(rand() % 0xff, rand() % 0xff, rand() % 0xff, 0xff);
        obj->SetColor(clr);
        if(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS) {
            app->Close();
            break;
        }
        svcSleepThread(100'000'000l);
    }
}

Thread another_thread_v;

int main()
{
    auto init = pu::sdl2::InitializeAll<SDL_INIT_VIDEO, true, pu::sdl2::flags::None, pu::sdl2::flags::None>();

    if(init) {
        log("Good init...")

        pu::render::Renderer renderer;
        auto rc = pu::render::CreateRenderer(renderer, "Demo", 1920, 1080, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(R_SUCCEEDED(rc)) {
            rc = pu::ui::InitializeApplication(renderer);
            if(R_SUCCEEDED(rc)) {
                auto app = pu::ui::GetApplication();

                auto layout = pu::ui::Layout::New<pu::ui::Layout>();
                auto obj = pu::ui::Object::New<custom::Rectangle>(10, 10, 100, 100, pu::ui::Color::FromRGBA(0, 0xff, 0, 0xff));
                layout->Add("Rect1", obj);

                app->Add("MainLayout", layout);
                app->SetCurrentLayout("MainLayout");

                threadCreate(&another_thread_v, &another_thread, nullptr, nullptr, 0x2000, 0x2b, -2);
                threadStart(&another_thread_v);

                app->Show();
            }
        }
        if(R_FAILED(rc)) {
            log("Error... - 0x%X, SDL error: '%s'", rc, SDL_GetError())
        }
    }
    else {
        log("Bad init... - 0x%X, SDL error: '%s'", init.GetResult(), SDL_GetError())
    }

    threadWaitForExit(&another_thread_v);
    threadClose(&another_thread_v);

    return 0;
}