#include "calc.h"
#include <exception>
#include <cmath>

std::map<char, int> operation_priority {
	{'(', 0},
	{')', 0},
	{'+', 1},
	{'-', 1},
	{'*', 2},
	{'/', 2},
	{'^', 3}
};

std::string reverse_pol_exp(std::string exp)
{
	std::string res, num;
	std::stack<char> operations;
	exp.erase( std::remove( exp.begin(), exp.end(), ' ' ), exp.end() );
	for (int i = 0; i < exp.length(); ++i)
	{
		if (exp[i] >= '0' && exp[i] <= '9' || exp[i] == '.')
		{
			num += exp[i];
		}
		else 
		{
			if (!num.empty())
			{
				res += num + ' ';
				num.clear();
			}
			switch (exp[i])
			{
				case '*':
				case '/':
				case '+':
				case '^':
					if (!operations.empty() && operation_priority[exp[i]] <= operation_priority[operations.top()] )
					{
						res += operations.top();
						res += ' ';
						operations.pop();
					}
					operations.push(exp[i]);
					break;
				case '-':
					if ((i == 0 || exp[i-1] == '(') && (exp[i + 1] >= '0' && exp[i + 1] <= '9'))
					{
						num += '~';
					}
					else
					{
						if (!operations.empty() && operation_priority['-'] <= operation_priority[operations.top()] )
						{
							res += operations.top();
							res += ' ';
							operations.pop();
						}
						operations.push('-');
					}
					break;
				case '(':
					operations.push('(');
					break;
				case ')':
					while (operations.top() != '(')
					{
						res += operations.top();
						operations.pop();
						res += ' ';
					}
					operations.pop();
					break;
				default:
					std::cout << "Error" << std::endl;
					break;
			}
		}
	}
	if (!num.empty())
	{
		res += num + ' ';
	}
	while (!operations.empty())
	{
		res += operations.top();
		res += ' ';
		operations.pop();
	}

	std::cout << res << std::endl;
	return res;
}

double calc (std::string exp)
{
	exp = reverse_pol_exp(exp);
	std::string num;
	double tmp = 0, first = 0, second = 0, res = 0;
	std::stack<double> data;
	for (int i = 0; i <= exp.length(); ++i)
	{
		if (exp[i] == '~')
			num += '-';
		else if (exp[i] >= '0' && exp[i] <= '9' || exp[i] == '.')
		{
			num += exp[i];
		}
		else
		{
			if (!num.empty())
			{
				tmp = atof(num.c_str());
				num.clear();
				
				data.push(tmp);
			}
			if (exp[i] == ' ')
				continue;

			if (data.size() >= 2)
			{
				second = data.top();
				data.pop();
				first = data.top();
				data.pop();
			
				switch (exp[i])
				{
					case '*':
						res = first * second;
						break;
					case '/':
						if (second == 0)
							throw std::invalid_argument("division by zero");
						res = first / second;
						break;
					case '+':
						res = first + second;
						break;
					case '^':
						res = pow(first, second);
						break;
					case '-':
						res = first - second;
						break;
					default:
						std::cout << "Operation error" << std::endl;
						break;
				}

				data.push(res);
			}
		}


	}
	return data.top();
}


