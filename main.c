#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

#include "bmp.h"
#include "rotate.h"
#include "black_and_white.h"
#include "io.h"
#include "util.h"

typedef enum read_status reader(FILE*, struct image*);

typedef enum write_status writer(FILE*, const struct image*);

typedef struct image action(struct image);

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

enum action {
    ROTATE = 0,
    BW
    //More possible actions
};

static action* const actions[] = {
        [ROTATE] = rotate_90,
        [BW] = to_bw
};

static const struct {
    enum format format_enum;
    const char* format_str;
} formats_array[] = {
        {BMP, "bmp"},
};

static const struct {
    enum action action_enum;
    const char* action_str;
} actions_array[] = {
        {ROTATE, "rotate"},
        {BW, "bw"},
};


static void usage(const char* str) {
    err(str);
}

//    -------------------------------------------------------------------------------


int main(int argc, char** argv) {
    enum format format;
    enum action action;
    const char* input_file_name;
    const char* output_file_name;

    struct option long_options[] = {
            {"format", required_argument, NULL, 'f'},
            {"action", required_argument, NULL, 'a'},
            {0, 0, 0,                           0}
    };

    int32_t opt;

    const size_t actions_array_size = sizeof(actions_array) / sizeof(actions_array[0]);
    const size_t formats_array_size = sizeof(formats_array) / sizeof(formats_array[0]);

    while ((opt = getopt_long(argc, argv, "f:a:", long_options, NULL)) != -1) {

        switch (opt) {
            case 'f':
                for (size_t i = 0; i < formats_array_size; i++) {
                    if (strcmp(optarg, formats_array[i].format_str) == 0) {
                        format = formats_array[i].format_enum;
                        break;
                    }
                }
                usage("-f");
                break;

            case 'a':
                for (size_t i = 0; i < actions_array_size; i++) {
                    if (strcmp(optarg, actions_array[i].action_str) == 0) {
                        action = actions_array[i].action_enum;
                        break;
                    }
                }
                usage("-a");
                break;

            default:
                usage("?????");
        }
    }

    if (optind >= argc) {
        usage("MALO ARGS");
    }

    if (argc - optind == 2) {
        input_file_name = argv[optind];
        output_file_name = argv[optind + 1];
    } else {
        usage("ARGS N");
    }


//    -------------------------------------------------------------------------------

    struct image img = {0};

    if (!load_image_from_file(input_file_name, &img, readers[format])) {
        return 1;
    }

    struct image result = actions[action](img);

    if (!write_image_to_file(output_file_name, &result, writers[format])) {
        image_destroy(&img);
        image_destroy(&result);
        return 1;
    }

    image_destroy(&img);
    image_destroy(&result);

    return 0;
}
