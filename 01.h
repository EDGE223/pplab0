#pragma once
#include <stdio.h>
#include <string.h>
#include <stddef.h>

void ex1() {
	static const char* text[] = {
		"XXXXXX    XX    XX",
		"XX        XX  XX  ",
		"XXXXXX    XXXX    ",
		"XX        XX  XX  ",
		"XXXXXX    XX    XX",
	};

	for (unsigned char i = 0; i < sizeof(text) / sizeof(text[0]); ++i) {
		printf("%s\n", text[i]);
	}
}

void ex2() {
	static const char* text[] = {
		"     *",
		"    ***",
		"***********",
		"   *****",
		"  **   **",
		" *       *",
	};
	for (unsigned char i = 0; i < sizeof(text) / sizeof(text[0]); ++i) {
		printf("%s\n", text[i]);
	}
}

void ex3() {
	const char* titles[] = { "nr", "imie", "nazwisko" };
	const char* data[][3] = {
		{ "1", "Jan", "Kowalski" },
		{ "2", "Anna", "Nowak" },
		{ "3", "Piotr", "Jankowski" },
	};

	size_t widths[] = { 0, 0, 0 };
	for (unsigned char i = 0; i < sizeof(titles) / sizeof(titles[0]); ++i) {
		if (widths[i] < strlen(titles[i])) {
			widths[i] = strlen(titles[i]);
		}
		for (unsigned char j = 0; j < sizeof(data) / sizeof(data[0]); ++j) {
			if (widths[i] < strlen(data[j][i])) {
				widths[i] = strlen(data[j][i]);
			}
		}
	}

	/* Titles */
	for (unsigned char i = 0; i < sizeof(titles) / sizeof(titles[0]); ++i) {
		printf("%-*s ", (int)widths[i], titles[i]);
	}

	/* Data */
	for (unsigned char j = 0; j < sizeof(data) / sizeof(data[0]); ++j) {
		printf("\n");
		for (unsigned char i = 0; i < sizeof(titles) / sizeof(titles[0]); ++i) {
			printf("%-*s ", (int)widths[i], data[j][i]);
		}
	}
}