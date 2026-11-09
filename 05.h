#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <inttypes.h>
#include "libhs.h"

void ex1() {
	int stack[10] = { 0 };
	for (int i = 0; i < 10; i++) {
		printf("%2d> ", i + 1);
		(void)scanf("%d", &stack[i]);
	}
	for (int i = 9; i >= 0; i--) {
		printf("%2d: %d\n", 10 - i, stack[i]);
	}
}

void ex2() {
	unsigned n;
	printf("> ");
	(void)scanf("%u", &n);
	unsigned* mem = (unsigned*)calloc(n, sizeof(unsigned));
	if (!mem) {
		fprintf(stderr, "Out of memory\n");
		return;
	}

	if (n > 0) {
		mem[0] = 0;
		if (n > 1) {
			mem[1] = 1;
			for (unsigned i = 2; i < n; i++) {
				mem[i] = mem[i - 2] + mem[i - 1];
			}
		}

		for (unsigned i = 0; i < n; i++) {
			printf("%8u%s", mem[i], i % 5 ? " " : "\n");
		}
	}

	free(mem);
}

unsigned ex3average = 0;
void ex3a(unsigned* dst, const unsigned* src) {
	*dst = (unsigned)rand();
}

void ex3b(unsigned* acc, const unsigned* cur) {
	*acc += *cur;
}

void ex3c(unsigned* acc, const unsigned* cur) {
	*acc += (*cur) < ex3average;
}

void ex3d(unsigned* acc, const unsigned* cur) {
	const unsigned a = *acc;
	const unsigned c = *cur;

	*acc = a > c ? c : a;
}

void ex3e(unsigned* acc, const unsigned* cur) {
	const unsigned a = *acc;
	const unsigned c = *cur;

	*(unsigned*)acc = a < c ? c : a;
}

void ex3() {
	const unsigned count = 10;
	srand((unsigned)time(NULL));
	unsigned* mapped = hsMap((unsigned*)nullptr, count, (HsMapFn)ex3a);

	hsFoldl(mapped, count, (HsFoldFn)ex3b, &ex3average);
	ex3average /= count;
	
	unsigned belowAverage = 0;
	hsFoldl(mapped, count, (HsFoldFn)ex3c, &belowAverage);

	unsigned minValue = mapped[0], maxValue = mapped[0];
	hsFoldl(mapped, count, (HsFoldFn)ex3d, &minValue);
	hsFoldl(mapped, count, (HsFoldFn)ex3e, &maxValue);
	
	printf("below avg: %u, min: %u, max: %u\n", belowAverage, minValue, maxValue);

	for (unsigned i = 0; i < count; i++) printf("%u%s", mapped[i], i + 1 < count ? " " : "\n");

	free(mapped);
}

void ex4add(double* acc, const unsigned* cur) {
	*acc += (double)*cur;
}

void ex4() {
	uint32_t n;
	do {
		printf("n > ");
		(void)scanf("%u", &n);
	} while(n > 10);
	uint32_t num[10] = { 0 };
	for (uint32_t i = 0; i < n; i++) {
		do {
			printf("%2d/%2d> ", i + 1, n);
			(void)scanf("%u", &num[i]);
		} while (num[i] > 10);
	}

	double average = 0;
	hsFoldl(num, 10, (HsFoldFn)ex4add, &average);
	average /= 10;

	unsigned minValue = num[0], maxValue = num[0];
	hsFoldl(num, 10, (HsFoldFn)ex3d, &minValue);
	hsFoldl(num, 10, (HsFoldFn)ex3e, &maxValue);

	printf("avg: %lg, min: %u, max: %u\n", average, minValue, maxValue);
}

unsigned ex5happy;
void ex5a(unsigned* dst, const unsigned* src) {
	const int max_number = 10, minimum_number = 1;
	const int rnd = rand() % (max_number + 1 - minimum_number) + minimum_number;
	*dst = (unsigned)rnd;
}

bool ex5b(const unsigned* cur) {
	return *cur == ex5happy;
}

void ex5() {
	const unsigned count = 10;
	srand((unsigned)time(NULL));
	unsigned* mapped = hsMap((unsigned*)nullptr, count, (HsMapFn)ex5a);

	const int max_number = 10, minimum_number = 1;
	ex5happy = (unsigned)(rand() % (max_number + 1 - minimum_number) + minimum_number);

	const HsArray filteredResult = hsFilter(mapped, count, (HsFilterFn)ex5b);
	printf("happy number occured %zu times\n", filteredResult.len);

	hsFree(filteredResult);
	free(mapped);
}

void ex6() {
#define countof(x) (sizeof((x))/sizeof(typeof((x))))

	int32_t a[3][3] = {
		{1, 2, 3},
		{1, 2, 3},
		{1, 2, 3},
	};

	int32_t b[3][3] = {
		{1, 2, 3},
		{1, 2, 3},
		{1, 2, 3},
	};

	int32_t c[3][3];

	for (uint32_t y = 0; y < countof(a); y++) {
		for (uint32_t x = 0; x < countof(a[0]); x++) {
			c[y][x] = a[y][x] + b[y][x];
		}
	}
#undef countof
}

void ex8() {
#define mtxcoord(mtx, w, i, j) mtx[w*j+i]
	unsigned n;
	printf("n > ");
	(void)scanf("%u", &n);

	unsigned* a = (unsigned*)malloc(sizeof(unsigned) * n * n);
	if (a != nullptr) {
		for (unsigned i = 0; i < n; i++) {
			for (unsigned j = 0; j < n; j++) {
				printf("a %d %d > ", i, j);
				(void)scanf("%u", &mtxcoord(a, n, i, j));
			}
		}

		unsigned sum = 0;
		for (unsigned i = 0; i < n; i++) {
			sum += mtxcoord(a, n, i, i);
		}

		printf("%u\n", sum);

		free(a);
	}
#undef mtxcoord
}

void ex9() {
	int32_t num[10];
	for (uint8_t i = 0; i < 10; i++) {
		printf("%2u > ", i + 1);
		(void)scanf("%d", &num[i]);
	}

	for (int8_t i = 0; i < 9; i++) {
		for (int8_t j = 0; j < 9 - i; j++) {
			if (num[j] > num[j + 1]) {
				int32_t temp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = temp;
			}
		}
	}

	for (uint8_t i = 0; i < 10; i++) {
		printf("%d%c", num[i], i < 9 ? ' ' : '\n');
	}
}

void ex10sum(int32_t* acc, const int32_t* cur) {
	*acc += *cur;
}

void ex10() {
	int32_t mtx[8][8];
	int32_t rowSum[8] = { 0 }, colSum[8] = { 0 }, mtxSum = 0;

	for (uint8_t i = 0; i < 8; i++) {
		for (uint8_t j = 0; j < 8; j++) {
			printf("%d, %d > ", i + 1, j + 1);
			(void)scanf("%d", &mtx[i][j]);
			mtxSum += colSum[i] += rowSum[j] += mtx[i][j];
		}
	}

	printf(
		"row sums: %d %d %d %d %d %d %d %d\n"
		"col sums: %d %d %d %d %d %d %d %d\n"
		"sum of all values: %d\n",
		rowSum[0], rowSum[1], rowSum[2], rowSum[3], rowSum[4], rowSum[5], rowSum[6], rowSum[7],
		colSum[0], colSum[1], colSum[2], colSum[3], colSum[4], colSum[5], colSum[6], colSum[7],
		mtxSum
	);

	int32_t rs = 0, cs = 0;
	hsFoldl(rowSum, 8, (HsFoldFn)ex10sum, &rs);
	hsFoldl(colSum, 8, (HsFoldFn)ex10sum, &cs);

	assert(rs == cs && mtxSum == rs);
}

struct ex11MatrixExtrema {
	int32_t min;
	int32_t max;

	size_t min_i, min_j;
	size_t max_i, max_j;

	bool initialized;
};

bool ex11findExtrema(const void* element, size_t i, void* ctx) {
	const int32_t* row = element;
	struct ex11MatrixExtrema* result = ctx;

	for (size_t j = 0; j < 6; ++j) {
		int32_t value = row[j];

		if (!result->initialized) {
			result->min = result->max = value;
			result->min_i = result->max_i = i;
			result->min_j = result->max_j = j;
			result->initialized = true;
			continue;
		}

		if (value < result->min) {
			result->min = value;
			result->min_i = i;
			result->min_j = j;
		}

		if (value > result->max) {
			result->max = value;
			result->max_i = i;
			result->max_j = j;
		}
	}

	return false;
}

void ex11() {
	int32_t mtx[8][6];

	for (uint8_t i = 0; i < 8; i++) {
		for (uint8_t j = 0; j < 6; j++) {
			printf("%d, %d > ", i + 1, j + 1);
			(void)scanf("%d", &mtx[i][j]);
		}
	}

	struct ex11MatrixExtrema extrema = { 0 };

	HsArray result = hsFilterEx(mtx, 8, ex11findExtrema, &extrema);

	printf("Min: %d at [%zu][%zu]\n",
		extrema.min, extrema.min_i, extrema.min_j);

	printf("Max: %d at [%zu][%zu]\n",
		extrema.max, extrema.max_i, extrema.max_j);

	hsFree(result);
}

void ex12sum(int32_t* acc, const int32_t* cur, size_t i, void* ctx) {
	*acc += cur[5 - i];
}

void ex12() {
	int32_t mtx[6][6];

	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < 6; j++) {
			printf("%d, %d > ", i + 1, j + 1);
			(void)scanf("%d", &mtx[i][j]);
		}
	}

	int32_t sum = 0;

	hsFoldrEx(mtx, 6, ex12sum, &sum, nullptr);

	printf("sum: %d\n", sum);
}

struct ex13ctx_t {
	const int32_t(*mtx)[5];
};

bool ex13isSymmetric(const void* cur, size_t i, void* ctx) {
	const int32_t* row = cur;
	struct ex13ctx_t* c = ctx;

	for (size_t j = 0; j < 5; ++j) {
		if (row[j] != c->mtx[j][i])
			return false;
	}

	return true;
}

void ex13() {
	int32_t mtx[5][5];

	for (uint8_t i = 0; i < 5; i++) {
		for (uint8_t j = 0; j < 5; j++) {
			printf("%d, %d > ", i + 1, j + 1);
			(void)scanf("%d", &mtx[i][j]);
		}
	}

	struct ex13ctx_t ctx = { .mtx = mtx };

	bool symmetric = hsAllEx(mtx, 5, ex13isSymmetric, &ctx);

	printf("Matrix is %s\n", symmetric ? "symmetric" : "not symmetric");
}

void ex14sum(void* dst, const void* cur, size_t i, void* ctx) {
	int32_t* out = dst;
	const int32_t* in = cur;
	int32_t k = *(const int32_t*)ctx;

	for (size_t j = 0; j < 6; ++j) {
		out[j] = in[j] * k;
	}
}

void ex14() {
	int32_t mtx[6][6], k;

	for (uint8_t i = 0; i < 6; i++) {
		for (uint8_t j = 0; j < 6; j++) {
			printf("%d, %d > ", i + 1, j + 1);
			(void)scanf("%" SCNd32, &mtx[i][j]);
		}
	}

	printf("   k > ");
	(void)scanf("%d", &k);

	int32_t(*final)[6] = hsMapEx(
        mtx, 6, ex14sum, &k
    );

    if (final == nullptr)
        return;

    printf("\nResult:\n");

    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 6; ++j)
            printf("%6" PRId32, final[i][j]);

        printf("\n");
    }

    free(final);
}

struct ex15ctx_t {
	int32_t value;
};

bool ex15match(const void* cur, size_t i, void* ctx) {
	(void)i;

	const int32_t* value = cur;
	struct ex15ctx_t* c = ctx;

	return *value == c->value;
}

bool ex15exists(const void* cur, size_t i, void* ctx) {
	(void)i;

	return hsAnyWithStrideEx(
		cur,
		4,
		sizeof(int32_t),
		ex15match,
		ctx
	);
}

void ex15count(void* acc, const void* cur, size_t i, void* ctx) {
	(void)i;

	const int32_t* row = cur;
	struct ex15ctx_t* c = ctx;
	size_t* count = acc;

	for (size_t j = 0; j < 4; ++j)
		if (row[j] == c->value)
			++(*count);
}

void ex15print(void* acc, const void* cur, size_t i, void* ctx) {
	(void)acc;

	const int32_t* row = cur;
	struct ex15ctx_t* c = ctx;

	for (size_t j = 0; j < 4; ++j) {
		if (row[j] == c->value) {
			printf("Found at [%zu][%zu]\n", i + 1, j + 1);
		}
	}
}

void ex15() {
	int32_t mtx[8][4];

	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			printf("%zu, %zu > ", i + 1, j + 1);
			(void)scanf("%" SCNd32, &mtx[i][j]);
		}
	}

	struct ex15ctx_t ctx;

	printf("Search value > ");
	(void)scanf("%" SCNd32, &ctx.value);

	if (!hsAnyEx(mtx, 8, ex15exists, &ctx)) {
		puts("Value not found.");
		return;
	}

	size_t count = 0;

	hsFoldlEx(mtx, 8, ex15count, &count, &ctx);
	hsFoldlEx(mtx, 8, ex15print, nullptr, &ctx);

	printf("Occurrences: %zu\n", count);
}

bool ex16check(const void* cur, size_t i, void* ctx) {
	const int32_t* row = cur;

	for (size_t j = 0; j < 5; ++j) {
		if (row[j] != (i == j ? 1 : 0))
			return false;
	}

	return true;
}

void ex16() {
	int32_t mtx[5][5];

	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			printf("%zu, %zu > ", i + 1, j + 1);
			(void)scanf("%" SCNd32, &mtx[i][j]);
		}
	}

	puts(hsAllEx(mtx, 5, ex16check, nullptr) ? "Matrix is an identity matrix." : "Matrix is not an identity matrix.");
}

struct ex17sums_t {
	int64_t rows[8];
	int64_t cols[6];
};

struct ex17max_t {
	int64_t value;
	size_t index;
	bool initialized;
};

void ex17sum(void* acc, const void* cur, size_t i, void* ctx) {
	(void)ctx;

	struct ex17sums_t* sums = acc;
	const int32_t* row = cur;

	for (size_t j = 0; j < 6; ++j) {
		sums->rows[i] += row[j];
		sums->cols[j] += row[j];
	}
}

void ex17max(void* acc, const void* cur, size_t i, void* ctx) {
	(void)ctx;

	struct ex17max_t* max = acc;
	int64_t value = *(const int64_t*)cur;

	if (!max->initialized || value > max->value) {
		max->value = value;
		max->index = i;
		max->initialized = true;
	}
}

void ex17(void) {
	int32_t mtx[8][6];

	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 6; ++j) {
			printf("%zu, %zu > ", i + 1, j + 1);
			(void)scanf("%" SCNd32, &mtx[i][j]);
		}
	}

	struct ex17sums_t sums = { 0 };

	hsFoldlEx(mtx, 8, ex17sum, &sums, nullptr);

	struct ex17max_t max_row = { 0 };
	struct ex17max_t max_col = { 0 };

	hsFoldlEx(sums.rows, 8, ex17max, &max_row, nullptr);

	hsFoldlEx(sums.cols, 6, ex17max, &max_col, nullptr);

	puts("\nRow sums:");

	for (size_t i = 0; i < 8; ++i) {
		printf("Row %zu: %" PRId64 "\n",
			i + 1, sums.rows[i]);
	}

	printf(
		"Largest row: %zu (sum: %" PRId64 ")\n",
		max_row.index + 1,
		max_row.value
	);

	puts("\nColumn sums:");

	for (size_t j = 0; j < 6; ++j) {
		printf("Column %zu: %" PRId64 "\n",
			j + 1, sums.cols[j]);
	}

	printf(
		"Largest column: %zu (sum: %" PRId64 ")\n",
		max_col.index + 1,
		max_col.value
	);
}
