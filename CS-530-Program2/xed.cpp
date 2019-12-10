/*******************************************************************************************************
Name: Emily Jean Versoza - cssc0422, 819442111
      Christina Tran - cssc0466, 819312540
      Leeza Dalisay- cssc0464 - 819514274
Project: Assignment #2
File: xed.cpp
Notes: This will take info from symbol file and object file to dissasemble it 
 **************************************************************************************************/
#include "xed.h" //header file 
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void Disassembler::readdisF(ifstream& objF, ifstream& symF,string sic,string lis){

	string currSym;
	string currL;
	int i;
	int x;
	int j;
		
	while(getline (symF,currSym)) { //takes information form symbol file puts it into a vector 
		
		symTab.push_back(currSym);
	}
	
	for(i = 2; i < symTab.size(); i++) { 
	
		if(symTab[i][0] != ' ') {	
			symAdd.push_back(convertInt(symTab[i].substr(8,6))); //seperates address
			symN.push_back(symTab[i].substr(0,6)); //seperates symbol names 

		}
		else {
			i = i + 3; //move forward 3 when done
			break;
		}
	
	}

	for(j = i; j < symTab.size(); j++) { //literals 
		
		
		litL.push_back(convertInt(symTab[j].substr(19,1))); //grabs the literal length
		litS.push_back(symTab[j].substr(8,6));		//grabs literal symbols
		litAdd.push_back(convertInt(symTab[j].substr(24,6))); //grabs literal addresses
		
	}
	
	symF.close(); //closes symbol file

	sicS.open(sic.c_str()); //opens sic file 
	lisS.open(lis.c_str()); //opens lis file 
	
	
	//checks what record it is 
	while(getline(objF,currL)) {
			
		if(currL[0] == 'H') { 
			header(currL); 
		}
		if(currL[0] == 'T') {
			textR(currL);
		}
		if(currL[0] == 'M') {
			modR(currL);
		}
		if(currL[0] == 'E') {
			endR(currL);

		}
	}
	
	objF.close(); //closes object file
	sicS.close(); //closes sic file
	lisS.close(); //closes lis file 

}
void Disassembler::header(string currL) {
	
	
	string title = currL.substr(1,6); //grabs title of program
	string startA = currL.substr(7,6); //starting address
	string length = currL.substr(13,6); //length of whole program
	lengthP = convertInt(length); //converts it into an int
	
	

	if(startA.compare("000000") == 0) { 
		string lisA = startA.substr(2,4); //address
		startA = "0"; //condenses it to one zero 
		lisS<<setw(6)<<left<<lisA;
		sicS<<setw(6)<<title<<setw(3)<<" "<<"START"<<setw(3)<<" "<<startA<<endl;
		lisS<<setw(6)<<left<<title<<setw(4)<<"START"<<setw(3)<<" "<<startA<<endl;
		//prints out header 
	}
	else {	
		startA = startA.substr(2,4);
		lisS<<setw(6)<<left<<startA;
		sicS<<setw(6)<<title<<setw(3)<<" "<<"START"<<setw(3)<<" "<<startA<<endl;
		lisS<<setw(6)<<title<<setw(3)<<"START"<<setw(3)<<" "<<startA<<endl;
		//prints out header
	}	
}
void Disassembler::textR(string currL) {

	address = currL.substr(1,6);//grabs starting address
	intAdd = convertInt(address); //converts it into an int
	

	objLength = currL.substr(7,2); //grabs length of text 
	iLength = convertInt(objLength); //converts it into int 

	endLine = intAdd + iLength; //find the end of the text record
	
	objectStart = 9; //object code starts at pos 9
	int jump; //moves forward to the next object code
	int i;

	while(intAdd < endLine) {

		tempCurrL = currL;
		string convertOp = currL.substr(objectStart, 2); //graps the opcode
		intOp = convertInt(convertOp); //converts into int
		jump = determineFormat(); //determint the format 
		objectStart = objectStart + jump; //move forward depending on jump
		intAdd = intAdd + (jump/2); //add to address
		
				
	}
	for(i = 0; i < symAdd.size(); i++) {
		if(intAdd <= symAdd[i]) {
			if((intAdd % 3) == 0) { //if divisible by 3 then its RESW
				lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
				sicS<<setw(7)<<left<<symN[i]<<"    "<<"RESW   ";
				lisS<<setw(7)<<left<<symN[i]<<"    "<<"RESW   ";
			}
			else {	//else RESB
				lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<" ";
				sicS<<setw(7)<<left<<symN[i]<<"    "<<"RESB   ";
				lisS<<setw(7)<<left<<symN[i]<<"    "<<"RESB   ";
					
			}

			if(i < symAdd.size()-1) { //prints out memory allocated
					sicS<<setw(7)<<left<<((symAdd[i+1]-symAdd[i])/3)<<endl;
					lisS<<setw(7)<<left<<dec<<((symAdd[i+1]-symAdd[i])/3)<<endl;
					intAdd = intAdd + (symAdd[i+1] - symAdd[i]);
			}
			else {
				sicS<<setw(8)<<left<<((lengthP - symAdd[i])/3)<<endl;
				lisS<<setw(8)<<left<<dec<<((lengthP - symAdd[i])/3)<<endl;
				intAdd = intAdd + (lengthP - symAdd[i]);
			}
			
			
		}
	}
						

}
void Disassembler::modR(string currL) { //mod record
	string sAdd = currL.substr(1,6); //starting address
	int iAdd = convertInt(sAdd);
	string mlength = currL.substr(7,2); //length 
	int imlength = convertInt(mlength);
	

}
void Disassembler::endR(string currL) { //prints out end record
	string sAdd = currL.substr(1,6); //address to go back to 
	int iAdd = convertInt(sAdd);
	int i;
	for(i = 0; i < symAdd.size(); i++) {
		if(iAdd == symAdd[i]) {
			sicS<<"           "<<setw(7)<<left<<"END"<<symN[i]<<endl;
			lisS<<"                 "<<setw(7)<<left<<"END"<<symN[i]<<endl;
		}
	}
}

int Disassembler::determineFormat() {

	int moveS;
	
	
	lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  "; //prints out addresses
	opCode *search = new opCode();
	opcode = search->convertOp(intOp); //gets opcode
	opFormat = search->searchFormat(opcode); //uses opcode to find format 

	if(opFormat.length() < 2) { //either format 1 or 2
		if(opFormat == "1") {
			moveS = format1();
			return moveS;

		}
		else {
			moveS = format2();
			return moveS;
		}
	}
	else { //either format 3 or 4
		
		string flagsNI = tempCurrL.substr(objectStart + 1, 1);
		int iFlagsNI = convertInt(flagsNI);
		flagsNI = binConvert(iFlagsNI);
		reverse(flagsNI.begin(), flagsNI.end());
		

		string flagsXBPE = tempCurrL.substr(objectStart + 2, 1);
		int iFlagsXBPE = convertInt(flagsXBPE);
		flagsXBPE = binConvert(iFlagsXBPE);
		reverse(flagsXBPE.begin(), flagsXBPE.end());

		string flags = flagsNI + flagsXBPE;
		flags = flags.substr(2,6); //flags needed for format 3 and 4
		
		if(flags[5] == '1') { //format 4 if flag e is 1
			moveS = format4(flags);
			return moveS;
		}
		else {
			moveS = format3(flags);
			return moveS;
		}
	}


}

int Disassembler::format1() {

	opCode *search = new opCode();
	opMnemonic = search->searchMnemonic(opcode); //grabs the mnemonic 
	int i;
	string objectcode = tempCurrL.substr(objectStart, 2);

	for(i = 0; i < symAdd.size()-1; i++) {
		if(intAdd == symAdd[i]) { //checks for symbols
			sicS<<setw(11)<<left<<symN[i];
			lisS<<setw(11)<<left<<symN[i];
			break;
		}
		else {
			if(i >= symAdd.size()-2) {
				sicS<<"           ";
				lisS<<"           ";
			}
		}
	}
	for(i = 0; i < litAdd.size(); i++) {
		if(intAdd == litAdd[i]) { //checks for literals
			sicS<<setw(7)<<opMnemonic<<setw(10)<<left<<litS[i]<<endl;
			lisS<<setw(7)<<opMnemonic<<setw(10)<<left<<litS[i];
			lisS<<"      "<<objectcode<<endl; //prints out object code
			sicS<<"           "<<setw(10)<<"LTORG"<<endl;
			lisS<<"           "<<setw(10)<<"LTORG"<<endl;
			intAdd = intAdd + 1;
			objectStart = objectStart + 2;
			return 2;

		}
	}	
	sicS<<setw(7)<<left<<opMnemonic<<endl;
	lisS<<setw(7)<<left<<opMnemonic;
	lisS<<"      "<<objectcode<<endl;
	return 2;

}
int Disassembler::format2() {
	
	opCode *search = new opCode();

	opMnemonic = search->searchMnemonic(opcode); //grabs mnemonic 
	int register1 = convertInt(tempCurrL.substr(objectStart + 2, 1)); //gets register 1
	int register2 = convertInt(tempCurrL.substr(objectStart + 3, 1)); //gets register 2
	string output;
	string objectcode = tempCurrL.substr(objectStart, 4);

	int i;
	for(i = 0; i < symAdd.size()-1; i++) {
		if(intAdd == symAdd[i]) { //checks for symbols
			sicS<<setw(11)<<left<<symN[i];
			lisS<<setw(11)<<left<<symN[i];
			break;
		}
		else { 
			if(i >= symAdd.size()-2) {
				sicS<<"           ";
				lisS<<"           ";
			}
		}
	}
	for(i = 0; i < litAdd.size(); i++) {
		if(intAdd == litAdd[i]) { //checks for literal 
			sicS<<setw(6)<<opMnemonic<<setw(10)<<left<<litS[i]<<endl;
			lisS<<setw(6)<<opMnemonic<<setw(10)<<left<<litS[i];
			lisS<<"      "<<objectcode<<endl;
			sicS<<"           "<<setw(10)<<left<<"LTORG"<<endl;
			lisS<<"           "<<setw(10)<<left<<"LTORG"<<endl;
			intAdd = intAdd + 1;
			objectStart = objectStart + 2;
			return 4;
		}
	}
	if(register1 == 0) {
		output = "A,"; //determines which register for register 1
	}
	else if(register1 == 1) {
		output = "X,";
	}
	else if(register1 == 2) {
		output = "L,";
	}
	else if(register1 == 3) {
		output = "B,";
	}
	else if(register1 == 4) {
		output = "S,";
	}
	else if(register1 == 5) {
		output = "T,";
	}
	else {
		output = "F,";
	}
	
	if(register2 == 0) { //determines which register for register 2
		output = output + "A";
	}
	else if(register2 == 1) {
		output = output + "X";
	}
	else if(register2 == 2) {
		output = output + "L";
	}
	else if(register2 == 3) {
		output = output + "B";
	}
	else if(register2 == 4) {
		output = output + "S";
	}
	else if(register2 == 5) {
		output = output + "T";
	}
	else {
		output = output + "F";
	}
	sicS<<setw(7)<<left<<opMnemonic<<output<<endl; //output
	lisS<<setw(7)<<left<<opMnemonic<<output;
	lisS<<"      "<<objectcode<<endl;

	return 4;
}

int Disassembler::format3(string flags) {

	opCode *search = new opCode();

	opMnemonic = search->searchMnemonic(opcode); //grabs mnemonic 
	

	int i;
	for(i = 0; i < symAdd.size()-1; i++) { //checks for symbols
		if(intAdd == symAdd[i]) {
			sicS<<setw(11)<<left<<symN[i];
			lisS<<setw(11)<<left<<symN[i];
			break;
			
		}
		else {
			if(i >= symAdd.size()-2) {
				sicS<<"           ";
				lisS<<"           ";
			}
		
		}
	}
	
	for(i = 0; i < litAdd.size(); i++) { //check for literals
		if(intAdd == litAdd[i]) {
			intAdd = intAdd + 1;
			objectStart = objectStart + 2;
			sicS<<setw(6)<<left<<opMnemonic<<setw(10)<<left<<litS[i]<<endl;
			lisS<<setw(6)<<left<<opMnemonic<<setw(7)<<left<<litS[i];
			lisS<<"      "<<tempCurrL.substr(objectStart, 6)<<endl;
			lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
			sicS<<"           "<<setw(10)<<left<<"LTORG"<<endl;
			lisS<<"           "<<setw(10)<<left<<"LTORG"<<endl;
			return 6;
		}
	}
	int disp;
	string sd = tempCurrL.substr(objectStart + 3, 3); //gets disp 
	
	if(sd[0] == '8'|| sd[0] == '9' || sd[0] == 'A' || sd[0] == 'B'|| sd[0] == 'C' || sd[0] == 'D' || sd[0] == 'E' || sd[0] == 'F') {

		disp = negative(sd); //takes care of negative disps
			

	}	
	else {
		disp = convertInt(sd); 
	}	
	
	int target;
	int x;
	string objectcode = tempCurrL.substr(objectStart, 6);
	
	//direct 
	if(flags[3] == '0' && flags[4] == '0') {
		target = disp;
	}
	
	//index
	if(opMnemonic.compare("LDX") == 0) {
		x = intAdd;

	}
	//index
	if(flags[2] == '1') {
		target = target + x;
	}

	if(opMnemonic.compare("RSUB") == 0) {
		sicS<<setw(7)<<left<<opMnemonic<<endl;
		lisS<<setw(7)<<left<<opMnemonic;

	}


	//base relative
	if(opMnemonic.compare("LDB") == 0) {
		baseAdd = disp + intAdd;

	}

	//base relative
	if(flags[3] == '1'&& flags[4] == '0') {
		target = disp + baseAdd;
		
	}
	//PC
	if (flags[4] == '1'&& flags[3] == '0' && flags[0] == '1' && flags[1] == '1') {

		target = disp + intAdd + 3;
		

	}
	//simple 
	if(flags[0] == flags[1])  {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB") {
				if(flags[2] == '1') { //if x flag is 1
					sicS<<setw(7)<<left<<opMnemonic<<symN[i]<<",X"<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<symN[i]<<",X";
					lisS<<"    "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                 lisS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }

					return 6;	
				}
				else{
					
					sicS<<setw(7)<<left<<opMnemonic<<symN[i]<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<symN[i];
					lisS<<"      "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                 lisS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }

					return 6;
				}
			}
			
		}
		if(opMnemonic != "RSUB") {
			sicS<<setw(7)<<left<<opMnemonic<<target<<endl;
			lisS<<setw(7)<<left<<opMnemonic<<target;
			lisS<<"      "<<objectcode<<endl;
			if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                 lisS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }
  
			return 6;
		}
		 
	}
	//immediate 
	if(flags[1] == '1' && flags[0] == '0'&& flags[3] == '0' && flags[4] == '0') {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB" && target > 3){
				if(flags[2] == '1') {
					sicS<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<",X"<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<",X";
					lisS<<"    "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }

					return 6;
				}
				else {
					sicS<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<'#'<<symN[i];
					lisS<<"      "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }

					return 6;
			}
			
		}
		if(opMnemonic != "RSUB") {
			sicS<<setw(7)<<left<<opMnemonic<<'#'<<target<<endl;
			lisS<<setw(7)<<left<<opMnemonic<<'#'<<target;
			lisS<<"      "<<objectcode<<endl;
			if(opMnemonic == "LDB") {
                                 sicS<<"      ";
                                 lisS<<"      ";
                                 for(i = 0; i < symAdd.size(); i++) {
                                         if(target == symAdd[i]) {
                                                   sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
						   lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                   lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                          }

                                  }
                        }

			return 6;
		}		

	}
}
	//indirect 
	if(flags[0] == '1' && flags[1] == '0') {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB") {
				if(flags[2] == '1') {
					sicS<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<",X"<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<",X";
					lisS<<"     "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }

					return 6;
				}
				else {
					sicS<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<endl;
					lisS<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<endl;
					lisS<<"      "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                       }

                                                }
                                        }
					return 6;
				}
			}
		}
		if(opMnemonic != "RSUB") {
			sicS<<setw(7)<<left<<opMnemonic<<'@'<<target<<endl;
			lisS<<setw(7)<<left<<opMnemonic<<'@'<<target;
			lisS<<"      "<<objectcode<<endl;
			if(opMnemonic == "LDB") {
                                sicS<<"      ";       
                                for(i = 0; i < symAdd.size(); i++) {
                                        if(target == symAdd[i]) {
                                                  sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
						  lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                  lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                          }
                                }
                        }
			return 6;
		}
	
	}

	lisS<<"            "<<objectcode<<endl;

	return 6;
}

int Disassembler::format4(string flags) {
	
	opCode *search = new opCode();

	opMnemonic = search->searchMnemonic(opcode); //grabs mnemonic

	int target;
	int x;
	int i;
	string objectcode = tempCurrL.substr(objectStart, 8);


	for(i = 0; i < symAdd.size()-1; i++) {
		if(intAdd == symAdd[i]) { //checks for symbols
			sicS<<setw(7)<<left<<symN[i];
			lisS<<setw(7)<<left<<symN[i];
			break;
		}
		else {
			if(i >= symAdd.size()-2) {
				sicS<<"       ";
				lisS<<"       ";
			}
		}
	}
	for(i = 0; i < litAdd.size(); i++) { //checks for literals
		if(intAdd == litAdd[i]) {
			intAdd = intAdd + 1;
			objectStart = objectStart + 2;
			sicS<<setw(7)<<opMnemonic<<setw(10)<<left<<litS[i]<<endl;
			lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
			lisS<<setw(7)<<opMnemonic<<setw(7)<<left<<litS[i];
			lisS<<"      "<<objectcode<<endl;
			sicS<<"            "<<setw(10)<<left<<"LTORG"<<endl;
			lisS<<"            "<<setw(10)<<left<<"LTORG"<<endl;
		}
	}
	
	
	int disp;
	string sd = tempCurrL.substr(objectStart + 4, 4);
	if(sd[0] == '8'|| sd[0] == '9'|| sd[0] == 'A'|| sd[0] == 'B'|| sd[0] == 'C'|| sd[0] == 'D'||sd[0] == 'E'|| sd[0] == 'F') {
		disp = negative(sd); //takes care of negative disps 
	}
	else {
		disp = convertInt(sd);
	}
	target = disp; //direct 
		
	if(opMnemonic.compare("LDX") == 0) { //index
		x = intAdd;
	}
	if(flags[2] == '1') { //index
		target = target + x;
	} 
	if(opMnemonic.compare("RSUB") == 0) {
		sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<endl;
		lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<endl;
	}
	 if(opMnemonic.compare("LDB") == 0) {
                baseAdd = convertInt(tempCurrL.substr(objectStart + 4, 4));


        }

	//immediate 
	if(flags[1] == '1' && flags[0] == '0') {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB") {
				if(flags[2] == '1') {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<",X"<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<",X";
					lisS<<"     "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
						 sicS<<"      ";
              					 for(i = 0; i < symAdd.size(); i++) {
                       				 	if(target == symAdd[i]) {
                               				sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
							lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                		 	lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                       					}

               				 	}
					}
					return 8;
				}
				else {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<symN[i]<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<symN[i];
					lisS<<"      "<<objectcode<<endl;
					 if(opMnemonic == "LDB") {
                                                 sicS<<"      ";
                                                 for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                        sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
							lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";								  lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }
					return  8;
				}
			}
				
		
		}
		if(opMnemonic != "RSUB") {
			sicS<<"   "<<setw(7)<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<target<<endl;
			lisS<<"   "<<setw(7)<<'+'<<setw(7)<<left<<opMnemonic<<'#'<<target;
			lisS<<"      "<<objectcode<<endl;
			 if(opMnemonic == "LDB") {
                                 sicS<<"      ";
                                 for(i = 0; i < symAdd.size(); i++) {
                                	 if(target == symAdd[i]) {
                                 	 	sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
						lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                	 	lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                	}

                       		 }
                        }

			return 8;
		}
	
	}
	//indirect
	if(flags[0] == '1' && flags[1] == '0') {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB") {
				if(flags[2] == '1') {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<",X"<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<",X";
					lisS<<"     "<<objectcode<<endl;
					 if(opMnemonic == "LDB") {
                                		sicS<<"      ";
                                 		for(i = 0; i < symAdd.size(); i++) {
                                        		if(target == symAdd[i]) {
                                        			sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                         			lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
                                        		}

                                 		}       
                       			 }		

					return 8;
				}
				else {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'@'<<symN[i]<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<'@'<<symN[i];
					lisS<<"      "<<objectcode<<endl;
					 if(opMnemonic == "LDB") {
                                		 sicS<<"      ";
                                 		for(i = 0; i < symAdd.size(); i++) {
                                         		if(target == symAdd[i]) {
                                         			sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                         			lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                        		}	

                                 		}       
                        		}	

					return 8;
				}
			}
		}
		if(opMnemonic != "RSUB") {
			sicS<<"   "<<'+'<<setw(7)<<setw(7)<<left<<opMnemonic<<'@'<<target<<endl;
			lisS<<"   "<<'+'<<setw(7)<<setw(7)<<left<<opMnemonic<<'@'<<target;
			lisS<<"      "<<objectcode<<endl;
			if(opMnemonic == "LDB") {
                                sicS<<"      ";
                                for(i = 0; i < symAdd.size(); i++) {
                                        if(target == symAdd[i]) {
                                                 sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
						 lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                 lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                         }

                                }
                        }

			return 8;
		}
	}
	//simple
	if(flags[0] == flags[1]) {
		for(i = 0; i < symAdd.size(); i++) {
			if(target == symAdd[i] && opMnemonic != "RSUB") {
				if(flags[2] == '1') {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<symN[i]<<",X"<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<symN[i]<<",X";
					lisS<<"     "<<objectcode<<endl;
					 if(opMnemonic == "LDB") {
                                		sicS<<"      ";
                                 		for(i = 0; i < symAdd.size(); i++) {
                                         		if(target == symAdd[i]) {
                                         			sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                         			lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                        		}

                                 		}       
                        		}	

					return 8;
				}
				else {
					sicS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<symN[i]<<endl;
					lisS<<"   "<<'+'<<setw(7)<<left<<opMnemonic<<symN[i];
					lisS<<"      "<<objectcode<<endl;
					if(opMnemonic == "LDB") {
                                                sicS<<"      ";                                             
                                                for(i = 0; i < symAdd.size(); i++) {
                                                        if(target == symAdd[i]) {
                                                                sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
								lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                                        }

                                                }
                                        }
					return 8;
				}
			}
		}
		if(opMnemonic != "RSUB") {
			sicS<<"   "<<'+'<<setw(7)<<setw(7)<<left<<opMnemonic<<target<<endl;
			lisS<<"   "<<'+'<<setw(7)<<setw(7)<<left<<opMnemonic<<target;
			lisS<<"      "<<objectcode<<endl;
			if(opMnemonic == "LDB") {
                               sicS<<"      ";
                               for(i = 0; i < symAdd.size(); i++) {
                                         if(target == symAdd[i]) {
                                         	sicS<<"     "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;
						lisS<<setfill('0')<<setw(4)<<right<<hex<<intAdd<<setfill(' ')<<"  ";
                                                lisS<<"           "<<setw(7)<<left<<"BASE"<<symN[i]<<endl;

                                           }

                                }
                        }
			return 8;
		}
	}

	lisS<<"            "<<objectcode<<endl;
		
	return 8;

}
int Disassembler::negative(string sd) { 
//takes hex and converts it into 2's compliment to get negative int
	opCode *search = new opCode();
	string temp;
	string temp2;
	int num;
	int i;
	int j = 0;

	for(i = 0; i < sd.length(); i++) {
		if(sd[i] == 'F') {
			temp += "0000";
		}
		else if(sd[i] == 'E') {
			temp += "0001";
		}
		else if(sd[i] == 'D') {
			temp += "0010";
		}
		else if(sd[i] == 'C') {
			temp += "0011";
		}
		else if(sd[i] == 'B') {
			temp += "0100";
		}
		else if(sd[i] == 'A') {
			temp += "0101";
		}
		else if(sd[i] == '9') {
			temp += "0110";
		}
		else if(sd[i] == '8') {
			temp += "0111";
		}
		else if(sd[i] == '7') {
			temp += "1000";
		}
		else if(sd[i] == '6') {
			temp += "1001";
		}
		else if(sd[i] == '5') {
			temp += "1010";
		}
		else if(sd[i] == '4') {
			temp += "1011";
		}
		else if(sd[i] == '3') {
			temp += "1100";
		}
		else if(sd[i] == '2') {
			temp += "1101";
		}
		else if(sd[i] == '1') {
			temp += "1110";
		}
		else {
			temp += "1111";
		}
	}
	while(j < temp.length()) {
		temp2 += search->binSwitch(temp.substr(j,4));
		j = j + 4;


	}
	temp2 = "-"+ temp2;
	num = convertInt(temp2) - 1;
	
	return num;
}

int Disassembler::convertInt(string convert){ //takes string converts to int

	int strlength = convert.length();
	char addA [strlength + 1];
	strcpy(addA,convert.c_str());
	int convertedInt = strtol(addA, 0, 16);
	return convertedInt;
}

	
string Disassembler::binConvert(int convertB) { //converts to binary

	string binResult;
	int i,k;
	

	for(i = 3; i >= 0; i--) {
		
		k = convertB >> i;
		
		if(k & 1) {
		      binResult.insert(binResult.begin(), '1');	

		}
		else {
			binResult.insert(binResult.begin(), '0');
		}
		
	}
	return binResult;
}
