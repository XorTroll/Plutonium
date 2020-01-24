
#pragma once
#include <pu/ui/ui_Types.hpp>
#include <pu/render/render_Renderer.hpp>

namespace pu::ui {

    class Object {

        private:
            Mutex lock;

        public:
            Object() : lock(EmptyMutex) {}

            virtual PositionAndSize GetPositionAndSize() = 0;
            virtual void OnRender() = 0;
            virtual void OnInput() = 0;

            void OnRenderCall() PU_LOCKED_SCOPE(this->lock, {
                this->OnRender();
            })

            void OnInputCall() PU_LOCKED_SCOPE(this->lock, {
                this->OnInput();
            })

            template<typename O, typename ...Args>
            inline static std::shared_ptr<Object> New(Args &&...args) {
                return NewInstance<Object, O>(args...);
            }
    };
}