#include "arraysAndStrings.h"
#include <iostream>
#include <string>

void removeDuplicates()
{
	std::cout << "*** Arrays and Strings 03 ***" << std::endl;
	bool bContinue = true;
	std::string strInput;
	do
	{
		std::cout << "Please enter a string (exit to terminate):\t";
		std::getline(std::cin, strInput);

		if ("exit" == strInput)
		{
			bContinue = false;
		}
		else
		{
			if (strInput.length() > 1)
			{
				int nTail = 1;
				for (int i = 1; i < strInput.length(); ++i)
				{
					int j;
					for (j = 0; j < nTail; ++j)
					{
						if (strInput[j] == strInput[i])
							break;
					}
					if (j == nTail)
					{
						strInput[nTail] = strInput[i];
						++nTail;
					}
				}
				if (nTail < strInput.length())
					strInput.erase(nTail);
			}
		}
		std::cout << "result: " << strInput << std::endl;

	} while (bContinue);
}

void replaceSpaces()
{
	std::cout << "***  Arrays and Strings 05: replace all spaces ***" << std::endl;
	bool bContinue = true;
	std::string strInput;
	do
	{
		std::cout << "Please write a string: ";
		std::getline(std::cin, strInput);
		if ("exit" == strInput)
		{
			break;
		}

		int nSpaces = 0, nLen = strInput.length();
		const char* pBuf = strInput.c_str();
		for (int i = 0; i < nLen; ++i)
		{
			if (' ' == *(pBuf + i))
				++ nSpaces;
		}

		if (0 < nSpaces)
		{
			strInput.resize(nLen + 2*nSpaces);
			const char* pt = pBuf + nLen - 1;
			//const char* pt2 = pBuf + strInput.length() - 1;
			int nPos = strInput.length() - 1;
			for (int i = nLen - 1; i >= 0; --i)
			{
				if (' ' == *pt)
				{
					strInput[nPos--] = '0';
					strInput[nPos--] = '2';
					strInput[nPos--] = '%';
				}
				else
				{
					strInput[nPos--] = *pt;
				}
				-- pt;
			}
		}

		std::cout << strInput << std::endl;

	} while (bContinue);
}
