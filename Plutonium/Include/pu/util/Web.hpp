
#pragma once
#include <switch.h>
#include <string>

namespace pu::util
{
    bool CanShowWebContent();
    void ShowWebContentFromFile(std::string Path);
    void ShowWebContentFromDirectory(std::string Dir);
    void ShowWebContent(std::string HTMLSource);
    void ShowVideo(std::string Path);
}