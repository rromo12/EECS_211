#include "disk_drive.h"
#include "definitions.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//Constructor Implementation
diskDrive::diskDrive(int size)
{blocks = (size+63)/64;
storage = (char *)malloc(int (64*blocks));
bitmap = (char *)malloc((int (blocks+7)/8));
memset(bitmap,0,((blocks+7)/8));}

diskDrive::~diskDrive()
{
	free( (void *) storage);
	free( (void *) bitmap);
}

int diskDrive::print() {
	int i, j;
	cout << "Disk Drive \nDisk_Size: " << blocks * 64;
	cout << "\nNumber of Blocks: " << blocks;
	cout << "\nSize of Map: " << (blocks+7)/8;
	cout << "\n" << "Memory Map: ";
	for(i=0; i < (blocks+7)/8 ; i++){ 
		j=bitmap[i] ;
		j=j & 0x000000ff;
		cout<<hex << j << " ";
			if ((i+1)%8 == 0)
				{cout<< "\n        ";}}
	cout << dec;
	return 0;
/* * value , &location*/}

int diskDrive::allocateBlock(int blockNumber){
	if(blockNumber < 0 || blockNumber >= blocks){return BAD_BLOCK_NUMBER;}	
	int pos, bitpos; int mask;
	pos=blockNumber/8;
	bitpos=blockNumber%8;
	mask=1<<bitpos;
	bitmap[pos] |= mask;
	return 0;}

int diskDrive::freeBlock(int blockNumber){
	if(blockNumber < 0 || blockNumber >= blocks){return BAD_BLOCK_NUMBER;}	
	int pos, bitpos; int mask;
	pos=blockNumber/8;
	bitpos=blockNumber%8;
	mask=~(1<<bitpos);
	bitmap[pos] &= mask;
	return 0;}

int diskDrive::isBlockFree(int blockNumber){
	if(blockNumber < 0 || blockNumber >= blocks){return BAD_BLOCK_NUMBER;}	
	int pos, bitpos; int mask;
	pos=blockNumber/8;
	bitpos=blockNumber%8;
	mask = 1<<bitpos;
	if(bitmap[pos] & mask) return 0;
	else return 1;
}