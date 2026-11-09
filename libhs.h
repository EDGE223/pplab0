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

typedef bool (*HsFilterFn)(const void* cur);
typedef bool (*HsFilterFnEx)(const void* element, size_t i, void* ctx);
typedef void (*HsFoldFn)(void* acc, const void* cur);
typedef void (*HsFoldFnEx)(void* acc, const void* cur, size_t i, void* ctx);
typedef bool (*HsPredicateFn)(const void* cur);
typedef bool (*HsPredicateFnEx)(const void* cur, size_t i, void* ctx);
typedef void (*HsMapFn)(void* dst, const void* src);
typedef void (*HsMapFnEx)(void* dst, const void* src, size_t i, void* ctx);

typedef struct { void* ptr; size_t len; size_t stride; } HsArray;


#define hsAll(src, len, fn) hsAllWithStride(src, len, sizeof(*(src)), fn)
#define hsAllEx(src, len, fn, ctx) hsAllWithStrideEx(src, len, sizeof(*(src)), fn, ctx)
#define hsAny(src, len, fn) hsAnyWithStride(src, len, sizeof(*(src)), fn)
#define hsAnyEx(src, len, fn, ctx) hsAnyWithStrideEx(src, len, sizeof(*(src)), fn, ctx)
#define hsFilter(src, len, fn) hsFilterWithStride(src, len, sizeof(*(src)), fn)
#define hsFilterEx(src, len, fn, ctx) hsFilterWithStrideEx(src, len, sizeof(*(src)), fn, ctx)
#define hsFoldl(src, len, fn, init) hsFoldlWithStride(src, len, sizeof(*(src)), fn, init)
#define hsFoldlEx(src, len, fn, init, ctx) hsFoldlWithStrideEx(src, len, sizeof(*(src)), fn, init, ctx)
#define hsFoldr(src, len, fn, init) hsFoldrWithStride(src, len, sizeof(*(src)), fn, init)
#define hsFoldrEx(src, len, fn, init, ctx) hsFoldrWithStrideEx(src, len, sizeof(*(src)), fn, init, ctx)
#define hsMap(src, len, fn) /*(typeof(src))*/hsMapWithStride(src, len, sizeof(*(src)), fn)
#define hsMapEx(src, len, fn, ctx) /*(typeof(src))*/hsMapWithStrideEx(src, len, sizeof(*(src)), fn, ctx)

bool hsAllWithStride(const void* src, size_t len, size_t stride, HsPredicateFn fn) {
    if (len == 0)
        return true;

    if (src == nullptr || stride == 0 || fn == nullptr)
        return false;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        if (!fn(cur))
            return false;
    }

    return true;
}

bool hsAllWithStrideEx(const void* src, size_t len, size_t stride, HsPredicateFnEx fn, void* ctx) {
    if (len == 0)
        return true;

    if (src == nullptr || stride == 0 || fn == nullptr)
        return false;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        if (!fn(cur, i, ctx))
            return false;
    }

    return true;
}

bool hsAnyWithStride(const void* src, size_t len, size_t stride, HsPredicateFn fn) {
    if (src == nullptr || stride == 0 || fn == nullptr)
        return false;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        if (fn(cur))
            return true;
    }

    return false;
}

bool hsAnyWithStrideEx(const void* src, size_t len, size_t stride, HsPredicateFnEx fn, void* ctx) {
    if (src == nullptr || stride == 0 || fn == nullptr)
        return false;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        if (fn(cur, i, ctx))
            return true;
    }

    return false;
}

HsArray hsFilterWithStride(const void* src, size_t len, size_t stride, HsFilterFn fn) {
    if (len == 0 || stride == 0 || src == nullptr)
        return (HsArray) { .ptr = nullptr, .len = 0, .stride = stride };
    if (fn == nullptr) {
        void* mem = malloc(stride * len);
        if (mem == nullptr)
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

    return (HsArray) { .ptr = mem, .len = atLeastOneCorrect ? write - 1 : 0, .stride = stride };
}

HsArray hsFilterWithStrideEx(const void* src, size_t len, size_t stride, HsFilterFnEx fn, void* ctx) {
    if (len == 0 || stride == 0 || src == nullptr)
        return (HsArray) {
        .ptr = nullptr,
            .len = 0,
            .stride = stride
    };

    if (len > SIZE_MAX / stride)
        return (HsArray) {
        .ptr = nullptr,
            .len = 0,
            .stride = stride
    };

    size_t bytes = stride * len;

    void* mem = malloc(bytes);
    if (mem == nullptr)
        return (HsArray) {
        .ptr = nullptr,
            .len = 0,
            .stride = stride
    };

    size_t write = 0;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        if (fn == nullptr || fn(cur, i, ctx)) {
            memcpy(
                (unsigned char*)mem + write * stride,
                cur,
                stride
            );
            ++write;
        }
    }

    if (write == 0) {
        free(mem);
        mem = nullptr;
    }

    return (HsArray) {
        .ptr = mem,
            .len = write,
            .stride = stride
    };
}

void hsFoldlWithStride(const void* src, size_t len, size_t stride, HsFoldFn fn, void* init) {
    if (stride == 0 || fn == nullptr || init == nullptr)
        return;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur);
    }
}

void hsFoldlWithStrideEx(const void* src, size_t len, size_t stride, HsFoldFnEx fn, void* init, void* ctx) {
    if (len == 0 || stride == 0 ||
        src == nullptr || fn == nullptr || init == nullptr)
        return;

    for (size_t i = 0; i < len; ++i) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur, i, ctx);
    }
}

void hsFoldrWithStride(const void* src, size_t len, size_t stride, HsFoldFn fn, void* init) {
    if (len == 0 || stride == 0 ||
        src == nullptr || fn == nullptr || init == nullptr)
        return;

    for (size_t i = len; i-- > 0;) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur);
    }
}

void hsFoldrWithStrideEx(const void* src, size_t len, size_t stride, HsFoldFnEx fn, void* init, void* ctx) {
    if (len == 0 || stride == 0 ||
        src == nullptr || fn == nullptr || init == nullptr)
        return;

    for (size_t i = len; i-- > 0;) {
        const void* cur =
            (const unsigned char*)src + i * stride;

        fn(init, cur, i, ctx);
    }
}

void hsFree(HsArray array) {
    free(array.ptr);
}

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

void* hsMapWithStrideEx(const void* src, size_t len, size_t stride, HsMapFnEx fn, void* ctx) {
    if (stride == 0 || fn == nullptr)
        return nullptr;

    if (len > SIZE_MAX / stride)
        return nullptr;

    void* dst = malloc(len * stride);

    if (dst == nullptr && len != 0)
        return nullptr;

    for (size_t i = 0; i < len; ++i) {
        void* out =
            (unsigned char*)dst + i * stride;

        const void* in = src == nullptr
            ? nullptr
            : (const unsigned char*)src + i * stride;

        fn(out, in, i, ctx);
    }

    return dst;
}

#endif
