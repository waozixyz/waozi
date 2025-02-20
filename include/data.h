#ifndef DATA_H
#define DATA_H

#include "types.h"

extern Project g_naox_projects[];
extern Project g_personal_projects[];
extern BlogPost g_blog_posts[];
extern Connection g_connections[];

extern const int g_naox_projects_count;
extern const int g_personal_projects_count;
extern const int g_blog_posts_count;
extern const int g_connections_count;

extern Rocks_GridConfig naox_projects_grid_config;
extern Rocks_GridConfig personal_projects_grid_config;
extern Rocks_GridConfig blog_grid_config;
extern Rocks_GridConfig connections_grid_config;

char* get_image_filename(const char* project_name, char* buffer, size_t buffer_size);

#endif // DATA_H