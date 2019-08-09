
/*

    Plutonium library

    @file ui_Container.hpp
    @brief A Container is a basic object which contains a bunch of Elements.
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <vector>

namespace pu::ui
{
    class Container
    {
        public:
            Container(s32 X, s32 Y, s32 Width, s32 Height);
            void Add(elm::Element *Elm);
            elm::Element *At(s32 Index);
            bool Has(elm::Element *Elm);
            void Clear();
            s32 GetCount();
            void SetX(s32 X);
            s32 GetX();
            void SetY(s32 Y);
            s32 GetY();
            void SetWidth(s32 Width);
            s32 GetWidth();
            void SetHeight(s32 Height);
            s32 GetHeight();
            void PreRender();
        protected:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            std::vector<elm::Element*> elms;
    };
}