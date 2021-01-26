#include <malloc.h>
#include "rotate_90.h"

struct image rotate_90(struct image img) {
    const uint32_t result_width = img.height;
    const uint32_t result_height = img.width;

    struct image result_image = image_create(result_width, result_height);

    for (size_t i = 0; i < img.height; i++){
        for (size_t j = 0; j < img.width; j++){
            result_image.data[img.width * i + j] = img.data[img.height * j + (img.height - 1 - i)];
        }
    }
    
    return result_image;
}
