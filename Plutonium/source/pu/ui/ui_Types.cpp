#include <pu/ui/ui_Types.hpp>

namespace pu::ui
{
    Color Color::FromHex(std::string HexFmt)
    {
        Color clr;
        std::string r = "00";
        std::string g = "00";
        std::string b = "00";
        std::string a = "FF";
        if(HexFmt.length() >= 9) a = HexFmt.substr(7, 2);
        if(HexFmt.length() >= 7)
        {
            r = HexFmt.substr(1, 2);
            g = HexFmt.substr(3, 2);
            b = HexFmt.substr(5, 2);
        }
        clr.R = (u8)std::stoul(r, nullptr, 16);
        clr.G = (u8)std::stoul(g, nullptr, 16);
        clr.B = (u8)std::stoul(b, nullptr, 16);
        clr.A = (u8)std::stoul(a, nullptr, 16);
        return clr;
    }
}