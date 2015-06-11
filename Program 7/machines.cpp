#include "machines.h"
#include "disk_drive.h"
#include "definitions.h"
#include <string.h>
#include <iostream>
computer::computer(char compname[], int size)
{ memcpy(name, compname,21);
if(size < 128)	size=128;
drive = new diskDrive(size);
maximum_number_of_files=8;
;}
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
 maximum_number_of_files=8;
 drive->formatDrive(maximum_number_of_files);
 }
int PC::print(){
	computer::print();
	std::cout << "\nOwner:" << owner << "\n\n";
	return 0;
}
Server::Server(char compname[], int size, char loc[])
	:computer(compname,size) 
{ memcpy(location, loc,15);
maximum_number_of_files=16;
drive->formatDrive(maximum_number_of_files);
 }
int Server::print(){
	computer::print();
	std::cout <<"\nLocation:" << location << "\n\n";
		return 0;
}
printer::printer(char compname[], int size, int num)
	:computer(compname,size) 
{ printers=num;
maximum_number_of_files=16;
drive->formatDrive(maximum_number_of_files);
 }
int printer::print(){
	computer::print();
	std::cout <<"\nNumber of Printers:" << printers << "\n\n";
		return 0;
}





void computer::printDirectory(){
	char buffer[64]; 
	fileDescriptor *fd;
	for(int blk=0; blk < 2; blk++)
	{
	drive->retrieveBlock(buffer,blk);
	for(int pos=0; pos< maximum_number_of_files/2; pos++){
	fd= ((fileDescriptor *)buffer)+pos;
	std::cout << "File Entry - " << blk*4+pos <<" " ;
	if(fd->filelength == -1)
	{std::cout << "File Descriptor not in Use \n" ;}
	else {std::cout<< " =   " ;
	for(int i=0; i<8; i++)
		std::cout << fd->filename[i];
	std::cout<< " length = " << fd->filelength;
	std::cout<< "   first block on disk = " << fd->blocknum << "\n";}}
	}
 }
int computer::findFreeFileDescriptor(){
char buffer[64]; 
	fileDescriptor *fd;
	for (int blk = 0; blk<4; blk++){
	drive->retrieveBlock(buffer,blk);
		for(int pos=0; pos <=4; pos++){
			fd= (((fileDescriptor *)buffer)+pos);
				if(fd->filelength == -1)
					return blk*4 +pos;}}
return FILE_SYSTEM_FULL;}
void computer::getFileDescriptor(int n, fileDescriptor *fd){
		int blk;
			int pos;
		char buffer[64]; 
		blk= n/4;
		pos = n%4;
	drive->retrieveBlock(buffer,blk);
	fd=((fileDescriptor *)buffer)+pos;
	}
void computer::putFileDescriptor(int n, fileDescriptor *fd){
	int  blk,position, len, blocknum;
	char buffer[64], name[8];
	fileDescriptor *temp;
	blk= n/4;
	position = n%4;
	len=fd->filelength;
	blocknum=fd->blocknum;
	drive->retrieveBlock(buffer,blk);
	for(int i = 0; i<8;i++)
		name[i]=fd->filename[i];
	(((fileDescriptor *)buffer)+position)->blocknum=blocknum;
	(((fileDescriptor *)buffer)+position)->filelength=len;
	for(int i=0; i<8; i++)
		(((fileDescriptor *)buffer)+position)->filename[i]=name[i];
	drive->storeBlock(buffer,blk);

}
int computer::createFile(char *n,int len){
	int pos, blk,blkpos;char buffer[64];
	pos = findFreeFileDescriptor();
	blk= pos/4;
	drive->retrieveBlock(buffer,blk);
	blkpos= pos%4;
	if (pos == FILE_SYSTEM_FULL)
		return FILE_SYSTEM_FULL;
	fileDescriptor *temp;
	temp =((fileDescriptor *)buffer)+blkpos;
for(int i=0 ; i<8; i++)
	temp->filename[i]= n[i];
	temp->filelength=len;
	temp->blocknum= pos/4;
	putFileDescriptor(pos,temp);
	return 0; 
}