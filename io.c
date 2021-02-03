#include <stdbool.h>

#include "io.h"
#include "util.h"
#include "messages.h"

enum open_status open_file(FILE** file, const char* path, const char* mode) {
    *file = fopen(path, mode);
    if (!(*file)) {
        return OPEN_ERROR;
    }
    return OPEN_OK;
}

enum close_status close_file(FILE** file) {
    if (fclose(*file) != 0) {
        return CLOSE_ERROR;
    }
    return CLOSE_OK;
}

bool
load_image_from_file(const char* filename, struct image* image, enum read_status (reader)(FILE*, struct image*)) {
    FILE* file = NULL;

    const enum open_status input_open_status = open_file(&file, filename, "rb");

    if (input_open_status != OPEN_OK) {
        err(open_error_messages[input_open_status]);
        return false;
    }

    const enum read_status read_status = reader(file, image);

    if (read_status != READ_OK) {
        err(read_error_messages[read_status]);
        return false;
    }

    const enum close_status input_close_status = close_file(&file);

    if (input_close_status != CLOSE_OK) {
        err(close_error_messages[input_close_status]);
        return false;
    }

    return true;
}

bool
write_image_to_file(const char* filename, const struct image* image, enum write_status (writer)(FILE*, const struct image*)) {
    FILE* file = NULL;

    const enum open_status output_open_status = open_file(&file, filename, "wb");

    if (output_open_status != OPEN_OK) {
        err(open_error_messages[output_open_status]);
        return false;
    }

    const enum write_status write_status = writer(file, image);

    if (write_status != WRITE_OK) {
        err(write_error_messages[write_status]);
        return false;
    }

    const enum close_status output_close_status = close_file(&file);

    if (output_close_status != CLOSE_OK) {
        err(close_error_messages[output_close_status]);
        return false;
    }

    return true;
}

