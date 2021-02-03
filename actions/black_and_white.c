#include <limits.h>
#include "black_and_white.h"


struct image to_bw(struct image src) {
    struct image result_image = image_create(src.width, src.height);

    for (size_t i = 0; i < src.height; i++){
        for (size_t j = 0; j < src.width; j++){
            const size_t index = result_image.width * i + j;
            const uint32_t color = ( src.data[index].b + src.data[index].g + src.data[index].r ) / 3;
            result_image.data[index].b = color;
            result_image.data[index].g = color;
            result_image.data[index].r = color;
        }
    }

    return result_image;
}