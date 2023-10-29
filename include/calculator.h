#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__
#include "arithmetic.h"
namespace calculator {
	class Calculation {
	private:
		const char* calculate_str_;
		double value_;
		math::Expression *expression_;
		bool IsLegal(char c);
	public:
		Calculation();
		Calculation(const char* inputstring);
		void Show();
		bool ReadInString(const char* s);
	};

}

#endif // !__CALCULATOR_H__
