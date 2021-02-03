#ifndef _BMP_H_
#define _BMP_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../image.h"

#define FOR_BMP_HEADER(FOR_FIELD) \
        FOR_FIELD( uint16_t,bfType)\
        FOR_FIELD( uint32_t,bfileSize)\
        FOR_FIELD( uint32_t,bfReserved)\
        FOR_FIELD( uint32_t,bOffBits)\
        FOR_FIELD( uint32_t,biSize)\
        FOR_FIELD( uint32_t,biWidth)\
        FOR_FIELD( uint32_t,biHeight)\
        FOR_FIELD( uint16_t,biPlanes)\
        FOR_FIELD( uint16_t,biBitCount)\
        FOR_FIELD( uint32_t,biCompression)\
        FOR_FIELD( uint32_t,biSizeImage)\
        FOR_FIELD( uint32_t,biXPelsPerMeter)\
        FOR_FIELD( uint32_t,biYPelsPerMeter)\
        FOR_FIELD( uint32_t,biClrUsed)\
        FOR_FIELD( uint32_t,biClrImportant)

#define DECLARE_FIELD(t, n) t n ;

struct __attribute__((packed)) bmp_header {
    FOR_BMP_HEADER(DECLARE_FIELD)
};

#define BMP_SIGNATURE 0x4D42
#define BITS_PER_COLOR 24
#define INFO_HEADER_SIZE 40
#define PLANES_NUMBER 1

enum read_status from_bmp(FILE* in, struct image* img);

enum write_status to_bmp(FILE* out, struct image const* img);

#endif
