/******************************************************************************
Name: Emily Jean Versoza(819442111) and Christina Tran (819312540) 
Username: cssc0422,cssc0466
Project: Assignment1
File: xbd.c
Note: This program will read in a regular type file and dumps it out in either bianry or hexidecimal
*******************************************************************************/

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "xbd.h"
	
	
	char fileA[100]; //stores file contents in character array 
	FILE *inFile; //file pointer
	char nameF[50]; //contains name of the file 

/******************************************************************************/

	int pBin() { //convert to binary 
		 
		char * filePtr;
		int address = 0;
		unsigned char bytesOpen;
		char binString[9];

		inFile = fopen(nameF, "rb"); //opens file 

		if(inFile != NULL) { //checks if file was opened
			while((bytesOpen = fread(fileA, sizeof(unsigned char), BIN, inFile)) != 0) {
			//goes through each byte until the end  and keeps count of # of bytes read 	
				printf("\n");
				printf("%07x: ", address); //prints address
				address = address + BIN; //adds 6 to get the next address
				
				bytesOpen = bytesOpen - 1; //subtracts one so it doesnt print after 				    null terminator 
				

				int counter = 0; 
				int i;
				

				for(i = 0; i < BIN; i++) {
					if(counter <= bytesOpen) {
						
						int k;
						for(k = 7; k >= 0; k--) {
							putchar((fileA[i] & ( 1 << k)) ? '1': '0');
						}//converts it to binary 
						// then putchar outputs it into terminal 
					}
					else {
						printf("  ");//spacing 
					}
					printf(" ");//spacing
					counter = counter + 1;//increments counter 
				}
				
				int j;
				counter = 0;
				for(j = 0; j < BIN; j++) { //prints out readable characters 
					if(counter <= bytesOpen) {
						if(((fileA[j] < 32) || fileA[j] > 126)) {
							printf("%c", '.'); 
						//if character is non readable then replace with '.'
						}
						else {
							printf("%c", fileA[j]);
							//else print out char 
						}

					}

					counter = counter + 1; //increment by one 
				}
			
			}

			printf("\n");//newline
		
		}


					
				
				
		else { 
			printf("ERROR: file cannot be found"); //if file cannot be found error 
			return 1;
		}	

		

			
		fclose(inFile); //close file 
		return 0;	//end of function 
	}

/********************************************************************************/

	int pHex() { //print in Hex 
		
		char * filePtr;
		int address = 0;
		unsigned char bytesOpen;
		
			
		inFile = fopen(nameF, "rb");//opens file 

		if(inFile != NULL) {	//if file successfully opens
		
			while((bytesOpen = fread(fileA, sizeof(unsigned char), HEX, inFile)) != 0) {
				//reads bytes until it reaches the end and keeps track in bytesOpen
					printf("\n");
					printf("%07x: ", address); //prints out address
					
					address = address + HEX; //adds 16 to address

					bytesOpen = bytesOpen - 1; //minus 1 so that it stops at the 					    end 

					filePtr = fileA;
					int counter = 0;		
					int i;
					for(i = 0; i <= 8; i++) {
						
						if(counter <= bytesOpen) { //prints it in Hex
							printf("%02x", *filePtr++);
							printf("%02x", *filePtr++);
						}
						else { 
							printf("  "); //spacing 
						}
						printf(" ");//spacing
						counter = counter + 2;//since its 2 bytes add 2
						
					

						
					}
					
					int j;
					counter = 0;
					
					for(j = 0; j < HEX; j++) { //prints out readable characters
						if(counter <= bytesOpen) { 
							if((fileA[j] < 32) || (fileA[j] > 126)) {
								printf("%c", '.');
							}
							else {	
								printf("%c", fileA[j]);//prints char
							}
							
						}
		
						
						counter = counter + 1;//increment by 1
					}
				

			}
			printf("\n");//newline
		}

		else {

			printf("ERROR: file cannot be found.");//if file cannot be open error
			return 1;
		}
	
		fclose(inFile);//close file
		return 0;
	} 
		

/*********************************************************************************/
	int main(int argc, char * argv[]){ 
		
	
		if(argc == 3) {//checks to see whether it should be printed in binary or hex
			strcpy(nameF, argv[2]); //gets the file name
			pBin(); //goes to in binary
		}
		else if(argc == 2) {
			strcpy(nameF, argv[1]); //gets file name
			pHex(); //goes to print in Hex
		}
		else {
			printf("Error not enough inputs\n");//if inputs are not enough exit program
			exit(0);
		}
			
		return 0;
		
	}
/*****************************[EOF]**************************************************/
	
