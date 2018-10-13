#include "Window.hpp"

SDL_Window *sdlwindow;
SDL_Renderer *sdlrenderer;
SDL_Surface *sdlsurface;
bool sdlinit = false;
TTF_Font *small;
TTF_Font *normal;
TTF_Font *shfont;
SDL_RWops *fstd1;
SDL_RWops *fstd2;
SDL_RWops *fext;
bool rfirst = true;
u8 omode = 0;
bool attach = false;
u64 idown = 0;
u64 iup = 0;
u64 iheld = 0;

void sdl_init()
{
    if(!sdlinit)
    {
        romfsInit();
        plInitialize();
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_CreateWindowAndRenderer(1280, 720, 0, &sdlwindow, &sdlrenderer);
        sdlsurface = SDL_GetWindowSurface(sdlwindow);
        SDL_SetRenderDrawBlendMode(sdlrenderer, SDL_BLENDMODE_BLEND);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP);
        TTF_Init();
        Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
        PlFontData stdfont;
        PlFontData extfont;
        size_t fontss = 0;
        plGetSharedFontByType(&stdfont, 0);
        plGetSharedFontByType(&extfont, 5);
        fstd1 = SDL_RWFromMem(stdfont.address, stdfont.size);
        normal = TTF_OpenFontRW(fstd1, 1, 25);
        fstd2 = SDL_RWFromMem(stdfont.address, stdfont.size);
        small = TTF_OpenFontRW(fstd2, 1, 20);
        fext = SDL_RWFromMem(extfont.address, extfont.size);
        shfont = TTF_OpenFontRW(fext, 1, 20);
        sdlinit = true;
    }
}

void sdl_exit()
{
    if(sdlinit)
    {
        SDL_FreeRW(fstd1);
        SDL_FreeRW(fstd2);
        SDL_FreeRW(fext);
        plExit();
        romfsExit();
        TTF_CloseFont(normal);
        TTF_CloseFont(small);
        TTF_CloseFont(shfont);
        TTF_Quit();
        IMG_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_DestroyRenderer(sdlrenderer);
        SDL_FreeSurface(sdlsurface);
        SDL_DestroyWindow(sdlwindow);
        SDL_Quit();
        sdlinit = false;
    }
}

SDL_Surface *sdl_surfaceFromImage(string Path)
{
    SDL_Surface *srf = IMG_Load(Path.c_str());
	if(srf)
	{
		Uint32 colorkey = SDL_MapRGBA(srf->format, 0, 0, 0, 255);
		SDL_SetColorKey(srf, SDL_TRUE, colorkey);
	}
	return srf;
}

SDL_Texture *sdl_textureFromSurface(SDL_Surface *srf)
{
    return SDL_CreateTextureFromSurface(sdlrenderer, srf);
}

SDL_Color sdl_fromColor(CustomUI::GUI::Color GUIColor)
{
    return { GUIColor.Red, GUIColor.Green, GUIColor.Blue, GUIColor.Alpha };
}

void sdl_drawText(int x, int y, SDL_Color scolor, string text, TTF_Font *font)
{
    SDL_Surface *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), scolor, 1280);
    SDL_SetSurfaceAlphaMod(surface, 255);
    SDL_Texture *tex = sdl_textureFromSurface(surface);
    SDL_Rect position = { x, y, surface->w, surface->h };
    SDL_RenderCopy(sdlrenderer, tex, NULL, &position);
    SDL_FreeSurface(surface);
}

void sdl_drawRect(int x, int y, int w, int h, SDL_Color scolor)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_SetRenderDrawColor(sdlrenderer, scolor.r, scolor.g, scolor.b, scolor.a);
    SDL_RenderFillRect(sdlrenderer, &rect);
}

void sdl_drawImage(string Path, int X, int Y)
{
    SDL_Surface *imgs = IMG_Load(Path.c_str());
	if(imgs)
	{
		SDL_Texture *imgt = sdl_textureFromSurface(imgs);
        SDL_Rect position;
	    position.x = X;
        position.y = Y;
	    SDL_QueryTexture(imgt, NULL, NULL, &position.w, &position.h);
	    SDL_RenderCopy(sdlrenderer, imgt, NULL, &position);
	}
	SDL_FreeSurface(imgs);
}

void sdl_drawImageChroma(string Path, int X, int Y, SDL_Color ChromaKey)
{
    SDL_Surface *imgs = IMG_Load(Path.c_str());
	if(imgs)
	{
		Uint32 colorkey = SDL_MapRGBA(imgs->format, ChromaKey.r, ChromaKey.g, ChromaKey.g, ChromaKey.a);
		SDL_SetColorKey(imgs, SDL_TRUE, colorkey);
		SDL_Texture *imgt = SDL_CreateTextureFromSurface(sdlrenderer, imgs);
        SDL_Rect position;
	    position.x = X;
        position.y = Y;
	    SDL_QueryTexture(imgt, NULL, NULL, &position.w, &position.h);
	    SDL_RenderCopy(sdlrenderer, imgt, NULL, &position);
	}
	SDL_FreeSurface(imgs);
}

CustomUI::GUI::Page::Page(string Name)
{
    this->name = Name;
    this->drawset = false;
    this->wptr = NULL;
}

void CustomUI::GUI::Page::setName(string Name)
{
    this->name = Name;
}

string CustomUI::GUI::Page::getName()
{
    return this->name;
}

void CustomUI::GUI::Page::setControls(vector<CustomUI::GUI::ControlInfo> Controls)
{
    this->ctrls = Controls;
}

vector<CustomUI::GUI::ControlInfo> CustomUI::GUI::Page::getControls()
{
    return this->ctrls;
}

void CustomUI::GUI::Page::onEvent(function<void(CustomUI::Event)> Callback)
{
    this->cevent = Callback;
}

function<void(CustomUI::Event)> CustomUI::GUI::Page::getEventCallback()
{
    return this->cevent;
}

void CustomUI::GUI::Page::setParent(CustomUI::GUI::Window *Main)
{
    this->wptr = Main;
}

CustomUI::GUI::Window *CustomUI::GUI::Page::getParent()
{
    return this->wptr;
}

void CustomUI::GUI::Page::drawPixel(u32 X, u32 Y, CustomUI::GUI::Color PixelColor)
{
    sdl_drawRect(X, (Y + 75), 0, 0, sdl_fromColor(PixelColor));
}

void CustomUI::GUI::Page::drawRectangle(u32 X, u32 Y, u32 Width, u32 Height, CustomUI::GUI::Color RectangleColor)
{
    sdl_drawRect(X, (Y + 75), Width, Height, sdl_fromColor(RectangleColor));
}

void CustomUI::GUI::Page::drawImage(string Path, u32 X, u32 Y)
{
    sdl_drawImage(Path, X, (Y + 75));
}

void CustomUI::GUI::Page::drawImageChroma(string Path, u32 X, u32 Y, Color ChromaKey)
{
    sdl_drawImageChroma(Path, X, (Y + 75), sdl_fromColor(ChromaKey));
}

CustomUI::GUI::Window::Window()
{
    sdl_init();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = "";
    this->wdes.Main = Background();
    this->wdes.Accent = { 45, 45, 150, 255 };
    this->wdes.Text = { 10, 10, 10, 255 };
    this->wdes.Border = { 33, 33, 33, 255 };
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(string Footer)
{
    sdl_init();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = Footer;
    this->wdes.Main = Background();
    this->wdes.Accent = { 45, 45, 150, 255 };
    this->wdes.Text = { 10, 10, 10, 255 };
    this->wdes.Border = { 33, 33, 33, 255 };
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(CustomUI::GUI::WindowDesign Design)
{
    sdl_init();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = "";
    this->wdes = Design;
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(string Footer, CustomUI::GUI::WindowDesign Design)
{
    sdl_init();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = Footer;
    this->wdes = Design;
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(vector<CustomUI::GUI::Page> Pages)
{
    sdl_init();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = "";
    this->wdes.Main = Background();
    this->wdes.Accent = { 45, 45, 150, 255 };
    this->wdes.Text = { 10, 10, 10, 255 };
    this->wdes.Border = { 33, 33, 33, 255 };
    this->pages = Pages;
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(vector<CustomUI::GUI::Page> Pages, CustomUI::GUI::WindowDesign Design)
{
    this->initialize();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = "";
    this->wdes = Design;
    this->pages = Pages;
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

CustomUI::GUI::Window::Window(string Footer, vector<CustomUI::GUI::Page> Pages, CustomUI::GUI::WindowDesign Design)
{
    this->initialize();
    this->sectionw = 490;
    this->cpageidx = 0;
    this->footer = Footer;
    this->wdes = Design;
    this->pages = Pages;
    this->pagemenu = false;
    this->controlmenu = false;
    this->cont = true;
    this->aexit = true;
    this->winit = false;
    this->kexit = { KEY_PLUS, KEY_MINUS };
}

void CustomUI::GUI::Window::setFooter(string Footer)
{
    this->footer = Footer;
}

string CustomUI::GUI::Window::getFooter()
{
    return this->footer;
}

void CustomUI::GUI::Window::addPage(CustomUI::GUI::Page NewPage)
{
    NewPage.setParent(this);
    this->pages.push_back(NewPage);
}

CustomUI::GUI::Page CustomUI::GUI::Window::getCurrentPage()
{
    return this->pages[this->cpageidx];
}

vector<CustomUI::GUI::Page> CustomUI::GUI::Window::getPages()
{
    return this->pages;
}

void CustomUI::GUI::Window::setSectionWidth(u32 Width)
{
    this->sectionw = Width;
}

u32 CustomUI::GUI::Window::getSectionWidth()
{
    return this->sectionw;
}

void CustomUI::GUI::Window::setAutoExit(bool AutoExit)
{
    this->aexit = AutoExit;
}

bool CustomUI::GUI::Window::hasAutoExit()
{
    return this->aexit;
}

void CustomUI::GUI::Window::initialize()
{
    sdl_exit();
    sdl_init();
}

void CustomUI::GUI::Window::draw()
{
    SDL_RenderClear(sdlrenderer);
    switch(this->wdes.Main.getType())
    {
        case BackgroundType::Image:
            sdl_drawImage(this->wdes.Main.getImage(), 0, 0);
            break;
        case BackgroundType::SolidColor:
            sdl_drawRect(0, 0, 1280, 720, sdl_fromColor(this->wdes.Main.getColor()));
            break;
        case BackgroundType::Gradient:
            // how the fuck do I draw gradients...
            break;
    }
    sdl_drawRect(30, 74, 1220, 1, sdl_fromColor(this->wdes.Border));
    sdl_drawRect(30, 645, 1220, 1, sdl_fromColor(this->wdes.Border));
    sdl_drawText(65, 25, sdl_fromColor(this->wdes.Text), this->pages[this->cpageidx].getName(), normal);
    (this->pages[this->cpageidx].getEventCallback())(Event(EventType::Draw));
    if(!this->footer.empty()) sdl_drawText(75, 670, sdl_fromColor(this->wdes.Text), this->footer, normal);
    u32 sred = ((u32)this->wdes.Accent.Red + 10);
    if(sred > 255) sred = 255;
    u32 sgr = ((u32)this->wdes.Accent.Green + 10);
    if(sgr > 255) sgr = 255;
    u32 sbl = ((u32)this->wdes.Accent.Blue + 10);
    if(sbl > 255) sbl = 255;
    Color section = { (u8)sred, (u8)sgr, (u8)sbl, 80 };
    if(this->pagemenu && !this->controlmenu)
    {
        // sdl_drawRect(0, 0, 75, 75, { (u8)sred, (u8)sgr, (u8)sbl, 100 });
        sdl_drawRect(0, 75, this->sectionw, 750, sdl_fromColor(section));
        u32 pagey = 100;
        for(u32 i = 0; i < this->pages.size(); i++)
        {
            u32 pred = ((u32)this->wdes.Accent.Red + 35);
            if(pred > 255) pred = 255;
            u32 pgr = ((u32)this->wdes.Accent.Green + 35);
            if(pgr > 255) pgr = 255;
            u32 pbl = ((u32)this->wdes.Accent.Blue + 35);
            if(pbl > 255) pbl = 255;
            Color dprim = { (u8)pred, (u8)pgr, (u8)pbl, 200 };
            if(this->cpageidx == i) sdl_drawRect(0, (pagey - 25), this->sectionw, 68, sdl_fromColor(dprim));
            sdl_drawText(55, pagey, sdl_fromColor(this->wdes.Text), this->pages[i].getName(), small);
            pagey += 63;
        }
    }
    else if(this->controlmenu && !this->pagemenu)
    {
        // sdl_drawRect(1205, 0, 75, 75, { (u8)sred, (u8)sgr, (u8)sbl, 100 });
        sdl_drawRect(790, 75, this->sectionw, 750, sdl_fromColor(section));
        u32 controly = 110;
        vector<ControlInfo> controls = this->pages[this->cpageidx].getControls();
        if(!controls.empty()) for(u32 i = 0; i < controls.size(); i++)
        {
            u32 csize = (controls[i].Buttons.size() * 20) + 10;
            string ctext;
            for(u32 j = 0; j < controls[i].Buttons.size(); j++) ctext += controls[i].Buttons[j];
            sdl_drawText(825, controly, sdl_fromColor(this->wdes.Text), ctext, shfont);
            sdl_drawText((825 + csize), controly, sdl_fromColor(this->wdes.Text), controls[i].Description, small);
            controly += 50;
        }
    }
    SDL_RenderPresent(sdlrenderer);
}

void CustomUI::GUI::Window::pause()
{
    this->cont = false;
}

void CustomUI::GUI::Window::resume()
{
    this->cont = true;
    this->show();
}

bool CustomUI::GUI::Window::isPaused()
{
    return !this->cont;
}

void CustomUI::GUI::Window::show()
{
    if(!this->winit)
    {
        (this->pages[this->cpageidx].getEventCallback())(Event(EventType::Initialize));
        this->winit = true;
    }
    while(this->cont)
    {
        appletMainLoop();
        hidScanInput();
        idown = hidKeysDown(CONTROLLER_P1_AUTO);
        iheld = hidKeysHeld(CONTROLLER_P1_AUTO);
        iup = hidKeysUp(CONTROLLER_P1_AUTO);
        HidSharedMemory *hmem = (HidSharedMemory*)hidGetSharedmemAddr();
        if(rfirst)
        {
            this->draw();
            rfirst = false;
            omode = appletGetOperationMode();
            u64 connection = hmem->controllers[0].layouts[6].entries[hmem->controllers[0].layouts[6].header.latestEntry].connectionState;
            attach = !(connection & CONTROLLER_STATE_CONNECTED);
        }
        u64 connection = hmem->controllers[0].layouts[6].entries[hmem->controllers[0].layouts[6].header.latestEntry].connectionState;
        bool nattach = !(connection & CONTROLLER_STATE_CONNECTED);
        if(nattach != attach)
        {
            attach = nattach;
            if(nattach) (this->pages[this->cpageidx].getEventCallback())(Event(EventType::JoyConAttach));
            else (this->pages[this->cpageidx].getEventCallback())(Event(EventType::JoyConDetach));
            this->draw();
        }
        u8 nmode = appletGetOperationMode();
        if(omode != nmode)
        {
            omode = nmode;
            if(omode == 0) (this->pages[this->cpageidx].getEventCallback())(Event(EventType::ChangedToHandHeld));
            else (this->pages[this->cpageidx].getEventCallback())(Event(EventType::ChangedToDocked));
            this->draw();
        }
        if((idown & KEY_UP) && this->pagemenu)
        {
            if(this->cpageidx > 0) this->cpageidx--;
            else this->cpageidx = (this->pages.size() - 1);
            this->draw();
        }
        else if((idown & KEY_DOWN) && this->pagemenu)
        {
            if(this->cpageidx < (this->pages.size() - 1)) this->cpageidx++;
            else this->cpageidx = 0;
            this->draw();
        }
        else if(idown & KEY_TOUCH)
        {
            touchPosition tch;
            hidTouchRead(&tch, 0);
            if((tch.px >= 0 && tch.px <= 640) && (tch.py >= 0 && tch.py <= 75))
            {
                if(this->controlmenu) this->controlmenu = !this->controlmenu;
                else this->pagemenu = !this->pagemenu;
                this->draw();
            }
            else if((tch.px >= 640 && tch.px <= 1280) && (tch.py >= 0 && tch.py <= 75))
            {
                if(this->pagemenu) this->pagemenu = !this->pagemenu;
                else this->controlmenu = !this->controlmenu;
                this->draw();
            }
            else
            {
                if(this->pagemenu && !this->controlmenu)
                {
                    this->pagemenu = !this->pagemenu;
                    this->draw();
                }
                else if(this->controlmenu && !this->pagemenu)
                {
                    this->controlmenu = !this->controlmenu;
                    this->draw();
                }
            }
        }
        else if(idown & KEY_ZL)
        {
            if(this->controlmenu) this->controlmenu = !this->controlmenu;
            else this->pagemenu = !this->pagemenu;
            this->draw();
        }
        else if(idown & KEY_ZR)
        {
            if(this->pagemenu) this->pagemenu = !this->pagemenu;
            else this->controlmenu = !this->controlmenu;
            this->draw();
        }
        else if(idown)
        {
            if(!this->kexit.empty()) for(u32 i = 0; i < this->kexit.size(); i++) if(idown & this->kexit[i])
            {
                (this->pages[this->cpageidx].getEventCallback())(Event(EventType::Exit));
                this->draw();
                this->exit();
            }
            else if(this->pagemenu && !this->controlmenu)
            {
                this->pagemenu = !this->pagemenu;
                this->draw();
            }
            else if(this->controlmenu && !this->pagemenu)
            {
                this->controlmenu = !this->controlmenu;
                this->draw();
            }
            else if(!this->pagemenu && !this->controlmenu)
            {
                (this->pages[this->cpageidx].getEventCallback())(Event(EventType::KeyDown));
                this->draw();
            }
        }
        else if(iup)
        {
            (this->pages[this->cpageidx].getEventCallback())(Event(EventType::KeyUp));
            this->draw();
        }
        else if(iheld)
        {
            (this->pages[this->cpageidx].getEventCallback())(Event(EventType::KeyHeld));
            this->draw();
        }
    }
}

void CustomUI::GUI::Window::exit()
{
    sdl_exit();
    if(this->aexit) ::exit(0);
}

bool CustomUI::GUI::Window::isInitialized()
{
    return sdlinit;
}

void CustomUI::GUI::Window::setExitKeys(vector<u64> Keys)
{
    this->kexit = Keys;
}

vector<u64> CustomUI::GUI::Window::getExitKeys()
{
    return this->kexit;
}