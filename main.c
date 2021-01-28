#include <stdbool.h>
#include <stdio.h>

#include "bmp.h"
#include "rotate.h"
#include "io.h"

typedef enum read_status reader(FILE*, struct image*);

typedef enum write_status writer(FILE*, const struct image*);

enum format {
    BMP = 0
    //More possible formats
};

static reader* const readers[] = {
        [BMP] = from_bmp
};

static writer* const writers[] = {
        [BMP] = to_bmp
};

int main(int argc, char** argv) {
    struct image img = {0};

    if (!load_image_from_file("C:\\Users\\Антон\\Desktop\\test_rect.bmp", &img, readers[BMP])) {
        return 1;
    }

    const struct image rotated = rotate_90(img);

    if (!write_image_to_file("C:\\Users\\Антон\\Desktop\\res_rect.bmp", &rotated, writers[BMP])) {
        image_destroy(&img);
        image_destroy(&rotated);
        return 1;
    }

    image_destroy(&img);
    image_destroy(&rotated);

    return 0;
}
