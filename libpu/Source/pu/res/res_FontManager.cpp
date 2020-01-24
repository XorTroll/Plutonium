#include <pu/res/res_FontManager.hpp>

namespace pu::res {

    static std::map<std::string, std::shared_ptr<ttf::Font>> g_font_table;

    Result LoadFont(const std::string &name, std::shared_ptr<ttf::Font> font) {
        PU_RESULT_UNLESS(sdl2::ttf::IsInitialized(), result::ResultTTFNotInitialized);

        auto f = g_font_table.find(name);
        if(f == g_font_table.end()) {
            g_font_table.insert(std::make_pair(name, font));
        }
        return Success;
    }

    Result LoadSystemSharedFont(const std::string &name) {
        PU_RESULT_UNLESS(sdl2::ttf::IsInitialized(), result::ResultTTFNotInitialized);

        auto font = NewInstance<ttf::Font>();
        for(u32 i = 0; i < PlSharedFontType_Total; i++) {
            PlFontData data = {};
            auto rc = plGetSharedFontByType(&data, (PlSharedFontType)i);
            if(R_SUCCEEDED(rc)) {
                font->LoadFromMemory(data.address, data.size, &ttf::EmptyFontFaceDisposingFunction);
            }
        }
        return LoadFont(name, font);
    }

    Result LoadExternalFont(const std::string &name, const std::string &path) {
        PU_RESULT_UNLESS(sdl2::ttf::IsInitialized(), result::ResultTTFNotInitialized);
        
        auto font = NewInstance<ttf::Font>();
        font->LoadFromFile(path);
        return LoadFont(name, font);
    }

    std::shared_ptr<ttf::Font> GetFontByName(const std::string &name, i32 size) {
        auto f = g_font_table.find(name);
        if(f != g_font_table.end()) {
            auto font = f->second;
            if(size >= 0) {
                font->SetSize((u32)size);
            }
            return font;
        } 
        return nullptr;
    }

    void UnloadFontByName(const std::string &name) {
        auto f = g_font_table.find(name);
        if(f != g_font_table.end()) {
            g_font_table.erase(name);
        } 
    }

}