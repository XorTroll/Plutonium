


       ///////////////////////////////////////
      //              (uses                ///
     //              libnx)               // /
    ///////////////////////////////////////  /
    //              |--|                 //  /
    //     CustomUI libs by XorTroll     // /
    //              v0.1                 ///
    ///////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace CustomUI
{
    // Internal vars, no need to use them
    static bool inited = false;
    static bool loop;
    static int spage;
    static SDL_Window *_window;
    static SDL_Renderer *_renderer;
    static SDL_Surface *_surface;
    static SDL_Color txtcolor;
    static SDL_Color selcolor;
    static string ttf;
    static TTF_Font *fntMedium;
    static TTF_Font *fntLarge;
    static Mix_Music *audio;
    static SDL_Surface *bgs;
    static SDL_Texture *bgt;
    static string title;
    static string footer;
    static int vol;
    static int titleX = 60;
    static int titleY = 30;
    static int footerX = titleX;
    static int footerY = 672;
    static int optX = 55;
    static int optY = 115;

    // Internal functions, no need to use them
    SDL_Surface *surfInit(string Path)
    {
        SDL_Surface *srf = IMG_Load(Path.c_str());
        if (srf)
        {
            Uint32 colorkey = SDL_MapRGB(srf->format, 0, 0, 0);
            SDL_SetColorKey(srf, SDL_TRUE, colorkey);
        }
        return srf;
    }

    SDL_Texture *texInit(SDL_Surface *surf)
    {
        SDL_Texture *tex = SDL_CreateTextureFromSurface(_renderer, surf);
        return tex;
    }

    void drawText(int x, int y, SDL_Color scolor, string text, TTF_Font *font)
    {
        SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), scolor, 1280);
        SDL_SetSurfaceAlphaMod(surface, 255);
        SDL_Rect position = { x, y, surface->w, surface->h };
        SDL_BlitSurface(surface, NULL, _surface, &position);
        SDL_FreeSurface(surface);
    }

    void drawRect(int x, int y, int w, int h, SDL_Color scolor)
    {
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_SetRenderDrawColor(_renderer, scolor.r, scolor.g, scolor.b, scolor.a);
        SDL_RenderFillRect(_renderer, &rect);
    }

    void drawBackXY(SDL_Surface *surf, SDL_Texture *tex, int x, int y)
    {
        SDL_Rect position;
        position.x = x;
        position.y = y;
        position.w = surf->w;
        position.h = surf->h;
        SDL_RenderCopy(_renderer, tex, NULL, &position);
    }

    void drawBack(SDL_Surface *surf, SDL_Texture *tex)
    {
        drawBackXY(surf, tex, 0, 0);
    }

    // Input vars, updated every iteration of the loop, proper way to access input using CustomUI
    static u64 HeldInput = 0;
    static u64 PressedInput = 0;
    static u64 ReleasedInput = 0;

    // Current frame/iteration, incremented by "flushGraphics" every loop
    static int Frame = 0;

    // RGBA color
    struct RGBA
    {
        int R;
        int G;
        int B;
        int A;
    };

    // Theme for basic UI
    struct Theme
    {
        string BackgroundPath;
        string FontPath;
        RGBA TextColor;
        RGBA SelectedTextColor;
    };

    static Theme HorizonLight()
    {
        return { "romfs:/Graphics/Background.Light.png", "romfs:/Fonts/NintendoStandard.ttf", { 0, 0, 0, 255 }, { 140, 140, 140, 255 } };
    }
    static Theme HorizonDark()
    {
        return { "romfs:/Graphics/Background.Dark.png", "romfs:/Fonts/NintendoStandard.ttf", { 255, 255, 255, 255 }, { 140, 140, 140, 255 } };
    }

    // Theme being used by the current console
    static Theme HorizonCurrent()
    {
        ColorSetId id;
        setsysInitialize();
        setsysGetColorSetId(&id);
        setsysExit();
        if(id == ColorSetId_Dark) return HorizonDark();
        else return HorizonLight();
    }

    // Pages of the UI
    class Page
    {
        public:
            Page(string Name);
            void renderText(string Text, int X, int Y, RGBA Color, int Size);
            void renderImage(string Path, int X, int Y);
            void onRender(function<void()> Func);
            string getName();
            function<void()> getRenderFunction();
            void _runCallback();

        private:
            string name;
            function<void()> renderfunc;
    };

    inline Page::Page(string Name)
    {
        name = Name;
    }

    inline void Page::renderText(string Text, int X, int Y, RGBA Color, int Size)
    {
        SDL_Color clr = {Color.R, Color.G, Color.B, Color.A};
        TTF_Font *fnt = TTF_OpenFont(ttf.c_str(), Size);
        drawText(X + 411, Y + 88, clr, Text, fnt);
    }

    inline void Page::renderImage(string Path, int X, int Y)
    {
        SDL_Surface *imgs = IMG_Load(Path.c_str());
        if(imgs)
        {
            Uint32 key = SDL_MapRGB(imgs->format, 0, 0, 0);
            SDL_SetColorKey(imgs, SDL_TRUE, key);
            SDL_Texture *imgt = SDL_CreateTextureFromSurface(_renderer, imgs);
            SDL_Rect pos;
            pos.x = X + 411;
            pos.y = Y + 88;
            pos.w = imgs->w;
            pos.h = imgs->h;
            SDL_RenderCopy(_renderer, imgt, NULL, &pos);
        }
    }

    inline void Page::onRender(function<void()> Func)
    {
        renderfunc = Func;
    }

    inline string Page::getName()
    {
        return name;
    }

    inline function<void()> Page::getRenderFunction()
    {
        return renderfunc;
    }

    inline void Page::_runCallback()
    {
        renderfunc();
    }

    static vector<Page> pages;

    void render()
    {
        hidScanInput();
        HeldInput = hidKeysHeld(CONTROLLER_P1_AUTO);
        PressedInput = hidKeysDown(CONTROLLER_P1_AUTO);
        ReleasedInput = hidKeysUp(CONTROLLER_P1_AUTO);
        if(PressedInput & KEY_LSTICK_UP)
        {
            if(spage > 0) spage--;
            else spage = pages.size() - 1;
        }
        else if(PressedInput & KEY_LSTICK_DOWN)
        {
            if(spage < pages.size() - 1) spage++;
            else spage = 0;
        }
        SDL_RenderClear(_renderer);
        drawBack(bgs, bgt);
        drawText(titleX, titleY, txtcolor, title, fntLarge);
        int oy = optY;
        if(!pages.empty()) for(int i = 0; i < pages.size(); i++)
        {
            if(i == spage)
            {
                drawText(optX, oy, selcolor, pages[i].getName(), fntMedium);
                if(pages[i].getRenderFunction() != nullptr) pages[i]._runCallback();
            }
            else drawText(optX, oy, txtcolor, pages[i].getName(), fntMedium);
            oy += 50;
        }
        drawText(footerX, footerY, txtcolor, footer, fntLarge);
        SDL_RenderPresent(_renderer);
    }

    void init(string Title, string Footer, Theme Theme)
    {
        if(!inited)
        {
            inited = true;
            romfsInit();
            SDL_Init(SDL_INIT_EVERYTHING);
            SDL_CreateWindowAndRenderer(1280, 720, 0, &_window, &_renderer);
            _surface = SDL_GetWindowSurface(_window);
            SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
            IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP | IMG_INIT_TIF);
            TTF_Init();
            SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
            Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
            Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
            Mix_VolumeMusic(vol);
            ttf = Theme.FontPath;
            fntLarge = TTF_OpenFont(Theme.FontPath.c_str(), 25);
            fntMedium = TTF_OpenFont(Theme.FontPath.c_str(), 20);
            bgs = surfInit(Theme.BackgroundPath);
            bgt = texInit(bgs);
            txtcolor = { Theme.TextColor.R, Theme.TextColor.G, Theme.TextColor.B, Theme.TextColor.A };
            selcolor = { Theme.SelectedTextColor.R, Theme.SelectedTextColor.G, Theme.SelectedTextColor.B, Theme.SelectedTextColor.A };
            spage = 0;
            vol = 64;
            title = Title;
            footer = Footer;
        }
    }

    void setTheme(Theme Theme)
    {
        ttf = Theme.FontPath;
        fntLarge = TTF_OpenFont(Theme.FontPath.c_str(), 25);
        fntMedium = TTF_OpenFont(Theme.FontPath.c_str(), 20);
        bgs = surfInit(Theme.BackgroundPath);
        bgt = texInit(bgs);
        txtcolor = { Theme.TextColor.R, Theme.TextColor.G, Theme.TextColor.B, Theme.TextColor.A };
        selcolor = { Theme.SelectedTextColor.R, Theme.SelectedTextColor.G, Theme.SelectedTextColor.B, Theme.SelectedTextColor.A };
    }

    void addPage(Page NewPage)
    {
        pages.push_back(NewPage);
    }

    void exit()
    {
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_DestroyRenderer(_renderer);
        SDL_FreeSurface(_surface);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        romfsExit();
    }

    void exitApp()
    {
        exit();
        ::exit(0);
    }

    void renderGraphics()
    {
        SDL_RenderClear(_renderer);
        drawBack(bgs, bgt);
        drawText(titleX, titleY, txtcolor, title, fntLarge);
        int oy = optY;
        if(!pages.empty()) for(int i = 0; i < pages.size(); i++)
        {
            if(i == spage)
            {
                drawText(optX, oy, selcolor, pages[i].getName(), fntMedium);
                if(pages[i].getRenderFunction() != nullptr) pages[i]._runCallback();
            }
            else drawText(optX, oy, txtcolor, pages[i].getName(), fntMedium);
            oy += 50;
        }
        drawText(footerX, footerY, txtcolor, footer, fntLarge);
        SDL_RenderPresent(_renderer);
    }

    void flushGraphics()
    {
        if(Frame == 0) renderGraphics();
        Frame++;
        hidScanInput();
        HeldInput = hidKeysHeld(CONTROLLER_P1_AUTO);
        PressedInput = hidKeysDown(CONTROLLER_P1_AUTO);
        ReleasedInput = hidKeysUp(CONTROLLER_P1_AUTO);
        if(PressedInput & KEY_LSTICK_UP)
        {
            if(spage > 0) spage--;
            else spage = pages.size() - 1;
            renderGraphics();
        }
        else if(PressedInput & KEY_LSTICK_DOWN)
        {
            if(spage < pages.size() - 1) spage++;
            else spage = 0;
            renderGraphics();
        }
    }
}