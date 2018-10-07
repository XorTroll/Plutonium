#include "Color.hpp"

CustomUI::GUI::Color::Color()
{
    this->Red = 0;
    this->Green = 0;
    this->Blue = 0;
    this->Alpha = 255;
}

CustomUI::GUI::Color::Color(u8 Red, u8 Green, u8 Blue)
{
    this->Red = Red;
    this->Green = Green;
    this->Blue = Blue;
    this->Alpha = 255;
}

CustomUI::GUI::Color::Color(u8 Red, u8 Green, u8 Blue, u8 Alpha)
{
    this->Red = Red;
    this->Green = Green;
    this->Blue = Blue;
    this->Alpha = Alpha;
}