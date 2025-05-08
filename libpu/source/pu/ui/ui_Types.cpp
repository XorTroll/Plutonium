#include <pu/ui/ui_Types.hpp>

namespace pu::ui {

    namespace {

        constexpr size_t RGBColorSize = __builtin_strlen("#RRGGBB");
        constexpr size_t RGBAColorSize = __builtin_strlen("#RRGGBBAA");

    }

    Color Color::FromHex(const std::string &str) {
        // Sanity check the string length and format
        if((str.length() != RGBColorSize) && (str.length() != RGBAColorSize)) {
            return {};
        }
        if(str[0] != '#') {
            return {};
        }
        for(u32 i = 1; i < str.length(); i++) {
            if(!util::IsHexChar(str[i])) {
                return {};
            }
        }

        if(str.length() == RGBColorSize) {
            return Color::FromConstHexRGB(str.c_str());
        }
        else if(str.length() == RGBAColorSize) {
            return Color::FromConstHexRGBA(str.c_str());
        }

        // This should never happen, but just in case
        return {};
    }

}
