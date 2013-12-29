#include "stdafx.h"
#include "MeidConverter.h"

/**
* MeidConverter
*/
MeidConverter::MeidConverter(void){

}

/**
* MeidConverter
*/
MeidConverter::~MeidConverter(void){

}

/**
* convert
* @param char[] input
*/
MeidConverter::MEID MeidConverter::convert(char input[]){

	if(!this->isValid(input)){
		throw std::string("Invalid Input");
	}

	this->mInput = input;

	MEID output;
	output.meidDec = this->convertToMeidDec(input);
	output.meidHex = this->convertToMeidHex(input);

	if(this->getInputType() == MEID_DEC || this->getInputType() == MEID_HEX){
		output.pEsnHex = this->calculatePesn((char*)output.meidHex.c_str());
		output.pEsnDec = this->convertToEsnDec((char*)output.pEsnHex.c_str());
	} else {
		output.pEsnDec = this->convertToEsnDec(input);
		output.pEsnHex = this->convertToEsnHex(input);
	}
	return output;
}

/**
* convertToMeidHex
* @param char[] input
*/
std::string MeidConverter::convertToMeidHex(char input[]){
	if(this->getInputType() == MEID_HEX){
		return std::string(input);
	}
	return this->transformSerial(input, 10, 16, 10, 8, 6);
}

/**
* convertToMeidDec
* @param char[] input
*/
std::string MeidConverter::convertToMeidDec(char input[]){
	if(this->getInputType() == MEID_DEC){
		return std::string(input);
	}
	return this->transformSerial(input, 16, 10, 8, 10, 8);
}

/**
* convertToEsnHex
* @param char[] input
*/
std::string MeidConverter::convertToEsnHex(char input[]){
	if(this->getInputType() == ESN_HEX){
		return std::string(input);
	}
	return this->transformSerial(input, 10, 16, 3, 2, 6);
}

/**
* convertToEsnDec
* @param char[] input
*/
std::string MeidConverter::convertToEsnDec(char input[]){
	if(this->getInputType() == ESN_DEC){
		return std::string(input);
	}
	return this->transformSerial(input, 16, 10, 2, 3, 8);
}

/**
* calculatePesn
* @param char[] meidHex
*/
std::string MeidConverter::calculatePesn(char meidHex[]){
	if( this->getInputType() == ESN_DEC  || this->getInputType() == ESN_HEX ){ //ESN has no pESN
		return NULL;
    }

	unsigned char hash[20];
	char hexstring[41];
	unsigned int key = 0;
	char buff[7];

	for(unsigned int i = 0; i < strlen(meidHex); i+=2){
		buff[key] = strtol(std::string(meidHex).substr(i, 2).c_str(),NULL,16);
		key++;
	}

    sha1::calc(buff, sizeof(buff), hash);
	sha1::toHexString(hash, hexstring);
	
	std::string out = "80";
	out.append(std::string(hexstring).substr((strlen(hexstring) -6),(strlen(hexstring))));
	return out;    
}

/**
* isValid
* @param char[] input
*/
bool MeidConverter::isValid(char input[]){
	std::string s = input;

	std::regex meidDecTest ("[0-9]{18}");
	std::regex meidHexTest ("[a-fA-F0-9]{14}");
	std::regex esnDecTest ("[0-9]{11}");
	std::regex esnHexTest ("[a-fA-F0-9]{8}");

	if( std::regex_match (s,meidDecTest) ){
		this->setType(MEID_DEC);
		return true;
	}

	if( std::regex_match (s,meidHexTest) ){
		this->setType(MEID_HEX);
		return true;
	}

	if( std::regex_match (s,esnDecTest) ){
		this->setType(ESN_DEC);
		return true;
	}

	if( std::regex_match (input,esnHexTest) ){
		this->setType(ESN_HEX);
		return true;
	}

	return false;
}

/**
* transformSerial
* @param char[] input
* @param int srcBase
* @param int dstBase
* @param int p1Width
* @paran int p1Padding
* @param int p2Padding
*/
std::string MeidConverter::transformSerial(char input[], int srcBase, int dstBase, int p1Width, int p1Padding, int p2Padding){
	std::string inputAsString = input;
	bool toHex = srcBase == 10 && dstBase == 16;

	std::string part1_s = inputAsString.substr(0,p1Width);
	std::string part2_s = inputAsString.substr(p1Width);
		
	unsigned long part1_l = strtoul(part1_s.c_str(),NULL,srcBase);
	unsigned long part2_l = strtoul(part2_s.c_str(),NULL,srcBase);
	
	char outputBuffer[50];
	if(toHex)
		sprintf(outputBuffer, "%lX%lX", part1_l, part2_l );
	else
		sprintf(outputBuffer, "%lu%lu", part1_l, part2_l );

	return std::string(outputBuffer);
}


/**
* getInputType
*/
int MeidConverter::getInputType(){
	return this->mInputType;
}

/**
* setType
* @param int type
*/
void MeidConverter::setType(int type){
	this->mInputType = type;
}