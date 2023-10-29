#include "calculator.h"
#include <stdio.h>
namespace calculator {
	bool Calculation::IsLegal(char c)
	{
		bool b1 = ('0' <= c) && (c <= '9');
		bool b2 = 0;
		for (int i = 0; expression_->OPERATOR_SEQUENCE[i]; i++) {
			if (expression_->OPERATOR_SEQUENCE[i] == c) {
				b2 = 1; break;
			}
		}
		return (b1||b2);
	}
	Calculation::Calculation() :value_(0){
		expression_ = new math::Expression();
	}
	Calculation::Calculation(const char* inputstring):value_(0),calculate_str_(inputstring){
		expression_ = new math::Expression(inputstring);
	}
	void Calculation::Show()
	{
		printf("%s=%f\n", expression_->GetString(), expression_->GetValue());
	}

	void Calculation::ReadInString(const char* s)
	{
		//first clean up the string for expression
		char* tmp = new char[expression_->LIMIT];
		int i = 0,j=0;
		while (!IsLegal(s[i]))i++;
		while (IsLegal(s[i])) {
			tmp[j] = s[i];
			j++, i++;
		}
		tmp[j] = '\0';
		expression_->ReadIn(tmp);
	}

}