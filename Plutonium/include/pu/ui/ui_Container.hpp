
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

            inline elm::Element::Ref &At(const i32 idx) {
                return this->elems.at(idx);
            }

            inline bool Has(elm::Element::Ref &elem) {
                return std::find(this->elems.begin(), this->elems.end(), elem) != this->elems.end();
            }

            inline void Clear() {
                this->elems.clear();
            }

            inline size_t GetCount() {
                return this->elems.size();
            }

            inline void SetX(const i32 x) {
                this->x = x;
            }

            inline i32 GetX() {
                return this->x;
            }

            inline void SetY(const i32 y) {
                this->y = y;
            }

            inline i32 GetY() {
                return this->y;
            }

            inline void SetWidth(const i32 width) {
                this->w = width;
            }

            inline i32 GetWidth() {
                return this->w;
            }

            inline void SetHeight(const i32 height) {
                this->h = height;
            }
            
            inline i32 GetHeight() {
                return this->h;
            }

            void PreRender();
    };

}