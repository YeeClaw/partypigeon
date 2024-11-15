#include <stdio.h>
#include <string.h>

void main_loop() {
	char user_input[] = "none";
	while (strcmp("exit", user_input) != 0) {
		fgets(user_input, 5, stdin);
	}
}

int main() {
	return 0;
}

