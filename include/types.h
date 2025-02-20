#ifndef TYPES_H
#define TYPES_H

#include "rocks.h"
#include "components/grid.h"

enum {
    FONT_TITLE = 0,
    FONT_BODY = 1,
    FONT_COUNT
};

typedef struct {
    const char* title;
    const char* description;
    void* image;
    const char* link;
} Project;

typedef struct {
    const char* title;
    const char* description;
    const char* date;
    const char* link;
    void* image; // New field for blog post image
} BlogPost;

typedef struct {
    const char* platform;
    const char* contact;
} Connection;

#define PROJECT_CARD_WIDTH 256
#define PROJECT_CARD_HEIGHT 300

#endif // TYPES_H