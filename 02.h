#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ex1() {
	/* x ∈ [5, 7] */
	/*for (int i = 5; i <= 7; i++) {*/

	/* x ∈ [5, 7) */
	/*for (int i = 5; i < 7; i++) {*/

	/* x ∈ [0, 10], x mod 2 == 0 */
	/*for (int i = 0; i <= 10; i += 2) { */

	/* x ∈ [0, 10], reverse [0, 10] */
	for (int i = 10; i >= 0; i--) {
		printf("%d\n", i);
	}
}

void ex2() {
	int start = 0, limit = 200, step = 20, fahr = start, celsius;

	while (fahr <= limit) {
		celsius = 5 * (fahr - 32) / 9;
		printf("%3d %6.1f\n", fahr, (float)celsius);
		fahr += step;
	}
}

void ex3() {
	const int start = 0, limit = 200, step = 20;

	for (int fahr = start; fahr <= limit; fahr += step) {
		float celsius = 5 * ((float)fahr - 32) / 9;
		printf("%3d %6.1f\n", fahr, celsius);
	}
}

void ex6() {
	int start, limit, step;

	printf("Enter start, limit, step: ");
	(void)scanf("%d %d %d", &start, &limit, &step);

	for(int fahr = start; fahr <= limit; fahr += step) {
		float celsius = 5 * ((float)fahr - 32) / 9;
		printf("%3d %6.1f\n", fahr, celsius);
	}
}

void ex7() {
	for (int i = 0; i < 10; i++) {
		float num;
		printf("enter any real number ");
		(void)scanf("%g", &num);
		if (num > 0) {
			printf("%g\n", num);
		}
	}
}

void ex8() {
	for (int i = 0; i <= 100; i += 2) {
		printf("%3d%c", i, i % 10 == 0 ? '\n' : ' ');
	}
}

void ex9() {
	int n = -1;
	while(1) {
		printf("enter any natural number ");
		(void)scanf("%d", &n);
		if (!n) {
			printf("zero is not a natural number\n");
		} else if (n < 0) {
			printf("negative numbers are not natural numbers\n");
		} else {
			break;
		}
	}

	for (int i = 0; i <= 100; i++) {
		if (i % n == 0) {
			printf("%3d%c", i, i % 10 == 0 ? '\n' : ' ');
		}
	}
}

void ex10() {
	int n = -1;
	int divisible = 0;
	while (1) {
		printf("enter any natural number ");
		(void)scanf("%d", &n);
		if (!n) {
			printf("zero is not a natural number\n");
		}
		else if (n < 0) {
			printf("negative numbers are not natural numbers\n");
		}
		else {
			break;
		}
	}

	for (int i = 0; i <= 100; i++) {
		if (i % n == 0) {
			divisible++;
		}
	}

	printf("there are %d numbers divisible by %d in the range [0, 100]\n", divisible, n);
}

void ex11() {
	int a, b;

	printf("enter two natural numbers ");
	(void)scanf("%d %d", &a, &b);

	const int bigger = a > b ? a : b;
	const int smaller = a <= b ? a : b;

	for (int i = smaller; i < bigger; i++) {
		if (i % 3 == 0) {
			printf("%d%c", i, i % 24 == 0 ? '\n' : ' ');
		}
	}
}

void ex12() {
	int n = -1;
	while(1) {
		printf("enter any natural number ");
		(void)scanf("%d", &n);
		if (!n) {
			printf("zero is not a natural number\n");
		}
		else if (n < 0) {
			printf("negative numbers are not natural numbers\n");
		}
		else {
			break;
		}
	}

	float sum = 0;

	for (int i = 0; i < n; i++) {
		printf("enter #%d real number ", i + 1);
		float num;
		(void)scanf("%g", &num);
		sum += num;
	}

	printf("average of %d numbers is %g\n", n, sum / n);
}

void ex13() {
	for (int i = 100; i >= 0; i--) {
		printf("%3d%c", i, i % 10 == 0 ? '\n' : ' ');
	}
}

void ex14() {
	int a, b, c;
	printf("enter 3 natural numbers ");
	(void)scanf("%d %d %d", &a, &b, &c);

	printf("the smallest number is %d\n", a < b ? (a < c ? a : c) : (b < c ? b : c));
}

void ex15() {
	int n, m;
	printf("enter 2 natural numbers (n, m) ");
	(void)scanf("%d %d", &n, &m);

	const minimum_number = 0;
	const max_number = m;

	srand((unsigned)time(NULL));

	printf("Random numbers between %d and %d:\n", minimum_number, max_number);

	for (int i = 0; i < n; i++) {

		// Source - https://stackoverflow.com/a/1202706
		// Posted by Tyler McHenry, modified by community. See post 'Timeline' for change history
		// Retrieved 2026-10-13, License - CC BY-SA 3.0
		const rnd = rand() % (max_number + 1 - minimum_number) + minimum_number;

		printf("%3d%c", rnd, i % (n / 10) == 0 ? '\n' : ' ');
	}
}

void ex16() {
	const minimum_number = 0;
	const max_number = 10;

	int luckynumber;
	int luckycount = 0;

	printf("enter your lucky number ");
	(void)scanf("%d", &luckynumber);

	srand((unsigned)time(NULL));

	for (int i = 0; i < 10; i++) {
		const rnd = rand() % (max_number + 1 - minimum_number) + minimum_number;
		if(rnd == luckynumber) {
			luckycount++;
		}
	}

	printf("your lucky number %d appeared %d times\n", luckynumber, luckycount);
}