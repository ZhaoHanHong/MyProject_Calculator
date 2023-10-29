#include "arithmetic.h"
#include "calculator.h"
#include <stdio.h>
int main() {
	calculator::Calculation newcalculation;
	printf("Type the calculation below:\n");
	char c=getchar();
	char* s = new char[100]; int i = 0;
	while (c == '\0' || c == '\n') {
		c = getchar();
	}
	while (!(c == '\0' || c == '\n')) {
		s[i] = c;
		c = getchar(), i++;
	}
	s[i] = '\0';
	newcalculation.ReadInString(s);
	newcalculation.Show();
	return 0;
}