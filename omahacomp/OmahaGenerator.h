#pragma once

class COmahaGenerator
{
	COmahaGenerator(void);
	~COmahaGenerator(void);

public:
	/*
	To design the algorithm and write a C++ program that will determine 
	which one of the two OMAHA Hi/Lo poker hands is the winning hand 
	for High and which one is the winning hand for Low (if any).
	*/
	static int commit(const std::wstring& strInput, std::wstring& strOutput);
};

