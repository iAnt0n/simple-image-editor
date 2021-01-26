#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include "image.h"
#include "bmp.h"

enum open_status {
    OPEN_OK = 0,
    OPEN_ERROR
};

enum open_status open_file(FILE** file, const char* path, const char* mode);

enum close_status {
    CLOSE_OK = 0,
    CLOSE_ERROR
};

enum close_status close_file(FILE** file);

bool load_image_from_file(const char* filename, struct image* image, enum read_status (reader) (FILE*, struct image*));

#endif //_IO_H_
