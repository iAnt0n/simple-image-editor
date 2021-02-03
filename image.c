#include <malloc.h>
#include "image.h"

struct image image_create(uint32_t width, uint32_t height) {
    struct pixel* pixel = malloc(width * height * sizeof(struct pixel));
    return (struct image) {.width=width, .height=height, .data=pixel};
}

void image_destroy(const struct image* image) {
    free(image->data);
}

