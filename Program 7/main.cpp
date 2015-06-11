
#include <iostream>
#include <fstream>
using namespace std;
#include "definitions.h"
#include "system_utilities.h"
#include "machines.h"


int main(){
	int commandint=0, count,error=0;
	char *tokensptrs[MAX_TOKENS_ON_A_LINE];
	char line[MAX_CMD_LINE_LENGTH];
	

	//Attempt to Open Input File
	ifstream inpfile;
inpfile.open("p7input.txt", ios::in); 
if(inpfile.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit.";
			cin >> commandint;
			return 0;}

//Call Fill Command List
	fillCommandList();
	
while(commandint!=51){
//Allocate mem for tokens
for(int j=0;j<MAX_TOKENS_ON_A_LINE;j++){
			tokensptrs[j] = (char *) malloc(sizeof(char)*255);
			//NULL MEM ALLOCATED
			memset(tokensptrs[j], 0,255);}
//NULL LINE ARRAY
memset(line, 0, sizeof(char)*MAX_CMD_LINE_LENGTH);
inpfile.getline (line, MAX_CMD_LINE_LENGTH);
count = parseCommandLine(line,tokensptrs);
commandint = getCommandNumber(tokensptrs[0]);



	//Switch Case Statement
switch(commandint){
case SYSTEM_STATUS: 
	systemStatus();
		break;
case HALT: 
		break;
case ADD_NETWORK_NODE: 
	error=addNetworkNode(tokensptrs,count);
		break;
case DELETE_NETWORK_NODE: 
	error=deleteNetworkNode(tokensptrs,count);
	
		break;
case CREATE_FILE: 
	error=createfiles(tokensptrs,count);
		break;
case LS: 
	error=ls(tokensptrs, count);
		break;
case DELETE_FILES: 
	cout<< "\nRecognized Command:Delete Files";
		break;
case PRINT_FILES: 
	cout<< "\nRecognized Command:Print Files";
		break;
case TRANSFER_FILE: 
	cout<< "\nRecognized Command:Transfer File";
		break;
default: 
	cout<< "\nUndefined Command";
		break;}
/*cout<< "\nTokens: \n";
			for (int j=0; j < count; j++){
				cout << tokensptrs[j]<< "\n";}
			cout << "\n";*/
for(int j=0;j<10;j++){
	free((void *) tokensptrs[j]);}
if(error!=0)
	printError(error);
}
cin >>error;
return 0;}