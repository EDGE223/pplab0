#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
	unsigned* mem = calloc(n, sizeof(unsigned));
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
	unsigned* mapped = hsMap((unsigned*)nullptr, count, ex3a);

	hsFold(mapped, count, ex3b, &ex3average);
	ex3average /= count;
	
	unsigned belowAverage = 0;
	hsFold(mapped, count, ex3c, &belowAverage);

	unsigned minValue = mapped[0], maxValue = mapped[0];
	hsFold(mapped, count, ex3d, &minValue);
	hsFold(mapped, count, ex3e, &maxValue);
	
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
	hsFold(num, 10, ex4add, &average);
	average /= 10;

	unsigned minValue = num[0], maxValue = num[0];
	hsFold(num, 10, ex3d, &minValue);
	hsFold(num, 10, ex3e, &maxValue);

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
	unsigned* mapped = hsMap((unsigned*)nullptr, count, ex5a);

	const int max_number = 10, minimum_number = 1;
	ex5happy = (unsigned)(rand() % (max_number + 1 - minimum_number) + minimum_number);

	const HsArray filteredResult = hsFilter(mapped, count, ex5b);
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

	typeof(a) c;

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

	unsigned* a = malloc(sizeof(unsigned) * n * n);
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
	uint32_t n;
	printf("n > ");
	(void)scanf("%s", &n);
	int32_t* num = malloc(n*sizeof(int32_t));
}
