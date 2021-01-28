#include <malloc.h>
#include "rotate.h"

struct image rotate_90(struct image src) {
    const uint32_t result_width = src.height;
    const uint32_t result_height = src.width;

    struct image result_image = image_create(result_width, result_height);

    for (size_t i = 0; i < src.height; i++){
        for (size_t j = 0; j < src.width; j++){
            result_image.data[result_image.width * i + j] = src.data[src.width * j + (src.width - 1 - i)];
        }
    }
    
    return result_image;
}
