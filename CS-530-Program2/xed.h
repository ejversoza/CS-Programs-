/**************************************************************************************************
Name: Emily Jean Versoza - cssc0422, 819442111
      Christina Tran - cssc0466, 819312540
      Leeza Dalisay- cssc0464 - 819514274
Project: Assignment #2
File: xed.h
Notes: header file for xed.cpp 
 **************************************************************************************************/
#ifndef xedDIS
#define xedDIS

#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "opcode.h" //include opcode 

using namespace std;

	class Disassembler {

		public:
			void readdisF(ifstream&,ifstream&,string,string);
			void header(string);
			void textR(string);
			void modR(string);
			void endR(string);
			int convertInt(string);
			int negative(string);
			string binConvert(int);
			int determineFormat();
			int format1();
			int format2();
			int format3(string);
			int format4(string);

		private:
			ofstream sicS;
			ofstream lisS;
			int baseAdd;
			string tempCurrL;
			string address;
			int intAdd;
			string opMnemonic;
			string opFormat;
			string opcode;
			string objLength;
			int lengthP;
			int iLength; 
			int endLine;
			int intOp;
			int objectStart;
			vector<string> symTab;
			vector<int> symAdd;
			vector<string> symN;
			vector<int> litL;
			vector<int> litAdd;
			vector<string> litS;
			
			
			
	};

#endif 
