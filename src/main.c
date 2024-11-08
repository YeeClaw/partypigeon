#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// I want to find a way to essentially return a string!
char* greeting(char* userName) {
	char suffix[] = "Hello, ";
	char* finalOut = (char*)malloc(strlen(suffix) + strlen(userName) + 1);
	
	strcpy(finalOut, suffix);
	strcat(finalOut, userName);
	return finalOut;
}

int main() {
	char* introduction = greeting("Austin");
	printf("%s\n", introduction);
	free(introduction);

	return 0;
}

