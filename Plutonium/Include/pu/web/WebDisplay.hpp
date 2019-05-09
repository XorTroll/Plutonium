
#pragma once
#include <pu/web/Web.hpp>

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