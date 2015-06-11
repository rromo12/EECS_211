#include "machines.h"
#include "disk_drive.h"
#include "definitions.h"
#include <string.h>
#include <iostream>
#include "system_utilities.h"
extern computer *networkArray[];

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
	std::cout<<"\n";
	for(int blk=0; blk < maximum_number_of_files/4; blk++)
	{
	drive->retrieveBlock(buffer,blk);
	 
	for(int pos=0; pos<4; pos++){
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

	std::cout << "\n\n\n";}
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
int computer::createFile(char *n,int len,char *ff){
	int pos, blk,blkpos,totalblocks;char buffer[64];
	pos = findFreeFileDescriptor();
	blk= pos/4;
	drive->retrieveBlock(buffer,blk);
	blkpos= pos%4;
	totalblocks=(len+63)/64;
	if (pos == FILE_SYSTEM_FULL)
		return FILE_SYSTEM_FULL;
	fileDescriptor *temp;
	temp =((fileDescriptor *)buffer)+blkpos;
	drive->allocateBlock(0);
	drive->allocateBlock(1);
for(int i=0 ; i<8; i++)
	temp->filename[i]= n[i];
	temp->filelength=len;
	int startblk=drive->findNBlocks(totalblocks,0);
	temp->blocknum =startblk ;
	putFileDescriptor(pos,temp);
	int test=startblk+((totalblocks+63)/64);
	for(int j=startblk;j<test;j++){
		drive->allocateBlock(j);
	drive->retrieveBlock(buffer,j);
		memset(buffer,0,64);
		memcpy(buffer,ff,64);
	drive->storeBlock(buffer,j);
	}
	return 0; 
}
int computer::findFile(char *fname, fileDescriptor *file){
	char buffer[64]; 
	fileDescriptor *fd;
	int j = drive->totblocks();
	for(int i=0; i<maximum_number_of_files/4; i++){
		drive->retrieveBlock(buffer,i);
		for (int j=0;j<4;j++) {
		fd=((fileDescriptor *)buffer)+j;
		if(strcmp(fname,fd->filename)==0)
			{memcpy(file,fd,16);
		return (i*4)+j;}
		}
	}
return -1;
}
void computer::printOneFile(fileDescriptor fd){
	int ii=0;
	int test;
	test= (fd.blocknum)+(((fd.filelength)+63)/64);
	char buffer[64];
	std::cout << "\nPrinting: ";
	for(int i=0; i<8; i++)
		std::cout << fd.filename[i];
	std::cout<< "\n";
	for(int j=fd.blocknum;j<test+2; j++)
	{drive->retrieveBlock(buffer,j);
	while(ii<fd.filelength && ii <64){std::cout << buffer[ii]; ii++;}
	
}
	std::cout << "\n";
}
void computer::printFiles(int argc,char *argv[]){
	fileDescriptor *file; int err,i;
	file=(fileDescriptor *)malloc(16);
	for(i=2;i<argc;i++){
	err=findFile(argv[i],file);
	if(err!=-1)
	printOneFile(*file);
	else 
		std::cout << "\nERROR FILE:" << argv[i]  << " NOT FOUND\n";
	}


	
}
int computer::transfer_file(char F[8],char C[20]){
	fileDescriptor *file; int loc,test;
	packet PF;
	char buffer[64];
	file=(fileDescriptor *)malloc(16);
	findFile(F,file);
	memcpy(PF.file,file->filename,8);
	PF.filelen=file->filelength;
	memcpy(PF.comp,name,21);
	test= (file->blocknum)+(((file->filelength)+63)/64);
	for(int j=file->blocknum;j<test+2; j++)
	{drive->retrieveBlock(buffer,j);
	memcpy(PF.filedata,buffer,64);}
	loc=findNode(C);
	networkArray[loc]->receive_file(PF);
	
	return 0;
}
int computer::receive_file(packet P){
	createFile(P.file,P.filelen,P.filedata);
	return 0;
};
void computer::delete_one_file(char n[8]){
	char buffer[64];
	fileDescriptor *file;
	int loc, blk, test;
	file=(fileDescriptor *)malloc(16);
	loc=findFile(n,file);
	getFileDescriptor(loc,file);
	blk=file->blocknum;
	test=blk+(file->filelength+63)/64;
	for(int j=blk;j<test;j++){
		drive->freeBlock(j);
	drive->retrieveBlock(buffer,j);
		memset(buffer,0,64);
	drive->storeBlock(buffer,j);}



	file->blocknum = -1;
	file->filelength= -1;
	memset(file->filename,0,8);
	putFileDescriptor(loc,file);
}
void computer::deleteFiles(int argc, char *argv[]){

fileDescriptor *file; int err,i;
	file=(fileDescriptor *)malloc(16);
	for(i=2;i<argc;i++){
	err=findFile(argv[i],file);
	if(err!=-1)
		delete_one_file(file->filename);
	else 
		std::cout << "\nERROR FILE:" << argv[i]  << " NOT FOUND";
	}


}