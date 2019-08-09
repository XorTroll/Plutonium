#include <pu/web/web_Display.hpp>

namespace pu::web
{
    WebDisplay::WebDisplay(std::string Input, WebContentType Type)
    {
        this->input = Input;
        this->type = Type;
    }

    bool WebDisplay::Show()
    {
        if(!CanShowWebContent()) return false;
        ShowWebContent(this->input, this->type, [&](WebCommonConfig *cfg)
        {
            if(!this->calls.empty()) for(s32 i = 0; i < this->calls.size(); i++)
            {
                (this->calls[i])(cfg);
            }
        });
    }

    void WebDisplay::SetWebAudio(bool Enabled)
    {
        this->calls.push_back([&](WebCommonConfig *cfg)
        {
            webConfigSetWebAudio(cfg, Enabled);
        });
    }

    WebDisplay *LoadFromHTML(std::string Source)
    {
        return new WebDisplay(Source, WebContentType::HTMLSource);
    }

    WebDisplay *LoadFromFile(std::string Path)
    {
        return new WebDisplay(Path, WebContentType::File);
    }

    WebDisplay *LoadFromDirectory(std::string Path)
    {
        return new WebDisplay(Path, WebContentType::Directory);
    }

    WebDisplay *LoadFromVideo(std::string Path)
    {
        return new WebDisplay(Path, WebContentType::Video);
    }
}