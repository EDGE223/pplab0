#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

void ex1() {
	int a, b;
	printf("? ");
	(void)scanf("%d %d", &a, &b);
	printf("a %c b", a == b ? '=' : a < b ? '<' : '>');
}

void ex3() {
	int r;
	printf("r? ");
	(void)scanf("%d", &r);
	if (0.7 <= r && r <= 1) {
		printf("very high positive correlation\n");
	}
	else if (r >= 0.5) {
		printf("high positive correlation\n");
	}
	else if (r >= 0.3) {
		printf("moderate positive correlation\n");
	}
	else if (r >= 0.2) {
		printf("weak positive correlation\n");
	}
	else if (r >= 0) {
		printf("there is no postive correlation\n");
	}
}

#define clearStdIn do{int c; while ((c = getchar()) != '\n' && c != EOF) {}} while (0)

void ex4() {
	float lhs, rhs, res;
	char opr;
	printf("lhs? "); (void)scanf("%g", &lhs);
	printf("rhs? "); (void)scanf("%g", &rhs);
	clearStdIn;
	printf("+ - * / ? "); (void)scanf("%c", &opr);
	switch (opr) {
	case '+':
		res = lhs + rhs;
		break;
	case '-':
		res = lhs - rhs;
		break;
	case '*':
		res = lhs * rhs;
		break;
	case '/':
		if (!rhs) {
			printf("Division by zero is prohibited!\n");
			return;
		}
		res = lhs / rhs;
		break;
	default:
		printf("Operator %c isn't supported by now!\n", opr);
		return;
	}
	printf("%g %c %g = %g\n", lhs, opr, rhs, res);
}

void ex5() {
	int i = 0;
	while (1) printf("%4d%c", i++, (i-1)%9?' ':'\n');
}

void ex6() {
	float lhs, rhs, res;
	char opr = 0;
	while (opr != 'e') {
		printf("lhs? "); (void)scanf("%g", &lhs);
		printf("rhs? "); (void)scanf("%g", &rhs);
		clearStdIn;
		printf("+ - * / ? "); (void)scanf("%c", &opr);
		switch (opr) {
		case '+':
			res = lhs + rhs;
			break;
		case '-':
			res = lhs - rhs;
			break;
		case '*':
			res = lhs * rhs;
			break;
		case '/':
			if (!rhs) {
				printf("Division by zero is prohibited!\n");
				return;
			}
			res = lhs / rhs;
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

void ex7() {
	int i = 0;
	while (1) {
		if (i == 200) break;
		if (!(i % 2)) {
			i++;
			continue;
		}
		printf("%3d%c", i, i % 9 ? ' ' : '\n');
		i++;
	}
}

void ex8() {
	float n;
	printf("n? ");
	(void)scanf("%g", &n);
	const unsigned long long root = (unsigned long long)sqrt(n);
	for (int i = 2; i <= root; i++) {
		if (n / i == (int)(n / i)) {
			printf("%g's first divisor: %d\n", n, i);
			return;
		}
	}
	printf("%g have no natural divisors\n", n);
}

void ex9() {
	float c;
	printf("C? ");
	(void)scanf("%g", &c);
	if (c < 0) {
		printf("frosty\n");
	}
	else if (c >= 0 && c <= 10) {
		printf("cold\n");
	}
	else if (c > 10 && c < 20) {
		printf("mild\n");
	}
	else if (c >= 20 && c < 30) {
		printf("warm\n");
	}
	else if (c >=30) {
		printf("hot\n");
	}
}

void ex10() {
	int a, b, c;
	printf("enter 3 natural numbers ");
	(void)scanf("%d %d %d", &a, &b, &c);

	printf("the biggest number is %d\n", a > b ? (a > c ? a : c) : (b > c ? b : c));
}

void ex11() {
	int year;
	printf("year? ");
	(void)scanf("%d", &year);
	printf("the year %d is%s leap year\n", year, (year % 4 == 0 && year % 100 != 0 || year % 4 == 0 && year % 400 == 0) ? "" : "n't a");
}

void ex12() {
	int option;
	printf(
		"1. Start\n"
		"2. Settings\n"
		"3. Help\n"
		"4. End\n"
		"> "
	);
	(void)scanf("%d", &option);
	printf("Selected ");
	switch (option) {
	case 1: printf("Start"); break;
	case 2: printf("Settings"); break;
	case 3: printf("Help"); break;
	case 4: printf("End"); break;
	default: printf("Undefined option"); break;
	}
	printf("\n");
}

void ex13() {
	int option;
	printf("Enter a grade: ");
	(void)scanf("%d", &option);
	switch (option) {
	case 1: printf("(F) Failing"); break;
	case 2: printf("(D) Below average"); break;
	case 3: printf("(C) Average"); break;
	case 4: printf("(B) Good"); break;
	case 5: printf("(A) Excellent"); break;
	default: printf("(E) Entered grade is incorrect"); break;
	}
	printf("\n");
}

void ex14() {
	size_t sum = 0;
	for (size_t i = 0; i < 100; i++) {
		if (i % 3) sum += i;
		else continue;
	}
	printf("sum of elements not divisable by 3 is %llu\n", sum);
}

void ex15() {
	for (size_t i = 1; i < 1000; i++) {
		if (i > 50 && i % 7 == 0) {
			printf("%llu\n", i); break;
		}
	}
}

void ex16() {
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

void ex17() {
	size_t num;
	printf("> ");
	(void)scanf("%llu", &num);
	unsigned i = 1;
	while (num > 10) {
		num /= 10;
		i++;
	}
	printf("%u\n", i);
}

void ex18() {
	int n, isPrime = 1;
	printf("num: ");
	(void)scanf("%d", &n);

	for (int i = 2; i < sqrt((double)n); i++) {
		if (n % i == 0) {
			isPrime = 0; break;
		}
	}

	printf("%d is%sprime\n", n, isPrime ? " " : "n't ");
}

void ex19() {
	int option;
	do {
		printf(
			"1. Start\n"
			"2. Settings\n"
			"3. Help\n"
			"4. End\n"
			"> "
		);
		(void)scanf("%d", &option);
		printf("Selected ");
		switch (option) {
		case 1: printf("Start"); break;
		case 2: printf("Settings"); break;
		case 3: printf("Help"); break;
		case 4: printf("End"); break;
		default: printf("Undefined option"); break;
		}
		printf("\n");
	} while (!(option >= 1 && option <= 4));
}

void ex20() {
	float s = 0;
	for (unsigned char i = 0; s <= 10; i++, s += 0.1f) {
		printf("#%u iteration s = %g\n", i, s);
	}
}
