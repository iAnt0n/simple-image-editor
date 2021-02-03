#ifndef _FORMATS_H_
#define _FORMATS_H_

#include <stdio.h>
#include "bmp.h"

typedef enum read_status reader(FILE*, struct image*);

typedef enum write_status writer(FILE*, const struct image*);

enum format {
    BMP = 0
    //More possible formats
};

reader* const readers[] = {
        [BMP] = from_bmp
};

writer* const writers[] = {
        [BMP] = to_bmp
};

const struct {
    enum format format_enum;
    const char* format_str;
} formats_array[] = {
        {BMP, "bmp"},
};


#endif //_FORMATS_H_

