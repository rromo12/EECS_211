#ifndef machines_h
#define machines_h
#include "disk_drive.h"

class computer {
public:
	//Constructor
	computer(char name[21], int disksize);
	//Destructor
	~computer();
	//Member Functions
	int print();
	//Accessor Methods
private:
	//Data Members
	char name[21];
	diskDrive  *drive;

};
#endif