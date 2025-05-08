#include <pu/ui/ui_Style.hpp>

namespace pu::ui {

    namespace {

        Style::Ref g_Style = nullptr;

    }

    void SetStyle(Style::Ref style) {
        g_Style = style;

        /*
        atexit([]() {
            if(g_Style != nullptr) {
                g_Style.reset();
                g_Style = nullptr;
            }
        });
        */
    }

    Style::Ref GetStyle() {
        return g_Style;
    }

}
