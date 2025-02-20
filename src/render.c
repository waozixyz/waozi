#include "render.h"
#include "data.h"
#include "app.h"
#include "components/markdown.h"
#include <string.h>

// Project card click callback
static void project_card_click_callback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        Project* project = (Project*)userData;
        // Handle project click - e.g. open URL, navigate, etc.
    }
}

void render_project_card(void* data) {
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
        .border = { .color = theme.border, .width = {2, 2, 2, 2} },
        .userData = Rocks_AllocateCustomData((RocksCustomData) { 
            .cursorPointer = true
        })
    }) {
        Clay_OnHover(project_card_click_callback, (intptr_t)project);
        
        if (project->image) {
            CLAY({
                .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(180) } },
                .image = { .imageData = project->image, .sourceDimensions = image_dims }
            }) {}
        }
        
        CLAY_TEXT(title, CLAY_TEXT_CONFIG({ 
            .textColor = theme.text, 
            .fontSize = 24, 
            .fontId = get_font_id(FONT_TITLE) 
        }));
        
        CLAY_TEXT(description, CLAY_TEXT_CONFIG({ 
            .textColor = theme.text_secondary, 
            .fontSize = 16, 
            .fontId = get_font_id(FONT_BODY) 
        }));
    }
}

// Blog post click callback 
static void blog_post_click_callback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        BlogPost* post = (BlogPost*)userData;
        // Set selected blog based on the post's position in g_blog_posts
        for (int i = 0; i < g_blog_posts_count; i++) {
            if (&g_blog_posts[i] == post) {
                set_selected_blog_index(i);
                break;
            }
        }
    }
}

void render_blog_post_card(void* data) {
    BlogPost* post = (BlogPost*)data;
    Rocks_Theme theme = Rocks_GetTheme(GRocks);
    Clay_String date_str = { .chars = post->date, .length = strlen(post->date) };
    Clay_String title_str = { .chars = post->title, .length = strlen(post->title) };
    Clay_String desc_str = { .chars = post->description, .length = strlen(post->description) };
    Clay_Dimensions image_dims = Rocks_GetImageDimensions(GRocks, post->image);

    CLAY({
        .layout = {
            .padding = CLAY_PADDING_ALL(20),
            .childGap = 12,
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
            .sizing = { CLAY_SIZING_FIXED(320), CLAY_SIZING_FIXED(225) }
        },
        .backgroundColor = theme.secondary,
        .cornerRadius = CLAY_CORNER_RADIUS(12),
        .border = { .color = theme.border, .width = {1, 1, 1, 1} },
        .userData = Rocks_AllocateCustomData((RocksCustomData) { 
            .cursorPointer = true
        })
    }) {
        Clay_OnHover(blog_post_click_callback, (intptr_t)post);
        
        if (post->image) {
            CLAY({
                .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(100) } },
                .image = { .imageData = post->image, .sourceDimensions = image_dims }
            }) {}
        }

        CLAY({
            .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIT(0) } }
        }) {
            CLAY_TEXT(date_str, CLAY_TEXT_CONFIG({
                .textColor = {theme.text_secondary.r, theme.text_secondary.g, theme.text_secondary.b, 180},
                .fontSize = 14,
                .fontId = get_font_id(FONT_BODY)
            }));
        }

        CLAY_TEXT(title_str, CLAY_TEXT_CONFIG({
            .textColor = theme.text,
            .fontSize = 20,
            .fontId = get_font_id(FONT_TITLE)
        }));

        CLAY_TEXT(desc_str, CLAY_TEXT_CONFIG({
            .textColor = theme.text_secondary,
            .fontSize = 16,
            .fontId = get_font_id(FONT_BODY)
        }));
    }
}

static void connection_card_click_callback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        Connection* connection = (Connection*)userData;
        // Handle connection click
    }
}

void render_connection_card(void* data) {
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
        .border = { .color = theme.border, .width = {1, 1, 1, 1} },
        .userData = Rocks_AllocateCustomData((RocksCustomData) { 
            .cursorPointer = true 
        })
    }) {
        Clay_OnHover(connection_card_click_callback, (intptr_t)connection);

        CLAY_TEXT(platform, CLAY_TEXT_CONFIG({ 
            .textColor = theme.text, 
            .fontSize = 18, 
            .fontId = get_font_id(FONT_TITLE) 
        }));

        CLAY_TEXT(contact, CLAY_TEXT_CONFIG({ 
            .textColor = theme.text_secondary, 
            .fontSize = 16, 
            .fontId = get_font_id(FONT_BODY) 
        }));
    }
}

static void back_button_click_callback(Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData) {
    if (pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME) {
        set_selected_blog_index(-1);
    }
}

static void render_markdown_page(Rocks* rocks, int blog_index) {
    Rocks_Theme theme = Rocks_GetTheme(rocks);
    Rocks_Markdown* markdown_viewer = get_markdown_viewer();

    const char* markdown_content = NULL;
    if (blog_index == 0) { // Clingy Tree
        markdown_content = 
            "# Clingy Tree\n\n"
            "Once upon a time there was a young man, who traveled the world. He was in his early 20s when he met the clingy tree...\n\n"
            "## Features\n"
            "- Letting go of attachments\n"
            "- Finding balance\n";
    } else {
        markdown_content = "# Placeholder\n\nThis is a placeholder blog post.";
    }
    Rocks_LoadMarkdownFromString(markdown_viewer, markdown_content);

    CLAY({
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(40),
            .childGap = 20,
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .backgroundColor = theme.background
    }) {
        // Back button
        CLAY({
            .layout = { .sizing = { CLAY_SIZING_FIT(0), CLAY_SIZING_FIXED(40) } },
            .backgroundColor = Clay_Hovered() ? theme.primary_hover : theme.primary,
            .cornerRadius = CLAY_CORNER_RADIUS(4),
            .userData = Rocks_AllocateCustomData((RocksCustomData) { 
                .cursorPointer = true 
            })
        }) {
            Clay_OnHover(back_button_click_callback, 0);
            
            CLAY_TEXT(CLAY_STRING("Back"), CLAY_TEXT_CONFIG({
                .textColor = theme.secondary,
                .fontSize = 16,
                .fontId = get_font_id(FONT_BODY)
            }));
        }

        CLAY({
            .layout = { .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) } },
            .scroll = { .vertical = true }
        }) {
            Rocks_RenderMarkdown(markdown_viewer);
        }
    }
}

Clay_RenderCommandArray app_update(Rocks* rocks, float dt) {
    Rocks_Theme theme = Rocks_GetTheme(rocks);
    Clay_Dimensions logo_dims = Rocks_GetImageDimensions(rocks, get_logo_image());
    int selected_blog = get_selected_blog_index();

    Clay_BeginLayout();

    if (selected_blog == -1) { // Main page
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
            CLAY({
                .layout = { 
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_FIXED(200) }, 
                    .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER } 
                }
            }) {
                CLAY({
                    .layout = { .sizing = { CLAY_SIZING_FIXED(128), CLAY_SIZING_FIXED(128) } },
                    .image = { .imageData = get_logo_image(), .sourceDimensions = logo_dims }
                }) {}
            }

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
                    .fontId = get_font_id(FONT_TITLE) 
                }));

                CLAY({
                    .id = CLAY_ID("NaoxProjectsGrid"),
                    .layout = { 
                        .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, 
                        .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP } 
                    }
                }) {
                    Rocks_BeginGrid(get_naox_projects_grid());
                    for (int i = 0; i < g_naox_projects_count; i++) {
                        Rocks_RenderGridItem(get_naox_projects_grid(), i, render_project_card);
                    }
                    Rocks_EndGrid(get_naox_projects_grid());
                }
            }

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
                    .fontId = get_font_id(FONT_TITLE) 
                }));

                CLAY({
                    .id = CLAY_ID("PersonalProjectsGrid"),
                    .layout = { 
                        .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, 
                        .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP } 
                    }
                }) {
                    Rocks_BeginGrid(get_personal_projects_grid());
                    for (int i = 0; i < g_personal_projects_count; i++) {
                        Rocks_RenderGridItem(get_personal_projects_grid(), i, render_project_card);
                    }
                    Rocks_EndGrid(get_personal_projects_grid());
                }
            }

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
                    .fontId = get_font_id(FONT_TITLE) 
                }));

                CLAY({
                    .id = CLAY_ID("BlogGrid"),
                    .layout = { 
                        .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, 
                        .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP }
                        }
                }) {
                    Rocks_BeginGrid(get_blog_grid());
                    for (int i = 0; i < g_blog_posts_count; i++) {
                        Rocks_RenderGridItem(get_blog_grid(), i, render_blog_post_card);
                    }
                    Rocks_EndGrid(get_blog_grid());
                }
            }

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
                    .fontId = get_font_id(FONT_TITLE) 
                }));

                CLAY({
                    .id = CLAY_ID("ConnectionsGrid"),
                    .layout = { 
                        .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) }, 
                        .childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_TOP } 
                    }
                }) {
                    Rocks_BeginGrid(get_connections_grid());
                    for (int i = 0; i < g_connections_count; i++) {
                        Rocks_RenderGridItem(get_connections_grid(), i, render_connection_card);
                    }
                    Rocks_EndGrid(get_connections_grid());
                }
            }
        }
    } else { // Blog post page
        render_markdown_page(rocks, selected_blog);
    }

    return Clay_EndLayout();
}