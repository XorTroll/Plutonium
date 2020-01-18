
#pragma once
#include <pu/ui/ui_Object.hpp>
#include <pu/render/render_Renderer.hpp>
#include <map>

namespace pu::ui {

    class Layout {

        private:
            Mutex lock;
            std::map<std::string, std::shared_ptr<Object>> object_table;

            void DoAddObject(const std::string &name, std::shared_ptr<Object> object) {
                auto f = this->object_table.find(name);
                if(f == this->object_table.end()) {
                    this->object_table.insert(std::make_pair(name, object));
                }  
            }

        public:
            Layout() : lock(CreateMutex()) {}

            void Add(const std::string &name, std::shared_ptr<Object> object) PU_LOCKED_SCOPE(this->lock, {
                this->DoAddObject(name, object);
            })

            template<typename T, typename ...Args>
            void CreateAdd(const std::string &name, Args &&...args) PU_LOCKED_SCOPE(this->lock, {
                auto obj = NewInstance<Object, T>(args...);
                this->DoAddObject(name, obj);
            })

            template<typename T>
            std::shared_ptr<T> GetByName(const std::string &name) {
                static_assert(std::is_same_v<Object, T> || std::is_base_of_v<Object, T>, "Demo");
                auto f = this->object_table.find(name);
                if(f != this->object_table.end()) {
                    return std::static_pointer_cast<T>(f->second);
                } 
                return nullptr;
            }

            void DoRender(render::Renderer &renderer) PU_LOCKED_SCOPE(this->lock, {
                for(auto &[name, obj] : this->object_table) {
                    obj->DoRender(renderer);
                }
            })

            template<typename L, typename ...Args>
            inline static std::shared_ptr<Layout> New(Args &&...args) {
                return NewInstance<Layout, L>(args...);
            }
    };
}