#define ROCKS_CLAY_IMPLEMENTATION
#include "rocks.h"
#include "render.h"
#include "app.h"

int main(void) {
    Rocks_Config config = {
        .window_width = 1280,
        .window_height = 720,
        .window_title = "Waozi",
        .theme = {
            .background = (Clay_Color){245, 245, 245, 255},
            .primary = (Clay_Color){70, 130, 180, 255},
            .primary_hover = (Clay_Color){60, 120, 170, 255},
            .secondary = (Clay_Color){255, 255, 255, 255},
            .text = (Clay_Color){33, 33, 33, 255},
            .text_secondary = (Clay_Color){120, 120, 120, 255},
            .border = (Clay_Color){200, 200, 200, 255},
            .scrollbar_track = (Clay_Color){245, 245, 245, 200},
            .scrollbar_thumb = (Clay_Color){200, 200, 200, 255},
            .scrollbar_thumb_hover = (Clay_Color){180, 180, 180, 255}
        }
    };

    Rocks* rocks = Rocks_Init(config);
    if (!rocks) return 1;

    app_init(rocks);
    Rocks_Run(rocks, app_update);
    app_cleanup(rocks);

    return 0;
}