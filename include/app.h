#ifndef APP_H
#define APP_H

#include "types.h"

#include "components/markdown.h" 

uint16_t get_font_id(int index);
void* get_logo_image(void);
Rocks_Grid* get_naox_projects_grid(void);
Rocks_Grid* get_personal_projects_grid(void);
Rocks_Grid* get_blog_grid(void);
Rocks_Grid* get_connections_grid(void);
Rocks_Markdown* get_markdown_viewer(void);
int get_selected_blog_index(void);
void set_selected_blog_index(int index);

void app_init(Rocks* rocks);
void app_cleanup(Rocks* rocks);

#endif // APP_H