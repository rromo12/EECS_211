#include <iostream>
#include "definitions.h"
using namespace std;


void printError(int err){
	if(err==BAD_BLOCK_NUMBER){
	cout << "\n***ERROR. Bad block number encountered. \n";}
	else {cout << "UNKNOWN ERROR";}}