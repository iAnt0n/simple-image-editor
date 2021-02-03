#include "bmp.h"

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

static bool read_header(FILE* f, struct bmp_header* header) {
    return fread(header, sizeof(struct bmp_header), 1, f);
}

static size_t calc_padding(const uint32_t width) {
    return (4 - (width * sizeof(struct pixel) % 4)) % 4;
}

static enum read_status check_bmp_header(const struct bmp_header header) {
    if (header.biBitCount != 24
        || header.biCompression != 0
        || header.biSize != INFO_HEADER_SIZE
        || header.biPlanes != PLANES_NUMBER) {
        return READ_INVALID_HEADER;
    }

    if (header.bfType != BMP_SIGNATURE) {
        return READ_INVALID_SIGNATURE;
    }

    return READ_OK;

}

enum read_status from_bmp(FILE* in, struct image* img) {
    struct bmp_header header = {0};
    if (read_header(in, &header) < 1) {
        return READ_INVALID_HEADER;
    }

    const enum read_status header_check = check_bmp_header(header);
    if (header_check != READ_OK) {
        return header_check;
    }

    *img = image_create(header.biWidth, header.biHeight);

    const size_t padding = calc_padding(img->width);
    const size_t pixel_size = sizeof(struct pixel);
    const size_t gap = header.bOffBits - sizeof(header);

    if (fseek(in, gap, SEEK_CUR) != 0) {
        image_destroy(img);
        return READ_INVALID_BITS;
    }

    for (size_t row = 0; row < img->height; row++) {
        if (fread(&img->data[row * img->width], pixel_size, img->width, in) < img->width) {
            image_destroy(img);
            return READ_INVALID_BITS;
        };
        if (fseek(in, padding, SEEK_CUR) != 0) {
            image_destroy(img);
            return READ_INVALID_BITS;
        }
    }
    return READ_OK;
}

static struct bmp_header generate_bmp_header(const uint32_t width, const uint32_t height) {
    const size_t header_size = sizeof(struct bmp_header);
    const size_t image_size = height * (width + calc_padding(width)) * sizeof(struct pixel);

    struct bmp_header header = {
            .bfType = BMP_SIGNATURE,
            .biHeight = height,
            .biWidth = width,
            .bOffBits = header_size,
            .biSize = 40,
            .biPlanes = 1,
            .bfileSize = header_size + image_size,
            .biCompression = 0,
            .bfReserved = 0,
            .biBitCount = BITS_PER_COLOR,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0,
            .biSizeImage = image_size
    };

    return header;
}

enum write_status to_bmp(FILE* out, const struct image* img) {
    const struct bmp_header header = generate_bmp_header(img->width, img->height);
    const size_t padding = calc_padding(img->width);
    const uint8_t zero = 0;

    if (fwrite(&header, sizeof(struct bmp_header), 1, out) < 1) return WRITE_ERROR;
    for (size_t i = 0; i < header.biHeight; i++) {
        if (fwrite(&img->data[i * header.biWidth], sizeof(struct pixel), header.biWidth, out)
            < header.biWidth) return WRITE_ERROR;
        if (fwrite(&zero, padding, 1, out) < 1) return WRITE_ERROR;
    }
    return WRITE_OK;

}

