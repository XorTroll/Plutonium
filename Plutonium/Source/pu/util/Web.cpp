#include <pu/util/Web.hpp>
#include <pu/util/CFW.hpp>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <functional>

namespace pu::util
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
        u32 n = rand();
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

    void ShowWebContentFromFile(std::string Path)
    {
        auto docdir = CreateDocDir();
        if(docdir.empty()) return;
        CopyFile(Path, webDir + "/html-document/" + docdir + "/index.html");
        LaunchApplet(docdir);
    }

    void ShowWebContentFromDirectory(std::string Dir)
    {

    }

    void ShowWebContent(std::string HTMLSource)
    {
        auto docdir = CreateDocDir();
        if(docdir.empty()) return;
        std::ofstream ofs(webDir + "/html-document/" + docdir + "/index.html");
        ofs << HTMLSource;
        ofs.close();
        LaunchApplet(docdir);
    }

    void ShowVideo(std::string Path)
    {
        auto docdir = CreateDocDir();
        if(docdir.empty()) return;
        std::string fname = Path.substr(Path.find_last_of("/") + 1);
        rename(Path.c_str(), (webDir + "/html-document/" + docdir + "/" + fname).c_str());
        LaunchApplet(docdir, fname, [](WebCommonConfig *cfg)
        {
            webConfigSetBootAsMediaPlayer(cfg, true);
        });
        rename((webDir + "/html-document/" + docdir + "/" + fname).c_str(), Path.c_str());
    }
}