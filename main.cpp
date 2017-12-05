#include <iostream>
#include <wayland-egl.h>
using namespace std;

int main()
{
    wl_display* display = nullptr;
    wl_registry* registry = nullptr;
    display = wl_display_connect(nullptr);
    if (display == nullptr) {
        cout << "ERROR: Can't connect to wayland display!" << endl;
        return -1;
    }
    registry = wl_display_get_registry(display);
    wl_registry_add_listener(registry, nullptr, nullptr);


    wl_display_disconnect(display);

    cout << "Work Finished!" << endl;
    return 0;
}

