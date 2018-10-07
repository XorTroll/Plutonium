
#pragma once
#include "Color.hpp"

namespace CustomUI
{
    namespace GUI
    {
        enum class GradientDirection
        {
            TopToBottom,
            BottomToTop,
        };

        enum class BackgroundType
        {
            Image,
            SolidColor,
            Gradient,
        };

        class Background
        {
            public:
                Background();
                Background(string Path);
                Background(Color SolidColor);
                Background(Color Gradient1, Color Gradient2, GradientDirection Direction);
                BackgroundType getType();
                void setImage(string Path);
                string getImage();
                void setColor(Color SolidColor);
                Color getColor();
                void setGradientColors(Color Gradient1, Color Gradient2);
                Color getGradientColor1();
                Color getGradientColor2();
                void setGradientDirection(GradientDirection Direction);
                GradientDirection getGradientDirection();
            private:
                string path;
                Color base;
                Color gradient;
                GradientDirection gdir;
                BackgroundType btype;
        };
    }
}