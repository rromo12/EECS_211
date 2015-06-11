#include <iostream>
#include <fstream>
#include "definitions.h"
#include "system_utlities.h"
using namespace std;


int main() {
	ifstream inpfile;
	int count,i ;
	char *tokensptrs[MAX_TOKENS_ON_A_LINE];
	//
	char line[MAX_CMD_LINE_LENGTH];
	//Attempt to open file 
inpfile.open("p4input.txt", ios::in); 
if(inpfile.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit.";
			cin >> count;
			return 0;}
//Call function 4 times, zero mem before getting lines, display info
for(i=0; i<4;i++){
			for(int j=0;j<10;j++){
			tokensptrs[j] = (char *) malloc(sizeof(char)*255);
			memset(tokensptrs[j], 0,255);}
			memset(line, 0, sizeof(char)*MAX_CMD_LINE_LENGTH);
			inpfile.getline (line, MAX_CMD_LINE_LENGTH);
			count = parseCommandLine(line,tokensptrs);
			cout<< "The string is :" << line << "\n";
			cout<< "Number of Tokens: " << count << "\n";
			cout<< "Tokens: \n";
			for (int j=0; j < count; j++){
				cout << tokensptrs[j]<< "\n";}
			cout << "\n\n";

			}
for(int j=0;j<10;j++){
	free((void *) tokensptrs[j]);}
return 0;}
