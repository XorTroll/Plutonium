#include <pu/sdl2/sdl2_System.hpp>
#include <pu/ui/ui_Application.hpp>
#include <pu/render/render_Utils.hpp>
#include <pu/ttf/ttf_FontManager.hpp>
#include <thread>

namespace custom {

    class Rectangle : public pu::ui::Object {

        PU_CLASS_PROPERTY_SIMPLE_GS(x, i32, X)
        PU_CLASS_PROPERTY_SIMPLE_GS(y, i32, Y)
        PU_CLASS_PROPERTY_SIMPLE_GS(w, u32, Width)
        PU_CLASS_PROPERTY_SIMPLE_GS(h, u32, Height)
        PU_CLASS_PROPERTY_SIMPLE_GS(clr, pu::ui::Color, Color)

        public:
            Rectangle(i32 x, i32 y, u32 w, u32 h, pu::ui::Color clr) : x(x), y(y), w(w), h(h), clr(clr) {}

            virtual pu::ui::PositionAndSize GetPositionAndSize() override {
                return { this->x, this->y, this->w, this->h };
            }

            virtual void Render() override {
                auto pas = this->GetPositionAndSize();
                pu::render::DrawRoundedRectangle(clr, PU_UI_FORWARD_POSITION_AND_SIZE(pas), 25, true);
            }

    };

    class Text : public pu::ui::Object {

        PU_CLASS_PROPERTY_SIMPLE_GS(x, i32, X)
        PU_CLASS_PROPERTY_SIMPLE_GS(y, i32, Y)
        PU_CLASS_PROPERTY_SIMPLE_GS(clr, pu::ui::Color, Color)
        PU_CLASS_PROPERTY_G(fname, std::string, const std::string&, FontName)
        PU_CLASS_PROPERTY_SIMPLE_G(fsize, u32, FontSize)
        PU_CLASS_PROPERTY_G(txt, std::string, const std::string&, Text)

        private:
            pu::sdl2::Texture txt_tex;

            void RenderText() {
                pu::render::DisposeTexture(this->txt_tex);
                auto font = pu::ttf::GetFontByName(this->fname, this->fsize);
                if(font) {
                    this->txt_tex = font->RenderText(txt, this->clr);
                }
            }

        public:
            void SetText(const std::string &txt) {
                this->txt = txt;
                this->RenderText();
            }

            void SetFontSize(u32 size) {
                this->fsize = size;
                this->RenderText();
            }

            void SetFontName(const std::string &name) {
                this->fname = name;
                this->RenderText();
            }

        public:
            Text(i32 x, i32 y, pu::ui::Color clr, const std::string &font_name, u32 font_size, const std::string &text) : x(x), y(y), clr(clr), fname(font_name), fsize(font_size) {
                this->SetText(text);
            }

            virtual pu::ui::PositionAndSize GetPositionAndSize() override {
                auto txt_sz = pu::render::GetTextureSize(this->txt_tex);
                return { this->x, this->y, PU_UI_FORWARD_SIZE(txt_sz) };
            }

            virtual void Render() override {
                auto pas = this->GetPositionAndSize();
                pu::render::DrawTexture(this->txt_tex, PU_UI_FORWARD_POSITION(pas));
            }

    };

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
        tmplog("Good init...")

        pu::render::Renderer renderer;
        auto rc = pu::render::CreateRenderer(renderer, "Demo", 1920, 1080, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(R_SUCCEEDED(rc)) {
            rc = pu::ui::InitializeApplication(renderer);
            if(R_SUCCEEDED(rc)) {
                rc = pu::ttf::LoadSystemSharedFont("SharedFont");
                if(R_SUCCEEDED(rc)) {
                    auto app = pu::ui::GetApplication();

                    auto layout = pu::ui::Layout::New<pu::ui::Layout>();

                    auto rect1 = pu::ui::Object::New<custom::Rectangle>(10, 10, 100, 100, pu::ui::Color::FromRGBA(0, 0xff, 0, 0xff));
                    layout->Add("Rect1", rect1);

                    auto text1 = pu::ui::Object::New<custom::Text>(10, 100, pu::ui::Color::FromRGBA(10, 10, 10, 0xff), "SharedFont", 100, "Press \uE0EF to exit this demo.\nPress \uE0EF to exit this demo.\nPress \uE0EF to exit this demo.\nPress \uE0EF to exit this demo.");
                    layout->Add("Text1", text1);

                    app->Add("MainLayout", layout);
                    app->SetCurrentLayout("MainLayout");

                    threadCreate(&another_thread_v, &another_thread, nullptr, nullptr, 0x2000, 0x2b, -2);
                    threadStart(&another_thread_v);

                    app->Show();
                }
            }
        }
        if(R_FAILED(rc)) {
            tmplog("Error... - 0x%X, SDL error: '%s'", rc, SDL_GetError())
        }
    }
    else {
        tmplog("Bad init... - 0x%X, SDL error: '%s'", init.GetResult(), SDL_GetError())
    }

    threadWaitForExit(&another_thread_v);
    threadClose(&another_thread_v);

    return 0;
}