#pragma once
#include <regex>
#include <iostream>
#include "sha1.h"

class MeidConverter
{

enum {
	MEID_DEC = 1,
	MEID_HEX = 2,
	ESN_DEC	 = 3,
	ESN_HEX	 = 4
} INPUT_TYPES;

public:
	MeidConverter(void);
	~MeidConverter(void);

	int getInputType();

	struct MEID{
		std::string meidDec;
		std::string meidHex;
		std::string pEsnDec;
		std::string pEsnHex;
	};

	bool isValid(char input[]);
	MEID convert(char input[]);
	std::string convertToMeidHex(char input[]);
	std::string convertToMeidDec(char input[]);
	std::string convertToEsnHex(char input[]);
	std::string convertToEsnDec(char input[]);
	std::string calculatePesn(char input[]);

private:
	int mInputType;
	char *mInput;
	MEID result;
	void setType(int type);
	std::string transformSerial(char* input, int srcBase, int dstBase, int p1Width, int p1Padding, int p2Padding);
};