#include <pu/ui/ui_Container.hpp>

namespace pu::ui {

    void Container::PreRender() {
        for(auto &elm : this->elems) {
            elm->SetParentContainer(this);
        }
    }

}