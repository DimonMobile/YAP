#include "pch.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <iterator>


namespace Converter
{
	namespace Constants
	{
		const int debugTabSize = 20;
	}

	bool isOperation(char ch)
	{ 
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
			return true;
		return false;
	}

	bool isBrace(char ch)
	{
		if (ch == '(' || ch == ')')
			return true;
		return false;
	}
	
	namespace Polish
	{

		int priority(char ch)
		{
			if (ch == '(' || ch == ')')
				return 0;
			if (ch == '+' || ch == '-')
				return 1;
			if (ch == '*' || ch == '/')
				return 2;
			return 3;
		}

		std::string convert(const std::string &src)
		{
			std::string result;
			std::vector<char> stack;

			std::string mysrc = src;

			for (char ch : src)
			{
#ifdef _DEBUG
				std::string stackString;
				for(std::vector<char>::const_reverse_iterator it = stack.crbegin(); it != stack.crend(); ++it)
					stackString += *it;
				std::cout << std::setw(Constants::debugTabSize) << mysrc << std::setw(Constants::debugTabSize) << result << std::setw(Constants::debugTabSize) << stackString << std::endl;
				mysrc.erase(mysrc.begin());
#endif
				if (isalpha(ch))
				{
					result += ch;
				}
				else if (isOperation(ch))
				{
					if (stack.empty() || stack.back() == '(')
					{
						stack.push_back(ch);
					}
					else if (!stack.empty() && isOperation(stack.back()))
					{
						for (std::vector<char>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
						{
							if ( ( isOperation(*i) || isBrace(*i) ) && priority(ch) <= priority(*i))
							{
								result += *i;
								i = std::vector<char>::reverse_iterator(stack.erase(i.base() - 1));
							}
							else
							{
								break;
							}
						}
						stack.push_back(ch);
					}
				}
				else if (ch == '(')
				{
					stack.push_back(ch);
				}
				else if (ch == ')')
				{
					for (std::vector<char>::reverse_iterator i = stack.rbegin(); i != stack.rend();)
					{
						if (*i != '(')
						{
							result += *i;
							i = std::vector<char>::reverse_iterator(stack.erase(i.base() - 1));
						}
						else
						{
							stack.erase(i.base() - 1);
							break;
						}
					}
				}
			}
			for (std::vector<char>::const_reverse_iterator i = stack.crbegin(); i != stack.crend(); ++i)
			{
#ifdef _DEBUG
				std::string stackString;
				for (std::vector<char>::const_reverse_iterator it = stack.crbegin(); it != stack.crend(); ++it)
					stackString += *it;
				std::cout << std::setw(Constants::debugTabSize * 2) << result << std::setw(Constants::debugTabSize) << stackString << std::endl;
#endif
				result += *i;
			}
#ifdef _DEBUG
			std::cout << std::setw(Constants::debugTabSize * 2) << result << std::endl;
#endif
			return result;
		}

	} // namespace Polish
} // namespace Converter

int main()
{
	const std::string sources[] = { "(a+b)/(j-g))*(c+d)-e", "(a+b)*(c+d)-e" };
	int srcNumber = sizeof(sources) / sizeof(decltype(*sources));
	for (int i = 0; i < srcNumber; ++i)
	{
		std::cout << std::setfill('=') << std::setw(100) << '\n' << std::setfill(' ');
		std::cout << "***\tSource:\t" << sources[i] << std::endl;
		std::cout << "***\tResult:\t" << Converter::Polish::convert(sources[i]) << std::endl;
	}
}
