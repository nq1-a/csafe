#pragma once

#include <assert.h>

#include "types.h"

typedef enum {
    NONE,
    SOME
} Option;

typedef struct {
    Option valid;
    void* ref;
} option;

option opt_some(void* ref) {
    return (option){SOME, ref};
}

option opt_none() {
    return (option){NONE, (void*)0};
}

void* opt_unwrap(option* o) {
    assert(o->valid);
    return o->ref;
}
