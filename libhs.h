#pragma once
#ifndef LIBHS_H
#define LIBHS_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define let const auto
#ifndef nullptr
#define nullptr NULL
#endif

typedef void (*MapFn)(void* dst, const void* src);
typedef void (*FoldFn)(void* acc, const void* cur);

#define hsMap(src, len, fn) (typeof(src))hsMapWithStride(src, len, sizeof(*(src)), fn)
#define hsFold(src, len, fn, init) hsFoldWithStride(src, len, sizeof(*(src)), fn, init)

void* hsMapWithStride(const void* src, size_t len, size_t stride, MapFn fn) {
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

void hsFoldWithStride(const void* src, size_t len, size_t stride, FoldFn fn, void* init) {
    if (stride == 0 || fn == nullptr || init == nullptr)
        return;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur);
    }
}

#endif
