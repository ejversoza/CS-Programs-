/**
 * Program #2
 * This program will find all the prime numbers in a given range
 * CS108-1
 * 9-24-18
 * Emily Jean Versoza 
 */
        #include<stdio.h>
        #include<stdlib.h>
        #include<string.h>
        #include<ctype.h>

        int validateString(char *);
        int realInt;
        void sOe(int);

        int main(int argc, char * argv[]) { //input is from command line


                if(argc != 2) {
                        printf("Invalid input\n"); //check if user only inputs one arg
                        exit(0);
                }
   if(validateString(argv[1]) == 1) { //calls validateString
                        printf("Invalid input\n");
                        exit(0);
                }

                int realInt = atoi(argv[1]); //turns string into integer

                if(realInt  >= 15000 || realInt < 2) { //checks to see if its greater than two
                        printf("Invalid input\n"); // and less than maximum size
                        exit(0);
                }
                printf("Program #2, cssc0562, Emily Jean Versoza\n\n");

                sOe(realInt); //calls s0e
                return 0;


        }

        int validateString(char * stringIn) {
                if(strstr(stringIn, ".") != NULL) { //checks if its a double or float
	   	 return 1;
                }

                int i = 0;

                while(stringIn[i] != '\0') { //goes through each character to see if its valid
                        if(isalpha(stringIn[i]) != 0) { //if its an alphabet letter its invalid
                                return 1;
                        }
                        else if(isdigit(stringIn[i]) == 0) { //if its not a digit its invalid
                                return 1; //mostly to check for special characters
                        }
                        else { //if the current character passes moves on to the next
                                i++;
                        }
                }
                return 0; //string passess

        }

void sOe(int n) {

                int primeA[n];
                int i;
                int x;


                for(i = 1; i < n + 1; i++) { //fills array
                        primeA[i] = i;
                }
                for( i = 2; i < n + 1; i++) { //starts at two

                        if(primeA[i] != 0) { //checks if its been flagged
                                for(x = 2*i; x < n + 1; x += i) { //goes through all the multiples
                                        primeA[x] = 0; //and flags them
                                }
                        }
                }
                printf("Prime numbers in the range 2..%d are:\n" , n);
                for(i = 2; i < n + 1; i++) {
                        if(primeA[i] != 0) { //prints the numbers that have not been flagged
                                printf("%d ", primeA[i]);
                        }
                }
                printf("\n");
                exit(0);

        }

