#include "Background.hpp"

CustomUI::GUI::Background::Background()
{
    this->btype = BackgroundType::SolidColor;
    this->base = { 235, 235, 235, 255 };
}

CustomUI::GUI::Background::Background(string Path)
{
    this->btype = BackgroundType::Image;
    this->path = Path;
}

CustomUI::GUI::Background::Background(Color SolidColor)
{
    this->btype = BackgroundType::SolidColor;
    this->base = SolidColor;
}

CustomUI::GUI::Background::Background(Color Gradient1, Color Gradient2, GradientDirection Direction)
{
    this->btype = BackgroundType::Gradient;
    this->base = Gradient1;
    this->gradient = Gradient2;
    this->gdir = Direction;
}

CustomUI::GUI::BackgroundType CustomUI::GUI::Background::getType()
{
    return this->btype;
}

void CustomUI::GUI::Background::setImage(string Path)
{
    this->btype = BackgroundType::Image;
    this->path = Path;
}

string CustomUI::GUI::Background::getImage()
{
    return this->path;
}

void CustomUI::GUI::Background::setColor(Color SolidColor)
{
    this->btype = BackgroundType::SolidColor;
    this->base = SolidColor;
}

CustomUI::GUI::Color CustomUI::GUI::Background::getColor()
{
    return this->base;
}

void CustomUI::GUI::Background::setGradientColors(Color Gradient1, Color Gradient2)
{
    this->btype = BackgroundType::Gradient;
    this->base = Gradient1;
    this->gradient = Gradient2;
}

CustomUI::GUI::Color CustomUI::GUI::Background::getGradientColor1()
{
    return this->base;
}

CustomUI::GUI::Color CustomUI::GUI::Background::getGradientColor2()
{
    return this->gradient;
}

void CustomUI::GUI::Background::setGradientDirection(GradientDirection Direction)
{
    this->btype = BackgroundType::Gradient;
    this->gdir = Direction;
}

CustomUI::GUI::GradientDirection CustomUI::GUI::Background::getGradientDirection()
{
    return this->gdir;
}