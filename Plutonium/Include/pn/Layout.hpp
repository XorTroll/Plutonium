
#pragma once
#include <pn/fw.hpp>

namespace pn
{
    class Layout
    {
        public:
            void AddChild(fw::Element *Child);
            void ClearChildren();
            fw::Element *GetChildAt(u32 Index);
            u32 GetChildCount();
            bool HasChilds();
        private:
            std::vector<fw::Element*> chld;
    };
}