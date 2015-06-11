#include <stdlib.h>  
#include <string.h>
#include "definitions.h"
#include "system_utilities.h"
#include "machines.h"
#include <iostream>
computer* networkArray[MAX_NETWORK_NODES];


class commandElement {
	
public:
	commandElement(char * cmd, int cmdnum){
	commandint = cmdnum;
	commandstr = (char *) malloc(sizeof(char)*strlen(cmd)+1);
	memset(commandstr,0,strlen(cmd)+1);
	memcpy(commandstr,cmd,strlen(cmd));
	}
	int amIThisCommand(char * testcmd){
		int test;
			test = (strcmp(testcmd,commandstr));
		if(test==0)
			return commandint;
	    else return 0;}
	
private:
char* commandstr;
int	  commandint;
};
commandElement *CommandList[NUMBER_OF_COMMANDS];
void fillCommandList()
{
CommandList[0]= new commandElement("system_status", SYSTEM_STATUS);
CommandList[1]= new commandElement("halt", HALT);
CommandList[2]= new commandElement("add_network_node", ADD_NETWORK_NODE);
CommandList[3]= new commandElement("delete_network_node", DELETE_NETWORK_NODE);
CommandList[4]= new commandElement("create_file", CREATE_FILE);
CommandList[5]= new commandElement("ls" , LS);
CommandList[6]= new commandElement("delete_files", DELETE_FILES);
CommandList[7]= new commandElement("print_files", PRINT_FILES);
CommandList[8]= new commandElement("transfer_file", TRANSFER_FILE);
}
int getCommandNumber(char *s){ 
	int result=0,i=0;

	while(result==0 && i<NUMBER_OF_COMMANDS){
		result=CommandList[i]->amIThisCommand(s);
	i=i+1;}
	if (result != UNDEFINED_COMMAND)
	{return result;}
	else 
		return UNDEFINED_COMMAND;}
int parseCommandLine(char line[], char *tokens[]){
	int i, next_token, start, end, count, length;
 next_token=0;
 count=0;
 length = 0; 
 i=0;
	while(line[i]!=0){
		//Establish case of token, regular or " double quote" and get start,end and length of token.
		//Regular case, look for first character
		if( line[i] != ' ' && line[i] != '"'){
			//Save location of first character
			start=i;
				//Search for terminating character
				while(line[i] != ' ' && line[i]!=0 ) {
					i++;
					//Set location of terminating character and calculate length of token
				if(line[i] == ' ' || line[i]==0)
					{end=i;
					length= end-start;}}
				//Increase token count
				memset(*tokens, 0, sizeof(char)*(length));
				memcpy(*tokens,line+start,length);
				tokens++;
		count=count+1;}


		//Case of double quotes
		else if( line[i] == '"') {
			//Set start location
			start=i+1;
				i=i+1;
            //Look for terminating character
			while(line[i]!= '"')
				{i++;
				//Set location of terminating character and calculate token length
			if (line[i] == '"')
				{end=i;
				length=end-start;
			;}}
				//Increase token count
				memset(*tokens, 0, sizeof(char)*(length));
				memcpy(*tokens,line+start,length);
				tokens++;
		count=count+1;
		i++;}		
	
	i++;
}
	return count;}
int string2int(char D[])
{int i,N=0;
for(i=0;i<strlen(D);i++)
  N = N*10 + (D[i]-'0');
return N;
}
void systemStatus(){for(int i=0; i<MAX_NETWORK_NODES; i++){
	if(networkArray[i]!=NULL) networkArray[i]->print();
}};
int addNetworkNode(char *toks[], int count){
	int type, size;
	
	for(int i=0;i<MAX_NETWORK_NODES;i++)
		if(networkArray[i]==NULL){
			type=getNodeType(toks[1]);
			size = string2int(toks[3]);
			switch(type){
			case 1:  //PC
				networkArray[i] = new PC(toks[2],size,toks[4]);
				break;
			case 2: //Server
				networkArray[i] = new Server(toks[2],size,toks[4]);
			break;
			case 3: //Printer
				count= string2int(toks[4]);
				networkArray[i] = new printer(toks[2],size,count);
			break;
			case 4:
			return INVALID_COMPUTER_TYPE;}

		return 0;};
	return NETWORK_FULL;};
int getNodeType(char *type){
	// 1 = PC
	// 2 = Server
	// 3 = Printer
	// 4  = unknown

		int test;
			test = (strcmp(type,"PC"));
		if(test==0)
			return 1;
		else 
			test = (strcmp(type,"server"));
		if(test==0)
			return 2;
		else 
			test = (strcmp(type,"printer"));
		if(test==0)
			return 3;
		else
			return 4;

}
int deleteNetworkNode(char *toks[], int numberToks){int location;
    location=findNode(toks[1]);
	if(location>0){delete networkArray[location];
					networkArray[location]=NULL;}
	if ( location == -1) return COMPUTER_NOT_FOUND;
	return 0;}

int findNode(char *n){

int result=0,i=0;
	while(result==0 && i<MAX_NETWORK_NODES){
		if (networkArray[i] != NULL){
			result= networkArray[i]->isThisMyName(n);}
	i=i+1;}
	if (result != 0)
	{return result;}
	else 
		return -1;}
void printError(int err){
switch(err){
case NETWORK_FULL:
	std::cout << "\n***ERROR: Network Full";
		break;
case COMPUTER_NOT_FOUND:
	std::cout << "\n***ERROR : Computer Not Found";
		break;
case INVALID_COMPUTER_TYPE:
	std::cout << "\n***ERROR: Bad Computer Type";
		break;
case BAD_BLOCK_NUMBER: 
std::cout << "\n***ERROR: Bad Block Number";
default:
	std::cout << "\nUnknown Error";}
}