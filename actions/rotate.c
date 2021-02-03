#include <malloc.h>
#include "rotate.h"

struct image rotate_90(struct image src) {
    const uint32_t result_width = src.height;
    const uint32_t result_height = src.width;

    struct image result_image = image_create(result_width, result_height);

    for (uint32_t i = 0; i < src.height; i++){
        for (uint32_t j = 0; j < src.width; j++){
            result_image.data[j * result_width + result_width-i-1] = src.data[i*src.width + j];
        }
    }
    
    return result_image;
}
