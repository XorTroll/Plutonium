
#pragma once
#include <pu/render/render_Renderer.hpp>

namespace pu::ui {

    class Object {

        private:
            Mutex lock;

        public:
            Object() : lock(CreateMutex()) {}

            virtual s32 GetX() = 0;
            virtual s32 GetY() = 0;
            virtual s32 GetWidth() = 0;
            virtual s32 GetHeight() = 0;

            virtual void Render(render::Renderer &renderer) = 0;

            void DoRender(render::Renderer &renderer) PU_LOCKED_SCOPE(this->lock, {
                this->Render(renderer);
            })

            template<typename O, typename ...Args>
            inline static std::shared_ptr<Object> New(Args &&...args) {
                return NewInstance<Object, O>(args...);
            }
    };
}