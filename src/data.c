#include "data.h"
#include <ctype.h>
#include <string.h>

Project g_naox_projects[] = {
    {"Rocks", "Framework for Clay, providing an easy way to change renderers and use premade components", NULL, "https://github.com/naoxio/rocks"},
    {"Quest", "A personal life management app focused on habit tracking, task organization and life visualization.", NULL, "http://quest.naox.io/"},
    {"Inner Breeze", "Guided breathing meditation app based on the Wim Hof breathing method.", NULL, "https://inbreeze.xyz"},
    {"NaoX", "Explore more innovative projects and solutions at NaoX, where technology meets creativity.", NULL, "https://naox.io"}
};

Project g_personal_projects[] = {
    {"Kasaival", "A minimal and fast HTTP server written in C.", NULL, "https://github.com/waozixyz/kasaival"},
    {"Algotree", "Single header C library to draw 3d or 2d algorithmically grown trees in Raylib.", NULL, "https://github.com/waozixyz/algotree"}
};

BlogPost g_blog_posts[] = {
    {"Clingy Tree", "Explore the metaphor of a clingy tree and learn to let go of attachments...", "2020-09-29", "#", NULL}
};

Connection g_connections[] = {
    {"GitHub", "@waozixyz"},
    {"X/Twitter", "@waozixyz"},
    {"Nostr", "@waozi@ditto.pub"},
    {"Telegram", "@waozixyz"},
    {"Email", "hello@waozi.xyz"}
};

const int g_naox_projects_count = sizeof(g_naox_projects) / sizeof(g_naox_projects[0]);
const int g_personal_projects_count = sizeof(g_personal_projects) / sizeof(g_personal_projects[0]);
const int g_blog_posts_count = sizeof(g_blog_posts) / sizeof(g_blog_posts[0]);
const int g_connections_count = sizeof(g_connections) / sizeof(g_connections[0]);

Rocks_GridConfig naox_projects_grid_config = {
    .width = PROJECT_CARD_WIDTH,
    .height = PROJECT_CARD_HEIGHT,
    .gap = 20,
    .columns = 0,
    .padding = 0,
    .containerName = "NaoxProjectsGrid"
};

Rocks_GridConfig personal_projects_grid_config = {
    .width = PROJECT_CARD_WIDTH,
    .height = PROJECT_CARD_HEIGHT,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "PersonalProjectsGrid"
};

Rocks_GridConfig blog_grid_config = {
    .width = 320,
    .height = 225,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "BlogGrid"
};

Rocks_GridConfig connections_grid_config = {
    .width = 225,
    .height = 110,
    .gap = 20,
    .columns = 0,
    .padding = 20,
    .containerName = "ConnectionsGrid"
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