#include <stdlib.h>  
#include <string.h>
#include "definitions.h"

  



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
	int i, next_token,prevcount, start, end, count, length;
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
