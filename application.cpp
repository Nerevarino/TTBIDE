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

    surface = wl_compositor_create_surface(compositor);
    if (surface == nullptr) {
        cout << "ERROR: can't create surface!" << endl;
    }
    shm_pool = wl_shm_create_pool(shm, 0, 0);
    if (shm_pool == nullptr) {
        cout << "ERROR: Can't create shm_pool!" << endl;
    }


    cout << "content_buffer[Front] = " << content_buffers[Front] << endl;
    cout << "content_buffer[Back] = " << content_buffers[Back] << endl;
    content_buffers[Front] = wl_shm_pool_create_buffer(shm_pool,0,800,600,4,WL_SHM_FORMAT_ARGB8888);
    content_buffers[Back] = wl_shm_pool_create_buffer(shm_pool,1920000,800,600,4,WL_SHM_FORMAT_ARGB8888);
    if (content_buffers[Front] == nullptr) {
        cout << "ERROR: Can't create front wl_buffer!" << endl;
    }
    if (content_buffers[Back] == nullptr) {
        cout << "ERROR: Can't create back wl_buffer!" << endl;
    }
    cout << "content_buffer[Front] = " << content_buffers[Front] << endl;
    cout << "content_buffer[Back] = " << content_buffers[Back] << endl;

    wl_surface_attach(surface,content_buffers[Front],0,0);
    shell_surface = wl_shell_get_shell_surface(shell,surface);
    if (shell_surface == nullptr) {
        cout << "ERROR: Can't create shell surface!" << endl;
    }
    cout << "shell_surface = " << shell_surface << endl;
    wl_shell_surface_set_toplevel(shell_surface);
    wl_egl_window_create(surface,800,600);

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
    if (string(interface_name) == string("wl_compositor")) {
        app->compositor = (wl_compositor*)wl_registry_bind(registry,object_id,&wl_compositor_interface,1);
    } else if (string(interface_name) == string("wl_shm")) {
        app->shm = (wl_shm*)wl_registry_bind(registry,object_id,&wl_shm_interface,1);
    } else if (string(interface_name) == string("wl_seat")) {
        app->seat = (wl_seat*)wl_registry_bind(registry,object_id,&wl_seat_interface,1);
    } else if (string(interface_name) == string("wl_shell")) {
        app->shell = (wl_shell*)wl_registry_bind(registry,object_id,&wl_shell_interface,1);
    } else if (string(interface_name) == string("wl_output")) {
        app->output = (wl_output*)wl_registry_bind(registry,object_id,&wl_output_interface,1);
    } else {}
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
