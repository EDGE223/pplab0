#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void ex1() {
	char buf[1024] = { 0 };
	printf("What's your name? ");
	(void)scanf("%s", buf);
	printf("Hi, %s", buf);
}

void ex2() {
	for (size_t lhs = 1; lhs <= 10; lhs++) {
		if (lhs == 1) {
			printf("    ");
			for (size_t i = 1; i <= 10; i++) printf("%3llu%c", i, i % 10 ? ' ' : '\n');
		}
		printf("%3llu ", lhs);
		for (size_t rhs = 1; rhs <= 10; rhs++) {
			printf("%3llu%c", lhs * rhs, rhs % 10 ? ' ' : '\n');
		}
	}
}

int ex3b(int a, int b) { return a > b ? a : b; }
void ex3a(int a, int b) { printf("%d\n", ex3b(a, b)); }

void ex3() {
	int a, b;
	printf("> ");
	(void)scanf("%d %d", &a, &b);
	ex3a(a, b);
	(void)ex3b(a, b);
}

int ex4b(int a, int b, int c) {
	return a < b && b < c
		? a
		: b < a && a < c
			? b
			: c
	;
}
void ex4a(int a, int b, int c) { printf("%d\n", ex4b(a, b, c)); }

void ex4() {
	int a, b, c;
	printf("> ");
	(void)scanf("%d %d %d", &a, &b, &c);
	ex4a(a, b, c);
	(void)ex4b(a, b, c);
}

double ex5() {
	float lhs, rhs;
	printf("> ");
	(void)scanf("%g %g", &lhs, &rhs);
	const double result = lhs * rhs * 0.5;
	printf("%g\n", result);
	return result;
}

void ex6() {
	unsigned int n;
	printf("> ");
	(void)scanf("%u", &n);
	for (unsigned int i = 1; i < n / 2; i++) {
		if (!(n % 2)) printf("%u\n", n);
	}
}

double ex7() {
	float lhs, rhs;
	printf("> ");
	(void)scanf("%g %g", &lhs, &rhs);
	return (lhs + rhs) / 2;
}

void ex8() {
	float lhs, rhs;
	printf("> ");
	(void)scanf("%g %g", &lhs, &rhs);
	printf("%g\n", sqrt((lhs*lhs)+(rhs*rhs)));
}

#define clearStdIn do{int c; while ((c = getchar()) != '\n' && c != EOF) {}} while (0)

float ex9add(float lhs, float rhs) { return lhs + rhs; }
float ex9sub(float lhs, float rhs) { return lhs - rhs; }
float ex9mul(float lhs, float rhs) { return lhs * rhs; }
float ex9div(float lhs, float rhs) {
	if (!rhs) {
		printf("Division by zero is prohibited!\n");
		exit(1);
	}
	return lhs / rhs;
}

void ex9() {
	float lhs, rhs, res;
	char opr = 0;
	while (opr != 'e') {
		printf("lhs? "); (void)scanf("%g", &lhs);
		printf("rhs? "); (void)scanf("%g", &rhs);
		clearStdIn;
		printf("+ - * / ? "); (void)scanf("%c", &opr);
		switch (opr) {
		case '+':
			res = ex9add(lhs, rhs);
			break;
		case '-':
			res = ex9sub(lhs, rhs);
			break;
		case '*':
			res = ex9mul(lhs, rhs);
			break;
		case '/':
			res = ex9div(lhs, rhs);
			break;
		case 'e':
			return;
		default:
			printf("Operator %c isn't supported by now!\n", opr);
			return;
		}
		printf("%g %c %g = %g\n", lhs, opr, rhs, res);
	}
}

unsigned ex10a(unsigned n) {
	unsigned sum = 0;
	for (unsigned i = 0; i < n; i++) {
		printf("%3d: ", i);
		unsigned t;
		(void)scanf("%u", &t);
		sum += t;
	}
	return sum;
}
void ex10b(unsigned n) {
	unsigned sum = 0;
	for (unsigned i = 0; i < n; i++) {
		printf("%3d: ", i);
		unsigned t;
		(void)scanf("%u", &t);
		sum += t;
	}
	printf("%u\n", sum);
}

void ex10() {
	unsigned n;
	printf("> ");
	(void)scanf("%u", &n);
	ex10b(n);
}

float ex11() {
	float width, height;
	printf("W H> ");
	(void)scanf("%g %g", &width, &height);
	return (width + height) * 2;
}

double ex12() {
	float width, height, depth;
	printf("W H D> ");
	(void)scanf("%g %g %g", &width, &height, &depth);
	return width * height * depth;
}

double ex13() {
	float a;
	unsigned b;
	printf("> ");
	(void)scanf("%g %u", &a, &b);
	if (b == 0) return 1;
	double res = 1;
	while (b-- > 0) {
		res *= a;
	}
	return res;
}

size_t ex14() {
	unsigned a;
	printf("> ");
	(void)scanf("%u", &a);
	if (a == 0) return 1;
	size_t res = 1;
	while (a > 0) {
		res *= a;
		a--;
	}
	return res;
}
