#include <pu/draw/Color.hpp>

namespace pu::draw
{
    Color::Color()
    {
        this->R = 0;
        this->G = 0;
        this->B = 0;
        this->A = 255;
    }

    Color::Color(u8 R, u8 G, u8 B, u8 A)
    {
        this->R = R;
        this->G = G;
        this->B = B;
        this->A = A;
    }

    Color Color::FromHex(std::string HexFmt)
    {
        Color clr;
        if(HexFmt[0] == '#')
        {
            std::string r = "00", g = "00", b = "00", a = "ff";
            if(HexFmt.length() == 7)
            {
                r = HexFmt.substr(1, 2);
                g = HexFmt.substr(3, 2);
                b = HexFmt.substr(5, 2);
            }
            if(HexFmt.length() >= 9) a = HexFmt.substr(7, 2);
            clr.R = std::stoul(r, NULL, 16);
            clr.G = std::stoul(g, NULL, 16);
            clr.B = std::stoul(b, NULL, 16);
            clr.A = std::stoul(a, NULL, 16);
        }
        return clr;
    }
}