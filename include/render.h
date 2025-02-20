#ifndef RENDER_H
#define RENDER_H

#include "types.h"
#include "rocks_custom.h"

void render_project_card(void* data);
void render_blog_post_card(void* data);
void render_connection_card(void* data);
Clay_RenderCommandArray app_update(Rocks* rocks, float dt);

#endif // RENDER_H
