
/*

    Plutonium library

    @file Button.hpp
    @brief A Button is an Element for option selecting.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <functional>
#include <pu/pu_String.hpp>
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    enum class JoyCon
    {
        Left,
        Right
    };

    class MotionCursor : public Element
    {
        public:
            MotionCursor(String CursorImage, HidControllerID Player, JoyCon JoyCon);
            PU_SMART_CTOR(MotionCursor)
            ~MotionCursor();

            s32 GetX();
            s32 GetY();
            s32 GetWidth();
            s32 GetHeight();
            String GetCursorImage();
            void SetCursorImage(String Path);
            void OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            s32 lastx;
            s32 lasty;
            String imgpath;
            render::NativeTexture cursorimg;
            std::function<void(u32,u32)> click;
            JoyCon joycon;
            HidControllerID player;
            u32 sixaxishandles[2];
    };
}