#include <pu/ui/ui_Types.hpp>

namespace pu::ui {

    Color Color::FromHex(const std::string &str_clr) {
        // Format: '#rrggbbaa'

        std::string r = "00";
        std::string g = "00";
        std::string b = "00";
        std::string a = "FF";

        if(str_clr.length() >= 9) {
            a = str_clr.substr(7, 2);
        }
        if(str_clr.length() >= 7)
        {
            r = str_clr.substr(1, 2);
            g = str_clr.substr(3, 2);
            b = str_clr.substr(5, 2);
        }
        
        const auto r_val = static_cast<u8>(std::stoul(r, nullptr, 16));
        const auto g_val = static_cast<u8>(std::stoul(g, nullptr, 16));
        const auto b_val = static_cast<u8>(std::stoul(b, nullptr, 16));
        const auto a_val = static_cast<u8>(std::stoul(a, nullptr, 16));
        return { r_val, g_val, b_val, a_val };
    }

}