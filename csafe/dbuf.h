#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "option.h"
#include "result.h"
#include "types.h"

typedef struct {
    size_t len;
    size_t capacity;
    u8* raw;
} dbuf;

dbuf dbuf_new(size_t capacity) {
    return (dbuf){0, capacity, (u8*)malloc(capacity)};
}

Result dbuf_extend(dbuf* buf, size_t c) {
    if (buf->capacity + c < 0) return ERR;

    buf->capacity += c;
    if (buf->capacity < buf->len) buf->len = buf->capacity;
    buf->raw = realloc(buf->raw, buf->capacity);

    return SUC;
}

void dbuf_add(dbuf* buf, u8 b) {
    if (buf->capacity == buf->len) dbuf_extend(buf, 1);
    buf->raw[buf->len] = b;
    buf->len++;
}

option dbuf_get(dbuf* buf, size_t i) {
    if (i >= buf->len || i < 0) return opt_none();
    return opt_some((void*)(buf->raw + i));
}

Result dbuf_set(dbuf* buf, u8 b, size_t i) {
    if (i >= buf->len || i < 0) return ERR;
    buf->raw[i] = b;
    return SUC;
}

void dbuf_debug(dbuf* dbuf) {
    if (dbuf->len < 1) {
        puts("{}");
        return;
    }

    printf("{%hhd", dbuf->raw[0]);

    for (size_t i = 1; i < dbuf->len; i++) {
        printf(", %hhd", dbuf->raw[i]);
    }

    puts("}");
}
