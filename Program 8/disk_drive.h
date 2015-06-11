#ifndef diskDrive_H
#define diskDrive_H
class diskDrive{public:
//Constructor
diskDrive(int size); 
//Destructor
~diskDrive();
//Member Methods

int print();

//Accessor Methods
int allocateBlock(int blockNumber);
int freeBlock(int blockNumber);
int isBlockFree(int blockNumber);
int storeBlock(char *d, int blk);
int retrieveBlock(char*d, int blk);
int formatDrive(int maxfiles);
int findNBlocks(int n, int start);
int totblocks();
private: 
	//Data Members
	int blocks;
	char *bitmap;
	char *storage;
};
#endif