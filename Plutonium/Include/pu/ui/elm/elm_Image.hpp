
/*

    Plutonium library

    @file Image.hpp
    @brief An Image is an Element showing a picture. (JPEG, PNG, TGA, BMP)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class Image : public Element
    {
        public:
            Image(s32 X, s32 Y, String Image);
            ~Image();
            s32 GetX();
            void SetX(s32 X);
            s32 GetY();
            void SetY(s32 Y);
            s32 GetWidth();
            void SetWidth(s32 Width);
            s32 GetHeight();
            void SetHeight(s32 Height);
            String GetImage();
            void SetImage(String Image);
            bool IsImageValid();
            void OnRender(render::Renderer *Drawer);
            void OnInput(u64 Down, u64 Up, u64 Held, bool Touch, bool Focus);
        private:
            String img;
            render::NativeTexture ntex;
            s32 x;
            s32 y;
            s32 w;
            s32 h;
    };
}