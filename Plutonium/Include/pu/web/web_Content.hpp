
/*

    Plutonium library

    @file web_Content.hpp
    @brief Basic code to use Horizon's WebApplet
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <switch.h>
#include <string>
#include <vector>
#include <functional>

namespace pu::web
{
    enum class WebContentType
    {
        HTMLSource,
        File,
        Directory,
        Video
    };

    bool CanShowWebContent();
    void ShowWebContent(std::string Input, WebContentType Type, std::function<void(WebCommonConfig*)> PreShow);
}