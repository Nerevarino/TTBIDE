#include "application.h"
using namespace std;

Application::Application(int argc, char* argv[])
{

}

Application::~Application()
{

}

int Application::run()
{
    display = wl_display_connect(nullptr);
    if (display == nullptr) {
        cout << "ERROR: Can't connect to wayland display!" << endl;
        return -1;
    }
    registry = wl_display_get_registry(display);
    if (registry == nullptr) {
        cout << "ERROR: Can't get registry from wayland display!" << endl;
        return -1;
    }

    wl_registry_add_listener(registry, &registery_listener, this);
    int success_count = wl_display_dispatch(display);


    cout << success_count << " events has been processed" << endl;
    cout << "Work finished!" << endl;
    return 0;
}

void Application::onAddWaylandObject
    (
        void* client_data,
        wl_registry* registry,
        uint32_t object_id,
        const char* interface_name,
        uint32_t version
    )
{
    Application* app = (Application*)client_data;

    cout << "Here is a registry event for " << interface_name << " with id = " << object_id << endl;
}

void Application::onRemoveWaylandObject
    (
        void* client_data,
        wl_registry* registry,
        uint32_t object_id
    )
{
    Application* app = (Application*)client_data;
}
