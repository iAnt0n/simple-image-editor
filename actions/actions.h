#ifndef _ACTIONS_H_
#define _ACTIONS_H_

#include "rotate.h"
#include "black_and_white.h"

typedef struct image do_action(struct image);

enum action {
    ROTATE = 0,
    BW
    //More possible actions
};

do_action* const actions[] = {
        [ROTATE] = rotate_90,
        [BW] = to_bw
};

const struct {
    enum action action_enum;
    const char* action_str;
} actions_array[] = {
        {ROTATE, "rotate"},
        {BW, "bw"},
};

#endif //_ACTIONS_H_
