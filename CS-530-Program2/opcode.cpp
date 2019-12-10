/***************************************************************************************************
me: Emily Jean Versoza - cssc0422, 819442111
      Christina Tran - cssc0466, 819312540
      Leeza Dalisay- cssc0464 - 819514274
Project: Assignment #2
File: opcode.cpp
Notes: Uses opcode table to find formats and mnemomics  
 **************************************************************************************************/
#include "opcode.h"

using namespace std;
	
	

	struct opcode {
		string mnemonic;
		string format;
		string opcode;
	};

	const struct opcode opCode_Table [] = { 
		{"ADD","3/4", "18"},
		{"ADDF","3/4","58"},
		{"ADDR","2","90"},
		{"AND", "3/4","40"},
		{"CLEAR","2","84"},
		{"COMP","3/4","28"},
		{"COMPF","3/4","88"},
		{"COMPR","2","A0"},
		{"DIV","3/4","24"},
		{"DIVF","3/4","64"},
		{"DIVR","2","9C"},
		{"FIX","1","C4"},
		{"FLOAT","1","C0"},
		{"HIO","1","F4"},
		{"J","3/4","3C"},
		{"JEQ","3/4","30"},
		{"JGT","3/4","34"},
		{"JLT","3/4","38"},
		{"JSUB","3/4","48"},
		{"LDA","3/4","00"},
		{"LDB","3/4","68"},
		{"LDCH","3/4","50"},
		{"LDF","3/4","70"},
		{"LDL","3/4","08"},
		{"LDS","3/4","6C"},
		{"LDT","3/4","74"},
		{"LDX","3/4","04"},
		{"LPS","3/4","D0"},
		{"MUL","3/4","20"},
		{"MULF","3/4","60"},
		{"MULR","2","98"},
		{"NORM","1","C8"},
		{"OR","3/4","44"},
		{"RD","3/4","08"},
		{"RMO","2","AC"},
		{"RSUB","3/4","4C"},
		{"SHIFTL","2","A4"},
		{"SHIFTR","2","A8"},
		{"SIO","1","F0"},
		{"SSK","3/4","EC"},
		{"STA","3/4","0C"},
		{"STB","3/4","78"},
		{"STCH","3/4","54"},
		{"STF","3/4","80"},
		{"STI","3/4","D4"},
		{"STL","3/4","14"},
		{"STS","3/4","7C"},
		{"STSW","3/4","E8"},
		{"STT","3/4","84"},
		{"STX","3/4","10"},
		{"SUB","3/4","1C"},
		{"SUBF","3/4","94"},
		{"SVC","2","B0"},
		{"TD","3/4","E0"},
		{"TIO","1","F8"},
		{"TIX","3/4","2C"},
		{"TIXR","2","B8"},
		{"WD","3/4","DC"}
	};

string opCode::convertOp(int intOP) {

	string opString;
	opString = convertBin(intOP);//converts to binary 
	opString = convertHex(opString); // then converts to hex
	if(opString.length() < 2) {
		opString.insert(opString.begin(), '0'); //add zero if length is 1
	}
	return opString;

}
string opCode::searchFormat(string opCode) {
	
	string form = "";
	int index;
	int i;
	
	for(i = 0; i < 58; i++) {
		if(opCode_Table[i].opcode.compare(opCode) == 0) { //searches for index of opcode
			index = i;

		}
	}

	form = opCode_Table[index].format; //uses index to get format
	return form; 
	
}
string opCode::searchMnemonic(string opCode) {
	
	string mnemonic = "";
	int index;
	int i;

	for(i = 0; i < 58; i++) {
		if(opCode_Table[i].opcode.compare(opCode) == 0) { //searches for index of opcode
			index = i;
		}
	}
	mnemonic = opCode_Table[index].mnemonic; //uses index to find mnemonic 
	return mnemonic;
}

string opCode::convertBin(int intOP) { //int to binary 

	int i,k;
	string binaryOP; 
	
	for(i = 7; i >= 0; i--) {

		k = intOP >> i;

		if(k & 1) {
			binaryOP.insert(binaryOP.begin(), '1');
		}
		else {
			binaryOP.insert(binaryOP.begin(), '0');
		}
	}
	reverse(binaryOP.begin(), binaryOP.end());
	binaryOP.replace(binaryOP.length() - 2, 2, "00"); //changes last two bits
	return binaryOP;

}

string opCode::convertHex(string opString){
	
	
	string hex;

	string firstH = opString.substr(0,4);
	firstH = binSwitch(firstH); //converts first half to hex
	string secondH = opString.substr(4,4); //converts second half to hex
	secondH = binSwitch(secondH);
	
	hex = firstH + secondH; //puts it together to get the whole opcode

	return hex;
}
string opCode::binSwitch(string bin) { //binary to hex 
	
	
		if(bin.compare("0000") == 0){
			bin = "0";
		}
			
		else if(bin.compare("0001") == 0) {
			bin = "1";
		}
			
		else if(bin.compare("0010") ==0) {
			bin = "2";
		}
		else if(bin.compare("0011") == 0) {
			bin = "3";
		}
		else if(bin.compare("0100") == 0) {
			bin = "4";
		}	
		else if(bin.compare("0101") == 0) {
			bin = "5";
		}
		else if(bin.compare("0110") == 0) {
			bin = "6";
		}
		else if(bin.compare("0111") == 0) {
			bin = "7";
		}
		else if(bin.compare("1000") == 0) {
			bin = "8";
		}
		else if(bin.compare("1001") == 0) {
			bin = "9";
		}
		else if(bin.compare("1010") == 0) {
			bin = "A";
		}
			
		else if(bin.compare("1011") == 0) {
			bin = "B";
		}
		
		else if(bin.compare("1100") == 0) {
			bin = "C";
		}
		else if(bin.compare("1101") == 0) {
			bin = "D";
		}
		else if(bin.compare("1110") == 0) {
			bin = "E";
		}
		else {
			bin = "F";
		}
		
				
	
	return bin;
	
		

	
}
