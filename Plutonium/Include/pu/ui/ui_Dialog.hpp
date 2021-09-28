
/*

    Plutonium library

    @file ui_Dialog.hpp
    @brief A Dialog is an easy way to ask the user to choose between several options.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/pu_String.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <vector>

namespace pu::ui
{
    class Dialog
    {
        public:
            Dialog(String Title, String Content);
            PU_SMART_CTOR(Dialog)
            ~Dialog();

            void AddOption(String Name);
            void SetCancelOption(String Name = "Cancel");
            void RemoveCancelOption();
            bool HasCancelOption();
            void SetIcon(std::string Icon);
            bool Hasicon();
            i32 Show(render::Renderer::Ref &Drawer, void *App);
            bool UserCancelled();
            bool IsOk();
        private:
            bool hcancel;
            String scancel;
            String tfont_name;
            String cfont_name;
            String ofont_name;
            String stitle;
            String scnt;
            sdl2::Texture title;
            sdl2::Texture cnt;
            std::vector<String> sopts;
            std::vector<sdl2::Texture> opts;
            i32 osel;
            bool cancel;
            bool hicon;
            sdl2::Texture icon;
            i32 prevosel;
            i32 pselfact;
            i32 selfact;
    };
}