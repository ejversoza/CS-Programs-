/**************************************************************************************************
Name: Emily Jean Versoza - cssc0422, 819442111
      Christina Tran - cssc0466, 819312540
      Leeza Dalisay- cssc0464 - 819514274
Project: Assignment #2
File: main.cpp
Notes: Here is the main, checks for object file in the arguments and changes suffix to have access to the symbol file. If everything is valid passes it on to xed.cpp.
 **************************************************************************************************/
#include <iomanip>
#include <fstream>
#include <string>
#include "xed.h"

using namespace std;

int main(int argc, char* argv[]) {
	if(argc < 2) { //if less than two not enough args or user did not input file.
		cout<<"Error: no file inputed, please insert file in command line"<<endl; 
		exit(0);
	}
	else {
		string file = argv[1]; //grabs the file name 
		string oSuffix = ".obj"; 
		if(file.find(oSuffix) == string::npos) { //checks if it an object file 
			cout<<"Error: file is not an object file"<<endl;
			exit(0);
		}
		ifstream objF;
		string objN = argv[1];
		objF.open(objN.c_str()); //opens object file 
		if(!objF) {
			cout<<"Error: file cannot be open"<<endl;
			exit(0);
		}
		int pos = file.find('.'); //finds the starting of file type
		string filesym = file.substr(0,pos); //grabs the name of the file
		filesym = filesym + ".sym"; //adds .sym to access the symbol file

		ifstream symF;
		symF.open(filesym.c_str()); //opens symbol file 
		if(!symF) { //if not then file cannot be open 
			cout<<"Error: file cannot be open"<<endl;
			exit(0);
		}

		string sic = file.substr(0,pos); //creates the name for the sic file
		sic = sic + ".sic";

		string lis = file.substr(0,pos); //creates the name for the lis file
		lis = lis + ".lis";
	

		
		Disassembler *objFile = new Disassembler; 	
		objFile->readdisF(objF,symF,sic,lis);	//passes everything on to xed.cpp


	}

	return 0;

}


