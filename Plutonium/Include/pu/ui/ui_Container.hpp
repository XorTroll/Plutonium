
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
            PU_SMART_CTOR(Container)

            template<typename Elem>
            void Add(std::shared_ptr<Elem> Elm)
            {
                static_assert(std::is_base_of<elm::Element, Elem>::value, "Elements must inherit from pu::ui::elm::Element!");

                elms.push_back(std::dynamic_pointer_cast<elm::Element>(Elm));
            }

            elm::Element::Ref &At(s32 Index);
            bool Has(elm::Element::Ref &Elm);
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
            std::vector<elm::Element::Ref> elms;
    };
}