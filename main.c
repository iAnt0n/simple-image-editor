#include <stdbool.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#include "actions/actions.h"
#include "io.h"
#include "util.h"
#include "formats/formats.h"


//    -------------------------------------------------------------------------------

static void usage(const char* str) {
    err(str);
    err("\n");
    err(
            "Usage: img_edit [OPTION]... [INPUT_FILE] [OUTPUT_FILE]\n"
            "  -a, --action       transformation to apply. Default is rotate.\n"
            "  -f, --format       image format. Default is bmp.\n"
        );
    exit(EXIT_FAILURE);
}

//    -------------------------------------------------------------------------------


int main(int argc, char** argv) {
    enum format format = BMP;
    enum action action = ROTATE;
    const char* input_file_name;
    const char* output_file_name;

    struct option long_options[] = {
            {"format", required_argument, NULL, 'f'},
            {"action", required_argument, NULL, 'a'},
            {0, 0, 0, 0}
    };

    int32_t opt;

    const size_t actions_array_size = sizeof(actions_array) / sizeof(actions_array[0]);
    const size_t formats_array_size = sizeof(formats_array) / sizeof(formats_array[0]);

    while ((opt = getopt_long(argc, argv, "f:a:", long_options, NULL)) != -1) {

        bool format_found = false;
        bool action_found = false;

        switch (opt) {
            case 'f':
                for (size_t i = 0; i < formats_array_size; i++) {
                    if (strcmp(optarg, formats_array[i].format_str) == 0) {
                        format = formats_array[i].format_enum;
                        format_found = true;
                        break;
                    }
                }
                if (!format_found) { usage("Unknown format. Supported formats: bmp."); }
                break;

            case 'a':
                for (size_t i = 0; i < actions_array_size; i++) {
                    if (strcmp(optarg, actions_array[i].action_str) == 0) {
                        action = actions_array[i].action_enum;
                        action_found = true;
                        break;
                    }
                }
                if (!action_found) { usage("Unknown action. Supported actions: rotate, bw."); }
                break;

            default:
                usage("");
        }
    }

    if (optind >= argc) {
        usage("Too few arguments. You should provide input file and output file.");
    }

    if (argc - optind == 2) {
        input_file_name = argv[optind];
        output_file_name = argv[optind + 1];
    } else {
        usage("2 arguments expected");
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
