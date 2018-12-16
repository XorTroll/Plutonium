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
}