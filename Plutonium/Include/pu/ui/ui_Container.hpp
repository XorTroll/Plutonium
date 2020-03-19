
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
            Container(i32 X, i32 Y, i32 Width, i32 Height);
            PU_SMART_CTOR(Container)

            template<typename Elem>
            void Add(std::shared_ptr<Elem> Elm)
            {
                static_assert(std::is_base_of<elm::Element, Elem>::value, "Elements must inherit from pu::ui::elm::Element!");

                elms.push_back(std::dynamic_pointer_cast<elm::Element>(Elm));
            }

            elm::Element::Ref &At(i32 Index);
            bool Has(elm::Element::Ref &Elm);
            void Clear();
            i32 GetCount();
            void SetX(i32 X);
            i32 GetX();
            void SetY(i32 Y);
            i32 GetY();
            void SetWidth(i32 Width);
            i32 GetWidth();
            void SetHeight(i32 Height);
            i32 GetHeight();
            void PreRender();
        protected:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            std::vector<elm::Element::Ref> elms;
    };
}