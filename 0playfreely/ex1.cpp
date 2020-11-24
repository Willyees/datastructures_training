#include <iostream>
#include <string>
#include <stack>

using namespace std;

namespace ex{
	/*
	find if a string of parenthesis is balanced*/
	bool str_parenthesis_is_balanced(std::string s1) {
		cout << s1 << endl;
		//std::string s2 = "({)}";
		//std::string s2 = "(){}";

		std::stack<char> stack_c;

		//push only the opening brackets and only pop the last added bracket. if at the end of stack there are brackets -> not balanced
		for (char c : s1) {
			if (c == '{' || c == '[' || c == '(')
				stack_c.push(c);
			else {
				if (stack_c.empty())
					return false;
				switch (c) {
				case '}':
					if (stack_c.top() == '{')
						stack_c.pop();
					else
						return false;
					break;
				case ')':
					if (stack_c.top() == '(')
						stack_c.pop();
					else
						return false;
					break;
				case ']':
					if (stack_c.top() == '[')
						stack_c.pop();
					else
						return false;
					break;
				default:
					break;
				}
			}
		}
		if (stack_c.empty()) {
			std::cout << "Balanced" << std::endl;
			return true;
		}
		else {
			std::cout << "Not balanced" << std::endl;
			return false;
		}
	}
}