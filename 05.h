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
