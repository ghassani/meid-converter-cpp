// MeidConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "MeidConverter.h"

using namespace std;

int main(int argc, char* argv[])
{
	int mInputType;

	if(argc < 2){
		cout << "Please Provide an ESN or MEID in Hex or Dec Format";
		return 0;
	}

	// start new instance of meid converter
	MeidConverter meidConverter;


	try{
		MeidConverter::MEID result = meidConverter.convert(argv[1]);

		switch(meidConverter.getInputType()){
			case 1:
				cout << "Converted From MEID DEC" << endl;
				break;
			case 2:
				cout << "Converted From MEID HEX" << endl;
				break;
			case 3:
				cout << "Converted From ESN DEC" << endl;
				break;
			case 4:
				cout << "Converted From ESN HEX" << endl;
				break;
		}
	
		std::cout << "MEID DEC Result: " << result.meidDec << std::endl;
		std::cout << "MEID HEX Result: " << result.meidHex << std::endl;
		std::cout << "pESN DEC Result: " << result.pEsnDec << std::endl;
		std::cout << "pESN HEX Result: " << result.pEsnHex << std::endl;

	}catch(std::string e){
		std::cout << e << std::endl;
		return 0;
	}

	
	return 0;
}