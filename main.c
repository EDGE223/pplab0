#include <stdio.h>

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

int main(int argc, const char* argv[]) {
	printf("Praised be to the mashine!\n");

	ex2();
	return 0;
}