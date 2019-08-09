
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
            ~Dialog();
            void AddOption(String Name);
            void SetCancelOption(String Name = "Cancel");
            void RemoveCancelOption();
            bool HasCancelOption();
            void SetIcon(std::string Icon);
            bool Hasicon();
            s32 Show(render::Renderer *Drawer, void *App);
            bool UserCancelled();
            bool IsOk();
        private:
            bool hcancel;
            String scancel;
            render::NativeFont tfont;
            render::NativeFont cfont;
            render::NativeFont ofont;
            render::NativeTexture title;
            render::NativeTexture cnt;
            std::vector<String> sopts;
            std::vector<render::NativeTexture> opts;
            s32 osel;
            bool cancel;
            bool hicon;
            render::NativeTexture icon;
            s32 prevosel;
            s32 pselfact;
            s32 selfact;
    };
}