#include "recursion.h"

#include <iostream>
#include <string>
#include <vector>

void printVector( std::vector<char>& result )
{
	auto itStart = result.begin();
	auto itEnd = result.end();
	for (; itStart != itEnd; ++itStart)
	{
		std::cout << *itStart;
	}
	std::cout << std::endl;
}

//////////////////////////////////////////////////

void combination(
	const std::string& input, int pos, int len,
	std::vector<char>& result)
{
	if (0 == len)
	{
		auto itStart = result.begin();
		auto itEnd = result.end();
		for (; itStart != itEnd; ++itStart)
		{
			std::cout << *itStart;
		}
		std::cout << std::endl;
	}
	else if( pos < input.length() )
	{
		static long table = 0;
		if (table & (1 << input[pos]))
			return;

		result.push_back(input[pos]);
		combination(input, pos + 1, len - 1, result);

		table |= (1 << input[pos]);
		result.pop_back();
		combination(input, pos + 1, len, result);
		table ^= (1 << input[pos]);
	}
}

void testCombination()
{
	std::cout << "*** recursion: combination ***" << std::endl;
	int nLen = 0;
	do
	{
		std::cout << "Please input a string: ";
		std::string strInput;
		std::getline(std::cin, strInput);
		nLen = strInput.length();

		std::vector<char> result;
		for (int i = 0; i < nLen; ++i)
		{
			combination(strInput, 0, i + 1, result);
		}

	} while (0 < nLen);

	std::cout << "** end ***" << std::endl;
}

///////////////////////////////////////////////////////////////

void permute(std::string& input, int pos, int end)
{
	if (pos == end)
	{
		std::cout << input << std::endl;
	}
	else
	{
		static long table = 0;

		for (int i = pos; i <= end; ++i)
		{
			if (table & (1 << input[pos]))
				continue;

			table |= 1 << input[pos];
			std::swap(input[pos], input[i]);

			permute(input, pos + 1, end);

			std::swap(input[pos], input[i]);
			table ^= 1 << input[pos];
		}
	}
}

void testPermutation()
{
	std::cout << "*** recursion: permutation ***" << std::endl;
	int nLen = 0;
	do
	{
		std::cout << "Please input a string: ";
		std::string strInput;
		std::getline(std::cin, strInput);
		nLen = strInput.length();

		permute(strInput, 0, nLen-1);

	} while (0 < nLen);

	std::cout << "** end ***" << std::endl;
}