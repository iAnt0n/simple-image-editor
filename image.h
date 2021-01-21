#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_H

#include <stdint.h>

struct pixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

struct image {
    uint32_t width, height;
    struct pixel* data;
};

struct image image_create(uint32_t width, uint32_t height);

void image_destroy(const struct image* image);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_H
