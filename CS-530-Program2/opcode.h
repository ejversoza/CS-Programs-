/************************************************************************************************
me: Emily Jean Versoza - cssc0422, 819442111
      Christina Tran - cssc0466, 819312540
      Leeza Dalisay- cssc0464 - 819514274
Project: Assignment #2
File: opcode.
Notes: header file for opcode.cpp
**************************************************************************************************/


	#ifndef OPCODE
	#define OPCODE
	
	#include <iostream>
	#include <stdlib.h>
	#include <stdio.h>
	#include <iomanip>
	#include <fstream>
	#include <string.h>
	#include <string>
	#include <algorithm>
	
	
	using namespace std;

	class opCode {

		public: 
			string convertOp(int);
			string convertBin(int);
			string convertHex(string);
			string binSwitch(string);
			string searchFormat(string);
			string searchMnemonic(string); 

	};

	#endif 

