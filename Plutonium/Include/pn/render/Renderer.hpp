
#pragma once
#include <pn/draw/Color.hpp>
#include <pn/draw/Font.hpp>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace pn::render
{
    class Renderer
    {
        public:
            void Initialize();
            void Finalize();
            bool HasInitialized();
            void Clear(draw::Color ClearColor);
            void Render();
            void DrawImage(std::string Path, u32 X, u32 Y);
            void DrawImageColorKey(std::string Path, draw::Color ColorKey, u32 X, u32 Y);
            void DrawText(std::string Text, draw::SystemFont Font, u32 Size, u32 X, u32 Y, draw::Color TextColor);
            void DrawRectangle(draw::Color RecColor, u32 X, u32 Y, u32 Width, u32 Height);
            void DrawRectangleFill(draw::Color RecColor, u32 X, u32 Y, u32 Width, u32 Height);
            void DrawCircle(draw::Color CircleColor, u32 X, u32 Y, u32 Radius);
        private:
            bool okromfs;
            bool initialized;
            SDL_Window *rendwd;
            SDL_Renderer *rendrd;
            SDL_Surface *rendsf;
    };
}