#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include "image.h"

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
};

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum open_status open_file(FILE** file, const char* path, const char* mode);

enum close_status close_file(FILE** file);

bool load_image_from_file(const char* filename, struct image* image, enum read_status (reader) (FILE*, struct image*));

bool
write_image_to_file(const char* filename, const struct image* image, enum write_status (writer)(FILE*, const struct image*));

#endif //_IO_H_
