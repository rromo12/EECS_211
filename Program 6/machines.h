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
	virtual int print();
	
	int isThisMyName(char *n);
protected:
	//Data Members
	char name[21];
	diskDrive  *drive;

};
/*Class B:public A {

data members ---------- only the new ones 
function members -new ones
		 -need extra work if extra data members are tobe used
		 -function with same name as the parent class
		 -does something in addition to parent class function		 -
		 -
};
*/
class PC : public computer
{public:
//Constructor
PC(char compname[], int size, char owner[]);
~PC();
virtual int print();
private: 
	char owner[32];

};
class Server : public computer
{public:
	Server(char compname[], int size, char loc[]);
	virtual int print();
private:
char location[16];
};
class printer : public computer
{	public:
	printer(char compname[], int size, int num);
	virtual int print();
private:
int printers;
};
#endif