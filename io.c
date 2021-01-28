#include <stdbool.h>

#include "io.h"
#include "util.h"

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

    if (open_file(&file, filename, "rb") == OPEN_ERROR) {
        err("не открылся исходник", "\n");
        return false;
    }

    enum read_status read_status = reader(file, image);

    if (read_status != READ_OK) {
        err("не прочитался исходник", "\n");
        return false;
    }

    if (close_file(&file) == CLOSE_ERROR) {
        err("не закрылся исходник", "\n");
        return false;
    }
    return true;
}

bool
write_image_to_file(const char* filename, const struct image* image, enum write_status (writer)(FILE*, const struct image*)) {
    FILE* file = NULL;

    if (open_file(&file, filename, "wb") == OPEN_ERROR) {
        err("не открылся результат", "\n");
        return false;
    }

    enum write_status write_status = writer(file, image);

    if (write_status != WRITE_OK) {
        err("не записался результат", "\n");
        return false;
    }

    if (close_file(&file) == CLOSE_ERROR) {
        err("не закрылся результат", "\n");
        return false;
    }

    return true;
}

