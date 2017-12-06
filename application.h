#ifndef APPLICATION_H
#define APPLICATION_H

//dependencies
#include <iostream>
#include <wayland-egl.h>
//dependencies



class Application
{
    protected: wl_display* display = nullptr;
    protected: wl_registry* registry = nullptr;

    protected: wl_compositor* compositor = nullptr;
    protected: wl_surface* surface = nullptr;
    protected: wl_shell_surface* shell_surface = nullptr;






    public: Application(int argc, char* argv[]);
    public: ~Application();

    public: int run();

    public: static void onAddWaylandObject
        (
            void* client_data,
            wl_registry* registry,
            uint32_t object_id,
            const char* interface_name,
            uint32_t version
        );
    public: static void onRemoveWaylandObject
        (
            void* client_data,
            wl_registry* registry,
            uint32_t object_id
        );

    public: const wl_registry_listener registery_listener =
        {
          .global = Application::onAddWaylandObject,
          .global_remove = Application::onRemoveWaylandObject
        };

};

#endif // APPLICATION_H
