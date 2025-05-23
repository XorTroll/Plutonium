/**
 * Plutonium library
 * @file ui_Container.hpp
 * @brief Contains pu::ui::Container class
 * @author XorTroll
 * @copyright XorTroll
 */

#pragma once
#include <pu/ui/elm/elm_Element.hpp>
#include <vector>
#include <bits/stdc++.h>

namespace pu::ui {

    /**
     * @brief Type containing a list of elements.
     */
    class Container {
        protected:
            s32 x;
            s32 y;
            s32 w;
            s32 h;
            std::vector<elm::Element::Ref> elems;

        public:
            /**
             * @brief Creates a new Container with the specified position and size.
             * @param x The X position of the Container.
             * @param y The Y position of the Container.
             * @param width The width of the Container.
             * @param height The height of the Container.
             */
            Container(const s32 x, const s32 y, const s32 width, const s32 height) : x(x), y(y), w(width), h(height), elems() {}
            PU_SMART_CTOR(Container)

            /**
             * @brief Adds an Element to the Container.
             * @param elem The Element to add.
             */
            inline void Add(elm::Element::Ref elem) {
                this->elems.push_back(elem);
            }

            /**
             * @brief Gets the list of Elements in the Container.
             * @return The list of Elements in the Container.
             */
            inline std::vector<elm::Element::Ref> &GetElements() {
                return this->elems;
            }

            /**
             * @brief Gets whether the Container has the specified Element.
             * @param elem The Element to check.
             * @return Whether the Container has the specified Element.
             */
            inline bool Has(elm::Element::Ref &elem) {
                return std::find(this->elems.begin(), this->elems.end(), elem) != this->elems.end();
            }

            /**
             * @brief Removes all elements from the Container.
             */
            inline void Clear() {
                this->elems.clear();
            }

            PU_CLASS_POD_GETSET(X, x, s32)
            PU_CLASS_POD_GETSET(Y, y, s32)
            PU_CLASS_POD_GETSET(Width, w, s32)
            PU_CLASS_POD_GETSET(Height, h, s32)

            /**
             * @brief Function to be invoked before rendering the Container.
             * @note This function is not meant to be called by the user. Application will call it internally.
             */
            void PreRender();
    };

}
