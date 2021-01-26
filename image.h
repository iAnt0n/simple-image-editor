#ifndef _IMAGE_H_
#define _IMAGE_H_

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

#endif //_IMAGE_H_
