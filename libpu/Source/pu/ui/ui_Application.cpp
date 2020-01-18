#include <pu/ui/ui_Application.hpp>

namespace pu::ui {

    static Mutex g_application_instance_lock = pu::CreateMutex();
    static bool g_application_instance_created = false;
    static std::shared_ptr<Application> g_application_instance;

    Result Application::Initialize(render::Renderer renderer) PU_LOCKED_SCOPE(g_application_instance_lock, {
        if(!g_application_instance_created) {
            g_application_instance = std::make_shared<Application>(new Application(renderer));
            g_application_instance_created = true;
        }
        return Success;
    })

    std::shared_ptr<Application> Application::Get() PU_LOCKED_SCOPE(g_application_instance_lock, {
        if(g_application_instance_created) {
            return g_application_instance;
        }
        return nullptr;
    })
}