#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;

typedef struct {
    size_t len;
    size_t capacity;
    byte* raw;
} dbuf;

dbuf dbuf_new(size_t capacity) {
    return (dbuf){0, capacity, (byte*)malloc(capacity)};
}

int dbuf_extend(dbuf* buf, size_t c) {
    if (buf->capacity + c < 0) return -1;
    buf->capacity += c;
    if (buf->capacity < buf->len) buf->len = buf->capacity;
    buf->raw = realloc(buf->raw, buf->capacity);
    return 0;
}

void dbuf_add(dbuf* buf, byte b) {
    if (buf->capacity == buf->len) dbuf_extend(buf, 1);
    buf->raw[buf->len] = b;
    buf->len++;
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
