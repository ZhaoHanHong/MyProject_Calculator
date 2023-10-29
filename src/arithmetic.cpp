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
		// DON'T simply delete redundant kuohaos----------->			   You know what?
		int check_kuohao = 0;//												There are significant testcases that make me realize my problem:
		int num_left = 0, num_right = 0;//									It is (-1)/(-2) and (-1/2). If we don't delete the kuohao, then the second one would get in 
		int s_length = 0;//													 a dead loop; but if we do, then the first would be -1)/(-2.
		while (s[s_length++]);
		s_length--;
		//initialize
		exp_str_ = s;
		int i = 0;
		char* s1=new char[LIMIT]; int s1_count = 0;
		char* s2=new char[LIMIT]; int s2_count = 0;
		int* op_list = new int[OP_LIMIT]/*take down the position of operators*/;
		for (int j = 0; j < OP_LIMIT; j++)op_list[j] = -1;
		int in_kuohaos = 0; bool have_ops = 0;
		//check operators
		while (i<s_length) {
			//check whether in kuohaos
			if (s[i] == '(')in_kuohaos++;
			if (s[i] == ')')in_kuohaos--;
			//identify operators
			if (s[i] == ADD_str || s[i] == MINUS_str || s[i] == TIMES_str || s[i] == DEVIDE_str)have_ops = 1;
			if ( s[i] == ADD_str&&!in_kuohaos) {op_list[ADD] = i;}
			if ( s[i] == MINUS_str&&!in_kuohaos)op_list[MINUS] = i;//Especially for minus signs: when things like 1-2-3 appears, commensense is (1-2)-3.
			if ( s[i] == TIMES_str&&!in_kuohaos)op_list[TIMES] = i;//Thus, we must use the last position for the same kind of operators.
			if ( s[i] == DEVIDE_str&&!in_kuohaos)op_list[DEVIDE] = i;
			i++;
		}i = 0;
		//search for operators,using OPERATOR_SEQUENCE
		bool op_setted = 0; int check_i;
		for (check_i = 0; OPERATOR_SEQUENCE[check_i]; check_i++) {
			if (op_list[check_i] != -1) {
				op_ =check_i;//determin operator type
				op_setted = 1;
				break;
			}
		}
		int offset = 0;
		if ((!op_setted) && have_ops) {//must covered by kuohaos, such as (1-2) or ((-1)/(-2)).
			while (!op_setted&&(offset+offset<s_length)) {//loop until all the extra kuohaos are deleted
				offset++;
				for (int j = 0; j < OP_LIMIT; j++)op_list[j] = -1; in_kuohaos = 0;//reset
				for (i = offset; i < s_length - offset; i++) {
					//check whether in kuohaos
					if (s[i] == '(')in_kuohaos++;
					if (s[i] == ')')in_kuohaos--;
					//identify operators
					if (s[i] == ADD_str && !in_kuohaos) { op_list[ADD] = i; }
					if (s[i] == MINUS_str && !in_kuohaos)op_list[MINUS] = i;//Especially for minus signs: when things like 1-2-3 appears, commensense is (1-2)-3.
					if (s[i] == TIMES_str && !in_kuohaos)op_list[TIMES] = i;//Thus, we must use the last position for the same kind of operators.
					if (s[i] == DEVIDE_str && !in_kuohaos)op_list[DEVIDE] = i;
					for (check_i = 0; OPERATOR_SEQUENCE[check_i]; check_i++) {//check operator type again!
						if (op_list[check_i] != -1) {
							op_ = check_i;//determin operator type
							op_setted = 1;
							break;
						}
					}
				}
			}
			if (!op_setted) {
				printf("The expression %s must have something I haven't condidered!\n", exp_str_);
			}
		}
		//read in
		if (op_setted) {
			int sep_pos = op_list[check_i];
			i = offset;
			while (i<s_length-offset) {
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
	void Expression::ShowOff(int tabs) {
		for (int i = 0; i < tabs; i++)printf("  ");
		if (op_==-1) {
			printf("This expression is a value %.2f, reading from string %s\n", value_,exp_str_);
		}
		else {
			printf("This expression is %f=(%.2f)%c(%.2f), reading from string %s\n", value_, expression1_->value_, OPERATOR_SEQUENCE[op_], expression2_->value_, exp_str_);
			for (int i = 0; i < tabs; i++)printf("  ");
			printf("Firstly show you expression 1:\n");
			expression1_->ShowOff(tabs + 1);
			for (int i = 0; i < tabs; i++)printf("  ");
			printf("Then show you expression 2:\n");
			expression2_->ShowOff(tabs + 1);
		}
		for (int i = 0; i < tabs; i++)printf("  ");
		printf("That's all!\n");
		return;
	}
}