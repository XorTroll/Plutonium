
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
#include <bits/stdc++.h>

namespace pu::ui {

    class Container {
        protected:
            i32 x;
            i32 y;
            i32 w;
            i32 h;
            std::vector<elm::Element::Ref> elems;

        public:
            Container(const i32 x, const i32 y, const i32 width, const i32 height) : x(x), y(y), w(width), h(height), elems() {}
            PU_SMART_CTOR(Container)

            inline void Add(elm::Element::Ref elem) {
                this->elems.push_back(elem);
            }

            inline std::vector<elm::Element::Ref> &GetElements() {
                return this->elems;
            }

            inline bool Has(elm::Element::Ref &elem) {
                return std::find(this->elems.begin(), this->elems.end(), elem) != this->elems.end();
            }

            inline void Clear() {
                this->elems.clear();
            }

            PU_CLASS_POD_GETSET(X, x, i32)
            PU_CLASS_POD_GETSET(Y, y, i32)
            PU_CLASS_POD_GETSET(Width, w, i32)
            PU_CLASS_POD_GETSET(Height, h, i32)

            void PreRender();
    };

}
