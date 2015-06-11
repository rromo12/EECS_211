#include "machines.h"
#include "disk_drive.h"
#include "definitions.h"
#include <string.h>
#include <iostream>
//Constructor


computer::computer(char compname[], int size)
{ memcpy(name, compname,21);
if(size < 128)	size=128;
drive = new diskDrive(size);}

//Destructor
computer::~computer() {
	free( (void *) drive);
}

int computer::print()
{std::cout << "Machine:" << name<<"\n";
drive->print();


return 0;}
int computer::isThisMyName(char *n){

	int test;
			test = (strcmp(n,name));
		if(test==0)
			return 1;
	    else return 0;

};
PC::PC(char compname[], int size, char ownern[])
	:computer(compname,size) 
{ memcpy(owner, ownern,31);
 }
int PC::print(){
	computer::print();
	std::cout << "\nOwner:" << owner << "\n\n";
	return 0;
}
Server::Server(char compname[], int size, char loc[])
	:computer(compname,size) 
{ memcpy(location, loc,15);
 }
int Server::print(){
	computer::print();
	std::cout <<"\nLocation:" << location << "\n\n";
		return 0;
}
printer::printer(char compname[], int size, int num)
	:computer(compname,size) 
{ printers=num;
 }
int printer::print(){
	computer::print();
	std::cout <<"\nNumber of Printers:" << printers << "\n\n";
		return 0;
}