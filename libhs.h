#pragma once
#ifndef LIBHS_H
#define LIBHS_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define let const auto
#ifndef nullptr
#define nullptr NULL
#endif

typedef void (*HsMapFn)(void* dst, const void* src);
typedef void (*HsFoldFn)(void* acc, const void* cur);
typedef bool (*HsFilterFn)(const void* cur);
typedef struct { void* ptr; size_t len; size_t stride; } HsArray;

#define hsMap(src, len, fn) (typeof(src))hsMapWithStride(src, len, sizeof(*(src)), fn)
#define hsFold(src, len, fn, init) hsFoldWithStride(src, len, sizeof(*(src)), fn, init)
#define hsFilter(src, len, fn) hsFilterWithStride(src, len, sizeof(*(src)), fn)

void* hsMapWithStride(const void* src, size_t len, size_t stride, HsMapFn fn) {
    if (stride == 0 || fn == nullptr)
        return nullptr;

    if (len > SIZE_MAX / stride)
        return nullptr;

    void* dst = malloc(len * stride);

    if (dst == nullptr && len != 0)
        return nullptr;

    for (size_t i = 0; i < len; ++i) {
        void* out = (unsigned char*)dst + i * stride;

        const void* in = src == nullptr
            ? nullptr
            : (const unsigned char*)src + i * stride;

        fn(out, in);
    }

    return dst;
}

void hsFoldWithStride(const void* src, size_t len, size_t stride, HsFoldFn fn, void* init) {
    if (stride == 0 || fn == nullptr || init == nullptr)
        return;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur);
    }
}

HsArray hsFilterWithStride(const void* src, size_t len, size_t stride, HsFilterFn fn) {
    if (len == 0 || stride == 0 || src == nullptr)
        return (HsArray) { .ptr = nullptr, .len = 0, .stride = stride };
    if(fn == nullptr) {
        void* mem = malloc(stride* len);
        if(mem == nullptr)
            return (HsArray) { .ptr = nullptr, .len = 0, .stride = stride };
        return (HsArray) { .ptr = memcpy(mem, src, stride * len), .len = len, .stride = stride };
    }

    void* mem = malloc(stride * len);
    if (mem == nullptr)
        return (HsArray) { .ptr = nullptr, .len = 0, .stride = stride };
    size_t write = 0;
    bool atLeastOneCorrect = false;
    for (size_t r = 0; r < len; r++) {
        const void* cur =
            (const unsigned char*)src + r * stride;
        if (fn(cur)) {
            memcpy((unsigned char*)mem + (write++) * stride, cur, stride);
            atLeastOneCorrect = true;
        }
    }

    return (HsArray) {.ptr = mem, .len = atLeastOneCorrect ? write - 1 : 0, .stride = stride };
}

void hsFree(HsArray array) {
    free(array.ptr);
}

#endif
