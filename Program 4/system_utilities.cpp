#include <stdlib.h> 
#include "system_utlities.h"
#include <stdio.h>
#include "definitions.h"
#include <string.h>
#include <iostream>
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
