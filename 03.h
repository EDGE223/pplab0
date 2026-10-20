#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
	/*printf("the year %d is%syear\n", year % 4 == 0);*/
}
