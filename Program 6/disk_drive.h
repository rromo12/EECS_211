#ifndef diskDrive_H
#define diskDrive_H
class diskDrive{public:
//Constructor
diskDrive(int size); 
//Destructor
~diskDrive();
//Member Methods
int print();
int allocateBlock(int blockNumber);
int freeBlock(int blockNumber);
int isBlockFree(int blockNumber);
//Accessor Methods


private: 
	//Data Members
	int blocks;
	char *bitmap;
	char *storage;
};
#endif