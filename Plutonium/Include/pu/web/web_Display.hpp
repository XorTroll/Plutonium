
/*

    Plutonium library

    @file web_Display.hpp
    @brief A custom string class to support UTF16 and UTF8 -> UTF16 conversion
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/web/web_Content.hpp>

namespace pu::web
{
    class WebDisplay
    {
        public:
            WebDisplay(std::string Input, WebContentType InputType);
            bool Show();
            void SetWebAudio(bool Enabled);
        private:
            std::string input;
            WebContentType type;
            std::vector<std::function<void(WebCommonConfig*)>> calls;
    };

    WebDisplay *LoadFromHTML(std::string Source);
    WebDisplay *LoadFromFile(std::string Path);
    WebDisplay *LoadFromDirectory(std::string Path);
    WebDisplay *LoadFromVideo(std::string Path);
}