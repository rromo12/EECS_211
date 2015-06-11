#include "machines.h"
#include "disk_drive.h"
#include "definitions.h"
#include <string.h>
#include <stdlib.h>
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
{std::cout << "Machine:" << name;
drive->print();


return 0;}