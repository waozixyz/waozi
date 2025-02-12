#define ROCKS_CLAY_IMPLEMENTATION
#include "rocks.h"
#include <ctype.h>

enum {
    FONT_TITLE = 0,
    FONT_BODY = 1,
    FONT_COUNT
};

static uint16_t g_font_ids[FONT_COUNT];
static void* g_logo_image;
static void* g_project_images[6];

typedef struct {
    const char* title;
    const char* description;
    void* image;
    const char* link;
} Project;

static Project g_projects[] = {
    {
        .title = "Rocks",
        .description = "Framework for Clay, providing an easy way to change renderers and use premade components",
        .image = NULL,
        .link = "https://github.com/naoxio/rocks"
    },
    {
        .title = "Quest",
        .description = "A personal life managment app focused on habit tracking, task organizatino and life visualization.",
        .image = NULL,
        .link = "http://quest.naox.io/"
    },
    {
        .title = "Inner Breeze",
        .description = "Guided breathing meditation app based on the Wim Hof breathing method.",
        .image = NULL,
        .link = "https://inbreeze.xyz"
    },
    {
        .title = "Carousel",
        .description = "A fun lightweight spin the wheel tool.",
        .image = NULL,
        .link = "https://carousel.waozi.xyz"
    },
    {
        .title = "Algotree",
        .description = "Single header C library to draw 3d or 2d algorithmically grown trees in Raylib.",
        .image = NULL,
        .link = "https://github.com/waozixyz/algotree"
    }
};

typedef struct {
    const char* platform;
    const char* contact;
} Connection;

static Connection g_connections[] = {
    {"GitHub", "@waozixyz"},
    {"X/Twitter", "@waozixyz"},
    {"Nostr", "@waozi@ditto.pub"},
    {"Telegram", "@waozixyz"},
    {"Email", "hello@waozi.xyz"}
};

char* get_image_filename(const char* project_name, char* buffer, size_t buffer_size) {
    int j = 0;
    for (int i = 0; project_name[i] && j < buffer_size - 1; i++) {
        if (project_name[i] == ' ') {
            buffer[j++] = '_';
        } else {
            buffer[j++] = tolower(project_name[i]);
        }
    }
    buffer[j] = '\0';
    return buffer;
}


static void render_project_card(Rocks* rocks, Project project) {
    Rocks_Theme theme = Rocks_GetTheme(rocks);
    Clay_String title = { .chars = project.title, .length = strlen(project.title) };
    Clay_String description = { .chars = project.description, .length = strlen(project.description) };
    Clay_Dimensions image_dims = Rocks_GetImageDimensions(rocks, project.image);
    
    CLAY({
        .layout = {
            .sizing = { CLAY_SIZING_FIXED(300), CLAY_SIZING_FIXED(400) },
            .padding = CLAY_PADDING_ALL(20),
            .childGap = 15,
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .backgroundColor = theme.secondary,
        .cornerRadius = CLAY_CORNER_RADIUS(8),
        .border = {
            .color = theme.border,
            .width = { 1, 1, 1, 1 }
        }
    }) {
        // Project image
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_FIXED(260), CLAY_SIZING_FIXED(180) }
            },
            .image = {
                .imageData = project.image,
                .sourceDimensions = image_dims
            }
        }) {}

        // Title
        CLAY_TEXT(title, CLAY_TEXT_CONFIG({
            .textColor = theme.text,
            .fontSize = 20,
            .fontId = g_font_ids[FONT_TITLE]
        }));

        CLAY_TEXT(description, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 16,
            .fontId = g_font_ids[FONT_BODY]
        }));

        // Visit button
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(40) },
                .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
            },
            .backgroundColor = theme.primary,
            .cornerRadius = CLAY_CORNER_RADIUS(4)
        }) {
            CLAY_TEXT(CLAY_STRING("Visit Project"), CLAY_TEXT_CONFIG({
                .textColor = theme.secondary,
                .fontSize = 16,
                .fontId = g_font_ids[FONT_BODY]
            }));
        }
    }
}

static void render_connection_card(Rocks* rocks, Connection connection) {
    Rocks_Theme theme = Rocks_GetTheme(rocks);
    Clay_String platform = { .chars = connection.platform, .length = strlen(connection.platform) };
    Clay_String contact = { .chars = connection.contact, .length = strlen(connection.contact) };
    
    CLAY({
        .layout = {
            .sizing = { CLAY_SIZING_FIXED(200), CLAY_SIZING_FIXED(100) },
            .padding = CLAY_PADDING_ALL(15),
            .childGap = 10,
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
        },
        .backgroundColor = theme.secondary,
        .cornerRadius = CLAY_CORNER_RADIUS(8),
        .border = {
            .color = theme.border,
            .width = { 1, 1, 1, 1 }
        }
    }) {
        CLAY_TEXT(platform, CLAY_TEXT_CONFIG({
            .textColor = theme.text,
            .fontSize = 18,
            .fontId = g_font_ids[FONT_TITLE]
        }));

        CLAY_TEXT(contact, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 16,
            .fontId = g_font_ids[FONT_BODY]
        }));
    }
}

static Clay_RenderCommandArray app_update(Rocks* rocks, float dt) {
    Rocks_Theme theme = Rocks_GetTheme(rocks);
    Clay_Dimensions logo_dims = Rocks_GetImageDimensions(rocks, g_logo_image);
    
    Clay_BeginLayout();
    
    CLAY({
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .childGap = 40,
            .padding = CLAY_PADDING_ALL(20)
        },
            .scroll = { .vertical = true, .horizontal = false },
        .backgroundColor = theme.background
    }) {
        
        // Logo section
        CLAY({
            .layout = {
                        .sizing = { CLAY_SIZING_FIXED(128), CLAY_SIZING_FIXED(128) },
                .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
            },
            .image = {
                .imageData = g_logo_image,
                .sourceDimensions = logo_dims
            }
        }) {}

        // Projects grid
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
                .childGap = 20,
                .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
            }
        }) {
            for (int i = 0; i < sizeof(g_projects)/sizeof(g_projects[0]); i++) {
                render_project_card(rocks, g_projects[i]);
            }
        }

        // Footer
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(200) },
                .childGap = 20,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .padding = CLAY_PADDING_ALL(20)
            }
        }) {
            CLAY_TEXT(CLAY_STRING("Connect with me:"), CLAY_TEXT_CONFIG({
                .textColor = theme.text,
                .fontSize = 24,
                .fontId = g_font_ids[FONT_TITLE]
            }));

            CLAY({
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                    .childGap = 20,
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
                }
            }) {
                for (int i = 0; i < sizeof(g_connections)/sizeof(g_connections[0]); i++) {
                    render_connection_card(rocks, g_connections[i]);
                }
            }
        }
    }
    
    return Clay_EndLayout();
}
int main(void) {
    Rocks_Config config = {
        .window_width = 1280,
        .window_height = 720,
        .window_title = "My Portfolio",
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

    #ifdef ROCKS_USE_RAYLIB
    Rocks_RaylibConfig raylib_config = {
        .screen_width = 1280,
        .screen_height = 720
    };
    config.renderer_config = &raylib_config;
    #endif

    Rocks* rocks = Rocks_Init(config);
    if (!rocks) return 1;

    // Load fonts
    g_font_ids[FONT_TITLE] = Rocks_LoadFont("assets/Roboto-Bold.ttf", 24, FONT_TITLE);
    g_font_ids[FONT_BODY] = Rocks_LoadFont("assets/Roboto-Regular.ttf", 16, FONT_BODY);

    // Load images
    g_logo_image = Rocks_LoadImage(rocks, "assets/logo.png");

    for (int i = 0; i < 5; i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_projects[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/projects/%s.png", filename);
        printf("Loading image: %s\n", path); // Debug print
        g_project_images[i] = Rocks_LoadImage(rocks, path);
        g_projects[i].image = g_project_images[i];
    }

    Rocks_Run(rocks, app_update);
    
    // Cleanup
    Rocks_UnloadFont(g_font_ids[FONT_TITLE]);
    Rocks_UnloadFont(g_font_ids[FONT_BODY]);
    Rocks_UnloadImage(rocks, g_logo_image);
    for (int i = 0; i < 5; i++) {
        Rocks_UnloadImage(rocks, g_project_images[i]);
    }
    Rocks_Cleanup(rocks);
    
    return 0;
}
