#include <pu/web/web_Content.hpp>
#include <pu/pu_CFW.hpp>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <functional>
#include <filesystem>

namespace pu::web
{
    static std::string webDir;

    static bool EnsureWebDir()
    {
        if(webDir.empty())
        {
            if(IsAtmosphere()) webDir = "sdmc:/atmosphere/hbl_html";
            else if(IsReiNX()) webDir = "sdmc:/ReiNX/hbl_html";
        }
        if(webDir.empty()) return false;
        mkdir(webDir.c_str(), 777);
        mkdir((webDir + "/html-document").c_str(), 777);
        return true;
    }

    static std::string CreateDocDir()
    {
        if(!EnsureWebDir()) return "";
        s32 n = rand();
        std::string docdir = "PuWeb-" + std::to_string(n) + ".htdocs";
        mkdir((webDir + "/html-document/" + docdir).c_str(), 777);
        return docdir;
    }

    static void LaunchApplet(std::string DocDir, std::string Entry = "index.html", std::function<void(WebCommonConfig*)> customprelaunch = [](WebCommonConfig*cfg){})
    {
        WebCommonConfig webcfg;
        if(webOfflineCreate(&webcfg, WebDocumentKind_OfflineHtmlPage, 0, (DocDir + "/" + Entry).c_str()) != 0) return;
        webConfigSetJsExtension(&webcfg, true);
        customprelaunch(&webcfg);
        WebCommonReply webr;
        webConfigShow(&webcfg, &webr);
    }

    static void CopyFile(std::string Source, std::string Dest)
    {
        FILE *inf = fopen(Source.c_str(), "rb");
        FILE *of = fopen(Dest.c_str(), "wb");
        u8 buf[8192] = {0};
        size_t rsize = 0;
        while((rsize = fread(buf, 1, 8192, inf)) > 0)
        {
            fwrite(buf, 1, rsize, of);
        }
        fclose(inf);
        fclose(of);
    }

    bool CanShowWebContent()
    {
        return EnsureWebDir();
    }

    void ShowWebContent(std::string Input, WebContentType Type, std::function<void(WebCommonConfig*)> PreShow)
    {
        switch(Type)
        {
            case WebContentType::HTMLSource:
            {
                auto docdir = CreateDocDir();
                if(docdir.empty()) return;
                std::ofstream ofs(webDir + "/html-document/" + docdir + "/index.html");
                ofs << Input;
                ofs.close();
                LaunchApplet(docdir, "index.html", PreShow);
                break;
            }
            case WebContentType::File:
            {
                auto docdir = CreateDocDir();
                if(docdir.empty()) return;
                CopyFile(Input, webDir + "/html-document/" + docdir + "/index.html");
                LaunchApplet(docdir, "index.html", PreShow);
                break;
            }
            case WebContentType::Directory:
            {
                std::ifstream ifs(Input + "/index.html");
                bool ok = ifs.good();
                ifs.close();
                if(!ok) return;
                auto docdir = CreateDocDir();
                if(docdir.empty()) return;
                std::filesystem::rename(Input, webDir + "/html-document/" + docdir);
                LaunchApplet(docdir, "index.html", PreShow);
                std::filesystem::rename(webDir + "/html-document/" + docdir, Input);
                break;
            }
            case WebContentType::Video:
            {
                auto docdir = CreateDocDir();
                if(docdir.empty()) return;
                std::string fname = Input.substr(Input.find_last_of("/") + 1);
                rename(Input.c_str(), (webDir + "/html-document/" + docdir + "/" + fname).c_str());
                LaunchApplet(docdir, fname, [&](WebCommonConfig *cfg)
                {
                    webConfigSetBootAsMediaPlayer(cfg, true);
                    PreShow(cfg);
                });
                rename((webDir + "/html-document/" + docdir + "/" + fname).c_str(), Input.c_str());
                break;
            }
        }
    }
}