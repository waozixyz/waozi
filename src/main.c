#define ROCKS_CLAY_IMPLEMENTATION
#include "rocks.h"
#include "components/grid.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum {
    FONT_TITLE = 0,
    FONT_BODY = 1,
    FONT_COUNT
};

static uint16_t g_font_ids[FONT_COUNT];
static void* g_logo_image;
static void* g_project_images[10];

static Rocks_Grid* g_naox_projects_grid = NULL;
static Rocks_Grid* g_personal_projects_grid = NULL;
static Rocks_Grid* g_blog_grid = NULL;
static Rocks_Grid* g_connections_grid = NULL;



typedef struct {
    const char* title;
    const char* description;
    void* image;
    const char* link;
} Project;


// Split the projects into two arrays
static Project g_naox_projects[] = {
    {
        .title = "Rocks",
        .description = "Framework for Clay, providing an easy way to change renderers and use premade components",
        .image = NULL,
        .link = "https://github.com/naoxio/rocks"
    },
    {
        .title = "Quest",
        .description = "A personal life management app focused on habit tracking, task organization and life visualization.",
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
        .title = "NaoX",
        .description = "Explore more innovative projects and solutions at NaoX, where technology meets creativity.",
        .image = NULL,
        .link = "https://naox.io"
    }
};

static Project g_personal_projects[] = {
    {
        .title = "Kasaival",
        .description = "A minimal and fast HTTP server written in C.",
        .image = NULL,
        .link = "https://github.com/waozixyz/kasaival"
    },
    {
        .title = "Algotree",
        .description = "Single header C library to draw 3d or 2d algorithmically grown trees in Raylib.",
        .image = NULL,
        .link = "https://github.com/waozixyz/algotree"
    }
};


typedef struct {
    const char* title;
    const char* description;
    const char* date;
    const char* link;
} BlogPost;

typedef struct {
    const char* platform;
    const char* contact;
} Connection;


static BlogPost g_blog_posts[] = {
    {
        .title = "Coming Soon",
        .description = "Technical articles and insights coming soon...",
        .date = "2024",
        .link = "#"
    },
    {
        .title = "Stay Tuned",
        .description = "More content is on the way!",
        .date = "2024",
        .link = "#"
    }
};

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

const int PROJECT_CARD_WIDTH = 256;
const int PROJECT_CARD_HEIGHT = 300;

// Create and configure naox projects grid
Rocks_GridConfig naox_projects_grid_config = {
    .width = PROJECT_CARD_WIDTH,
    .height = PROJECT_CARD_HEIGHT,
    .gap = 20,
    .columns = 0,
    .padding = 0,
    .containerName = "NaoxProjectsGrid"
};

// Create and configure personal projects grid 
Rocks_GridConfig personal_projects_grid_config = {
    .width = PROJECT_CARD_WIDTH,
    .height = PROJECT_CARD_HEIGHT,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "PersonalProjectsGrid"
};

// Create and configure blog grid
Rocks_GridConfig blog_grid_config = {
    .width = 320,
    .height = 225,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "BlogGrid"
};

// Create and configure connections grid
Rocks_GridConfig connections_grid_config = {
    .width = 225,
    .height = 110,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "ConnectionsGrid"
};

static void render_project_card(void* data) {
    Project* project = (Project*)data;
    Rocks_Theme theme = Rocks_GetTheme(GRocks);
    Clay_String title = { .chars = project->title, .length = strlen(project->title) };
    Clay_String description = { .chars = project->description, .length = strlen(project->description) };
    Clay_Dimensions image_dims = Rocks_GetImageDimensions(GRocks, project->image);
    
    CLAY({
        .layout = {
            .sizing = { CLAY_SIZING_FIXED(PROJECT_CARD_WIDTH), CLAY_SIZING_FIXED(PROJECT_CARD_HEIGHT) },
            .padding = CLAY_PADDING_ALL(20),
            .childGap = 15,
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .backgroundColor = theme.secondary,
        .cornerRadius = CLAY_CORNER_RADIUS(8),
        .border = {
            .color = theme.border,
            .width = { 2, 2, 2, 2 }
        }
    }) {
        if (project->image) {
            CLAY({
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(180) }
                },
                .image = {
                    .imageData = project->image,
                    .sourceDimensions = image_dims
                }
            }) {}
        }

        CLAY_TEXT(title, CLAY_TEXT_CONFIG({
            .textColor = theme.text,
            .fontSize = 24,
            .fontId = g_font_ids[FONT_TITLE]
        }));

        CLAY_TEXT(description, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 16,
            .fontId = g_font_ids[FONT_BODY]
        }));

        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(40) },
                .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
            },
            .backgroundColor = Clay_Hovered() ? theme.primary_hover : theme.primary,
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
static void render_blog_post_card(void* data) {
    BlogPost* post = (BlogPost*)data;
    Rocks_Theme theme = Rocks_GetTheme(GRocks);
    
    Clay_String date_str = { .chars = post->date, .length = strlen(post->date) };
    Clay_String title_str = { .chars = post->title, .length = strlen(post->title) };
    Clay_String desc_str = { .chars = post->description, .length = strlen(post->description) };
    
    CLAY({
        .layout = {
            .padding = CLAY_PADDING_ALL(20),
            .childGap = 10,
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .backgroundColor = theme.secondary,
        .cornerRadius = CLAY_CORNER_RADIUS(8),
        .border = {
            .color = theme.border,
            .width = { 1, 1, 1, 1 }
        }
    }) {
        CLAY_TEXT(date_str, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 14,
            .fontId = g_font_ids[FONT_BODY]
        }));

        CLAY_TEXT(title_str, CLAY_TEXT_CONFIG({
            .textColor = theme.text,
            .fontSize = 20,
            .fontId = g_font_ids[FONT_TITLE]
        }));

        CLAY_TEXT(desc_str, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 16,
            .fontId = g_font_ids[FONT_BODY]
        }));
    }
}

static void render_connection_card(void* data) {
    Connection* connection = (Connection*)data;
    Rocks_Theme theme = Rocks_GetTheme(GRocks);
    Clay_String platform = { .chars = connection->platform, .length = strlen(connection->platform) };
    Clay_String contact = { .chars = connection->contact, .length = strlen(connection->contact) };
    
    CLAY({
        .layout = {
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
            .childGap = 60,
            .padding = CLAY_PADDING_ALL(40),
            .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
        },
        .scroll = { .vertical = true, .horizontal = false },
        .backgroundColor = theme.background
    }) {
        // Logo section
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(200) },
                .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER }
            }
        }) {
            CLAY({
                .layout = {
                    .sizing = { CLAY_SIZING_FIXED(128), CLAY_SIZING_FIXED(128) }
                },
                .image = {
                    .imageData = g_logo_image,
                    .sourceDimensions = logo_dims
                }
            }) {}
        }
        // NaoX Projects Section
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .childGap = 20,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            }
        }) {
            CLAY_TEXT(CLAY_STRING("NaoX Projects"), CLAY_TEXT_CONFIG({
                .textColor = theme.primary,
                .fontSize = 32,
                .fontId = g_font_ids[FONT_TITLE]
            }));

            CLAY({
                .id = CLAY_ID("NaoxProjectsGrid"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
                }
            }) {
                Rocks_BeginGrid(g_naox_projects_grid);
                for (int i = 0; i < sizeof(g_naox_projects)/sizeof(g_naox_projects[0]); i++) {
                    Rocks_RenderGridItem(g_naox_projects_grid, i, render_project_card);
                }
                Rocks_EndGrid(g_naox_projects_grid);
            }
        }
        // Personal Projects Section
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .childGap = 20,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            }
        }) {
            CLAY_TEXT(CLAY_STRING("Other Projects"), CLAY_TEXT_CONFIG({
                .textColor = theme.text,
                .fontSize = 32,
                .fontId = g_font_ids[FONT_TITLE]
            }));

            CLAY({
                .id = CLAY_ID("PersonalProjectsGrid"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
                }
            }) {
                Rocks_BeginGrid(g_personal_projects_grid);
                for (int i = 0; i < sizeof(g_personal_projects)/sizeof(g_personal_projects[0]); i++) {
                    Rocks_RenderGridItem(g_personal_projects_grid, i, render_project_card);
                }
                Rocks_EndGrid(g_personal_projects_grid);
            }
        }

        // Blog Section
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .childGap = 20,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            }
        }) {
            CLAY_TEXT(CLAY_STRING("Blog"), CLAY_TEXT_CONFIG({
                .textColor = theme.text,
                .fontSize = 32,
                .fontId = g_font_ids[FONT_TITLE]
            }));

            CLAY({
                .id = CLAY_ID("BlogGrid"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
                }
            }) {
                Rocks_BeginGrid(g_blog_grid);
                for (int i = 0; i < sizeof(g_blog_posts)/sizeof(g_blog_posts[0]); i++) {
                    Rocks_RenderGridItem(g_blog_grid, i, render_blog_post_card);
                }
                Rocks_EndGrid(g_blog_grid);
            }
        }

        // Connections section
        CLAY({
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
.childGap = 20,
                .layoutDirection = CLAY_TOP_TO_BOTTOM
            }
        }) {
            CLAY_TEXT(CLAY_STRING("Connect with me"), CLAY_TEXT_CONFIG({
                .textColor = theme.text,
                .fontSize = 32,
                .fontId = g_font_ids[FONT_TITLE]
            }));

            CLAY({
                .id = CLAY_ID("ConnectionsGrid"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
                }
            }) {
                Rocks_BeginGrid(g_connections_grid);
                for (int i = 0; i < sizeof(g_connections)/sizeof(g_connections[0]); i++) {
                    Rocks_RenderGridItem(g_connections_grid, i, render_connection_card);
                }
                Rocks_EndGrid(g_connections_grid);
            }
        }
    }
    
    return Clay_EndLayout();
}

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

    // Load fonts
    g_font_ids[FONT_TITLE] = Rocks_LoadFont("assets/Roboto-Bold.ttf", 24, FONT_TITLE);
    g_font_ids[FONT_BODY] = Rocks_LoadFont("assets/Roboto-Regular.ttf", 16, FONT_BODY);

    // Load logo image
    g_logo_image = Rocks_LoadImage(rocks, "assets/logo.png");

    g_naox_projects_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_naox_projects_grid, naox_projects_grid_config);

    g_personal_projects_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_personal_projects_grid, personal_projects_grid_config);

    g_blog_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_blog_grid, blog_grid_config);


    g_connections_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_connections_grid, connections_grid_config);


    // Add items to respective grids
    for (int i = 0; i < sizeof(g_naox_projects)/sizeof(g_naox_projects[0]); i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_naox_projects[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/projects/%s.png", filename);
        g_project_images[i] = Rocks_LoadImage(rocks, path);
        g_naox_projects[i].image = g_project_images[i];
        Rocks_AddGridItem(g_naox_projects_grid, &g_naox_projects[i]);
    }

    for (int i = 0; i < sizeof(g_personal_projects)/sizeof(g_personal_projects[0]); i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_personal_projects[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/projects/%s.png", filename);
        g_project_images[i + sizeof(g_naox_projects)/sizeof(g_naox_projects[0])] = Rocks_LoadImage(rocks, path);
        g_personal_projects[i].image = g_project_images[i + sizeof(g_naox_projects)/sizeof(g_naox_projects[0])];
        Rocks_AddGridItem(g_personal_projects_grid, &g_personal_projects[i]);
    }

    // Add blog posts to grid
    for (int i = 0; i < sizeof(g_blog_posts)/sizeof(g_blog_posts[0]); i++) {
        Rocks_AddGridItem(g_blog_grid, &g_blog_posts[i]);
    }

    // Add connections to grid
    for (int i = 0; i < sizeof(g_connections)/sizeof(g_connections[0]); i++) {
        Rocks_AddGridItem(g_connections_grid, &g_connections[i]);
    }

    Rocks_Run(rocks, app_update);
    
    // Cleanup

    Rocks_DestroyGrid(g_naox_projects_grid);
    Rocks_DestroyGrid(g_personal_projects_grid);
    Rocks_DestroyGrid(g_blog_grid);
    Rocks_DestroyGrid(g_connections_grid);
    Rocks_UnloadFont(g_font_ids[FONT_TITLE]);
    Rocks_UnloadFont(g_font_ids[FONT_BODY]);
    Rocks_UnloadImage(rocks, g_logo_image);
    // Cleanup
    for (int i = 0; i < sizeof(g_naox_projects)/sizeof(g_naox_projects[0]); i++) {
        Rocks_UnloadImage(rocks, g_project_images[i]);
    }
    for (int i = 0; i < sizeof(g_personal_projects)/sizeof(g_personal_projects[0]); i++) {
        Rocks_UnloadImage(rocks, g_project_images[i + sizeof(g_naox_projects)/sizeof(g_naox_projects[0])]);
    }
    Rocks_Cleanup(rocks);
    
    return 0;
}