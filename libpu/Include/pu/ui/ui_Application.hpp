
#pragma once
#include <pu/ui/ui_Layout.hpp>
#include <pu/render/render_Renderer.hpp>
#include <map>
#include <utility>

namespace pu::ui {

    class Application {

        private:
            bool running;
            Mutex lock;
            render::Renderer renderer;
            std::map<std::string, std::shared_ptr<Layout>> layout_table;
            std::string current_layout_name;

            Application(render::Renderer render) : running(false), lock(EmptyMutex), renderer(render) {}

            void DoAddLayout(const std::string &name, std::shared_ptr<Layout> layout) {
                if(this->layout_table.empty()) {
                    this->current_layout_name = name;
                }
                auto f = this->layout_table.find(name);
                if(f == this->layout_table.end()) {
                    this->layout_table.insert(std::make_pair(name, layout));
                }
            }

            void OnRenderCall() PU_LOCKED_SCOPE(this->lock, {
                if(renderer.IsValid()) {
                    SDL_SetRenderDrawColor(renderer.renderer, 0xff, 0xff, 0xff, 0xff);
                    SDL_RenderClear(renderer.renderer);
                    hidScanInput();
                    auto flyt = this->layout_table.find(this->current_layout_name);
                    if(flyt != this->layout_table.end()) {
                        auto lyt = flyt->second;
                        lyt->OnInputCall();
                        lyt->OnRenderCall();
                    }
                    SDL_RenderPresent(renderer.renderer);
                }
            })

        public:
            Application() = delete;
            Application(Application *ptr) : lock(ptr->lock), renderer(ptr->renderer) {}

            void Add(const std::string &name, std::shared_ptr<Layout> layout) PU_LOCKED_SCOPE(this->lock, {
                this->DoAddLayout(name, layout);
            })

            template<typename T, typename ...Args>
            void CreateAdd(const std::string &name, Args &&...args) PU_LOCKED_SCOPE(this->lock, {
                auto lyt = NewInstance<Layout, T>(args...);
                this->DoAddLayout(name, lyt);
            })

            template<typename T>
            std::shared_ptr<T> GetByName(const std::string &name) {
                static_assert(std::is_same_v<Layout, T> || std::is_base_of_v<Layout, T>, "Return type must be Layout or a derived class!");
                auto f = this->layout_table.find(name);
                if(f != this->layout_table.end()) {
                    return std::static_pointer_cast<T>(f->second);
                } 
                return nullptr;
            }

            render::Renderer &GetRenderer() {
                return this->renderer;
            }

            std::pair<u32, u32> GetDimensions() {
                i32 w = 0;
                i32 h = 0;
                if(this->renderer.IsValid()) {
                    SDL_GetWindowSize(renderer.window, &w, &h);
                }
                return std::make_pair((u32)w, (u32)h);
            }

            void SetDimensions(i32 w, i32 h) {
                if(this->renderer.IsValid()) {
                    SDL_SetWindowSize(renderer.window, w, h);
                }
            }

            void SetCurrentLayout(const std::string &name) PU_LOCKED_SCOPE(this->lock, {
                auto f = this->layout_table.find(name);
                if(f != this->layout_table.end()) {
                    this->current_layout_name = name;
                }
            })

            void Show() {
                this->running = true;
                while(appletMainLoop() && running) {
                    this->OnRenderCall();
                }
            }

            void Close() PU_LOCKED_SCOPE(this->lock, {
                this->running = false;
            })

        public:
            static Result Initialize(render::Renderer renderer);
            static std::shared_ptr<Application> Get();

    };

    inline Result InitializeApplication(render::Renderer renderer) {
        return Application::Initialize(renderer);
    }
    
    inline std::shared_ptr<Application> GetApplication() {
        return Application::Get();
    }
}