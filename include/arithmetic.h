#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
namespace math {
	//template <typename T>
	class Expression {
	private:
		const char* exp_str_;
		int op_;//operator
		Expression* expression1_;
		Expression* expression2_;
		double value_=0;
		void Calculate();
		static const int ADD = 0;
		static const int MINUS = 1;
		static const int TIMES = 2;
		static const int DEVIDE = 3;
		static const char ADD_str = '+';
		static const char MINUS_str = '-';
		static const char TIMES_str = '*';
		static const char DEVIDE_str = '/';
		static const int TranslateToInt(char c);
	public:
		Expression(int op, Expression* ex1, Expression* ex2);
		Expression(int op, Expression* ex1);
		Expression(const char* s);
		Expression();
		double GetValue();
		void ReadIn(const char *str);
		//debug
		void ShowOff();
		const char* GetString();
		static const int LIMIT = 100;
		static const int OP_LIMIT = 20;
		const char OPERATOR_SEQUENCE[OP_LIMIT] = "+-*/";
	};
}//namespace math
#endif//! __ARITHMETIC_H__