#include "app.h"
#include "data.h"
#include <stdio.h>
#include <string.h>

static uint16_t g_font_ids[FONT_COUNT];
static void* g_logo_image;
static void* g_project_images[10];
static void* g_blog_images[3]; // Assuming 3 blog posts for now
static Rocks_Grid* g_naox_projects_grid = NULL;
static Rocks_Grid* g_personal_projects_grid = NULL;
static Rocks_Grid* g_blog_grid = NULL;
static Rocks_Grid* g_connections_grid = NULL;
static Rocks_Markdown* g_markdown_viewer = NULL;
static int g_selected_blog_index = -1; // -1 means no blog selected

uint16_t get_font_id(int index) {
    return g_font_ids[index];
}

void* get_logo_image(void) {
    return g_logo_image;
}

Rocks_Grid* get_naox_projects_grid(void) {
    return g_naox_projects_grid;
}

Rocks_Grid* get_personal_projects_grid(void) {
    return g_personal_projects_grid;
}

Rocks_Grid* get_blog_grid(void) {
    return g_blog_grid;
}

Rocks_Grid* get_connections_grid(void) {
    return g_connections_grid;
}

Rocks_Markdown* get_markdown_viewer(void) {
    return g_markdown_viewer;
}

int get_selected_blog_index(void) {
    return g_selected_blog_index;
}

void set_selected_blog_index(int index) {
    g_selected_blog_index = index;
}

void app_init(Rocks* rocks) {
    g_font_ids[FONT_TITLE] = Rocks_LoadFont("assets/Roboto-Bold.ttf", 24, FONT_TITLE);
    g_font_ids[FONT_BODY] = Rocks_LoadFont("assets/Roboto-Regular.ttf", 16, FONT_BODY);
    g_logo_image = Rocks_LoadImage(rocks, "assets/logo.png");

    g_naox_projects_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_naox_projects_grid, naox_projects_grid_config);
    g_personal_projects_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_personal_projects_grid, personal_projects_grid_config);
    g_blog_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_blog_grid, blog_grid_config);
    g_connections_grid = Rocks_CreateGrid();
    Rocks_InitGrid(g_connections_grid, connections_grid_config);

    // Initialize Markdown viewer
    g_markdown_viewer = Rocks_CreateMarkdownViewer(g_font_ids[FONT_TITLE], g_font_ids[FONT_BODY]);

    // Load project images
    for (int i = 0; i < g_naox_projects_count; i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_naox_projects[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/projects/%s.png", filename);
        g_project_images[i] = Rocks_LoadImage(rocks, path);
        g_naox_projects[i].image = g_project_images[i];
        Rocks_AddGridItem(g_naox_projects_grid, &g_naox_projects[i]);
    }

    for (int i = 0; i < g_personal_projects_count; i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_personal_projects[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/projects/%s.png", filename);
        g_project_images[i + g_naox_projects_count] = Rocks_LoadImage(rocks, path);
        g_personal_projects[i].image = g_project_images[i + g_naox_projects_count];
        Rocks_AddGridItem(g_personal_projects_grid, &g_personal_projects[i]);
    }

    // Load blog images
    for (int i = 0; i < g_blog_posts_count; i++) {
        char filename[64];
        char path[128];
        get_image_filename(g_blog_posts[i].title, filename, sizeof(filename));
        snprintf(path, sizeof(path), "assets/blog/%s.jpg", filename); // Adjust path as needed
        g_blog_images[i] = Rocks_LoadImage(rocks, path);
        g_blog_posts[i].image = g_blog_images[i];
        Rocks_AddGridItem(g_blog_grid, &g_blog_posts[i]);
    }

    for (int i = 0; i < g_connections_count; i++) {
        Rocks_AddGridItem(g_connections_grid, &g_connections[i]);
    }
}

void app_cleanup(Rocks* rocks) {
    Rocks_DestroyGrid(g_naox_projects_grid);
    Rocks_DestroyGrid(g_personal_projects_grid);
    Rocks_DestroyGrid(g_blog_grid);
    Rocks_DestroyGrid(g_connections_grid);
    Rocks_DestroyMarkdownViewer(g_markdown_viewer);
    Rocks_UnloadFont(g_font_ids[FONT_TITLE]);
    Rocks_UnloadFont(g_font_ids[FONT_BODY]);
    Rocks_UnloadImage(rocks, g_logo_image);
    for (int i = 0; i < g_naox_projects_count; i++) {
        Rocks_UnloadImage(rocks, g_project_images[i]);
    }
    for (int i = 0; i < g_personal_projects_count; i++) {
        Rocks_UnloadImage(rocks, g_project_images[i + g_naox_projects_count]);
    }
    for (int i = 0; i < g_blog_posts_count; i++) {
        Rocks_UnloadImage(rocks, g_blog_images[i]);
    }
    Rocks_Cleanup(rocks);
}