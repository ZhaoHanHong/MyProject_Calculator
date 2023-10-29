#include "arithmetic.h"
#include <stdio.h>
#include <cmath>

namespace math {
	//template <typename T>
	Expression::Expression(int op, Expression* ex1, Expression* ex2):op_(op), expression1_(ex1), expression2_(ex2) { }
	//template<typename T>
	//template<typename T>
	Expression::Expression(const char* s) {
		ReadIn(s);
	}
	Expression::Expression():op_(-1/*default*/), expression1_(nullptr), expression2_(nullptr) {}
	//template<typename T>
	Expression::Expression(int op, Expression* ex1) : op_(op), expression1_(ex1), expression2_(nullptr) { }
	//template<typename T>
	void Expression::ReadIn(const char* s)
	{
		// delete redundant kuohaos
		int check_kuohao = 0;
		int num_left = 0, num_right = 0;
		int s_length = 0;
		while (s[check_kuohao] == '(') {
			check_kuohao++;
		}num_left = check_kuohao;
		while (s[check_kuohao])check_kuohao++;
		s_length = check_kuohao;check_kuohao--;
		while (s[check_kuohao]==')') {
			check_kuohao--,num_right++;
		}
		int startpos = (-abs(num_left - num_right) + num_left + num_right) / 2;
		int endpos = s_length - startpos - 1;
		//initialize
		exp_str_ = s;
		int i = startpos;
		char* s1=new char[LIMIT]; int s1_count = 0;
		char* s2=new char[LIMIT]; int s2_count = 0;
		int* op_list = new int[OP_LIMIT]/*take down the position of operators*/; int ops_count = 0;
		for (int j = 0; j < OP_LIMIT; j++)op_list[j] = -1;
		int in_kuohaos = 0;
		//check operators
		while (i<=endpos) {
			//check whether in kuohaos
			if (s[i] == '(')in_kuohaos++;
			if (s[i] == ')')in_kuohaos--;
			//identify operators
			if (op_list[ADD]==-1 && s[i] == ADD_str&&!in_kuohaos) {op_list[ADD] = i;}
			if (op_list[MINUS]==-1 && s[i] == MINUS_str&&!in_kuohaos)op_list[MINUS] = i;
			if (op_list[TIMES]==-1 && s[i] == TIMES_str&&!in_kuohaos)op_list[TIMES] = i;
			if (op_list[DEVIDE]==-1 && s[i] == DEVIDE_str&&!in_kuohaos)op_list[DEVIDE] = i;
			i++;
		}i = startpos;
		//search for operators,using OPERATOR_SEQUENCE
		bool op_setted = 0; int check_i;
		for (check_i = 0; OPERATOR_SEQUENCE[check_i]; check_i++) {
			if (op_list[check_i] != -1) {
				op_ =check_i;//determin operator type
				op_setted = 1;
				break;
			}
		}
		if (op_setted) {
			int sep_pos = op_list[check_i];
			while (i<=endpos) {
				if (i<sep_pos) {//read in expression1
					if (s1_count >= LIMIT-1) {
						printf("ERROR:Too long expression for s1!\n");
						return;
					}
					s1[s1_count] = s[i]; s1_count++;
				}
				if (i>sep_pos) {//read in expression2
					if (s2_count >= LIMIT-1) {
						printf("ERROR:Too long expression for s2!\n");
						return;
					}
					s2[s2_count] = s[i]; s2_count++;
				}
				i++;
			}
			s1[s1_count] = '\0';//end the a string
			s2[s2_count] = '\0';
			//devide and conquer
			if (!expression1_)expression1_ = new Expression();
			if (!expression2_)expression2_ = new Expression();
			expression1_->ReadIn(s1);
			expression2_->ReadIn(s2);
		}
		Calculate();
	}
    //template <typename T>
    void Expression::Calculate()
    {
		switch (op_) {
		case -1: {//convert the string in expression1 into numbers
			//identify decimal points
			value_ = 0;
			int i = 0, decimal_pt = -1;
			while (exp_str_[i]) {
				if (exp_str_[i] == '.') {
					if (decimal_pt < 0) {
						decimal_pt = i;
					}
					else {
						printf("Error:too much decimal points for a number!The number is going to be rendered as 0.\n");
						return;
					}
				}
				i++;
			}
			int j = 0;
			if (decimal_pt > 0) {
				for (j = 0; j < decimal_pt; j++) {
					value_ += double((exp_str_[j] - '0') * pow(10, decimal_pt - j - 1));
				}
				for (j = decimal_pt + 1; j < i; j++) {
					value_ += double((exp_str_[j] - '0') * pow(10, decimal_pt - j));
				}
			}
			else {
				for (j = 0; j < i; j++) {
					value_ += double((exp_str_[j] - '0') * pow(10, i - j-1));
				}
			}
			break;
		}
		case ADD: {
			value_ = double(expression1_->GetValue() + expression2_->GetValue());
			break;
		}
		case MINUS: {
			value_ = double(expression1_->GetValue() - expression2_->GetValue());
			break;
		}
		case TIMES: {
			value_ = double(expression1_->GetValue() * expression2_->GetValue());
			break;
		}
		case DEVIDE: {
			value_ = double(double(expression1_->GetValue()) / double(expression2_->GetValue()));
			break;
		}
		}
	}
	//template <typename T>
	double Expression::GetValue()
	{
		return value_;
	}

	const char* Expression::GetString()
	{
		return exp_str_;
	}

	const int Expression::TranslateToInt(char c) {
		switch (c) {
		case ADD_str:return ADD;
		case MINUS_str:return MINUS;
		case TIMES_str:return TIMES;
		case DEVIDE_str:return DEVIDE;
		default: {
			printf("Translation Error, operator '%c' doesn't exist!\n",c);
			return -1;
		}

		}
	}


	//debug functions
	void Expression::ShowOff() {
		printf("My value is %f, and have operator %d\n",value_,op_);
		printf("Firstly show you expression 1\n");
		if (expression1_) {
			expression1_->ShowOff();
		}
		else {
			printf("Expression 1 is null!\n");
		}
		printf("Then show you expression 2\n");
		if (expression2_) {
			expression2_->ShowOff();
		}
		else {
			printf("Expression 2 is null!\n");
		}
		printf("My structrue is shown!\n");
		return;
	}
}