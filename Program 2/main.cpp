/*

    Polynomial Program From File
    Author:  Rene Romo
	EECS 211, Winter 2013, Program 2
           This program reads the coeffecients of a polynomial from a text file, the polynomials are formated in the following manner
		   <Highest Power>  <coefficients in increasing power>
			I.E 1+2x+3x^2
			would be written
			2 1 2 3
            The program then outputs the polynomial, its derivative and a table of values.            

*/
#include <iostream>
#include <fstream>
using namespace std;
ifstream inp("polydata.txt", ios::in);
// This is the input file for when KEYBOARD is 0.
ifstream inFile;


//#DEFINE 
#define MAX_POWER 5
#define NUMBER_OF_COEFFICIENTS 6
#define KEYBOARD 0


//Declare Vars
float input, coef[NUMBER_OF_COEFFICIENTS], deriv[MAX_POWER]; int degree, i, x, j;



//Function Prototypes
float getinput(int src);
int readpoly(float poly[]);
int printpoly (float coef[],int degree);
int derivpoly(int degree,float poly[], float deriv[]);
float eval(int degree,float poly[],float x);

int main() {
	// Variables
	input = 0;x=0;
	 // Check if input file exists
	if(KEYBOARD==0) { 
		inFile.open("polydata.txt", ios::in);
		if(inFile.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit.";
			cin >> input;
			return 0;}}
	//Code 
	//Main for loop run throut 5 times
	for(i=0; i<5; i++){
		//Get highest degree
	degree = getinput(KEYBOARD);
	//Read polynomial into array
	readpoly(coef);
	//Print polynomial
	printpoly(coef,degree);
	//Calculate Derivative
	derivpoly(degree,coef,deriv);
	//Output derivative, 0 if degree is 0
	if(degree==0){cout << "0";}
	else {printpoly(deriv,degree-1);}
	//Output Table of Values
	cout << "\n\nx"  <<  "              P(x)" << "                       P'(x)";
	cout << "\n==================================================================";
	//Calculate/Output Values usinc eval function and a for loop
	for(j=0; j<=5; j++)
	{cout <<"\n" << x+(0.2*j) << "                   " << eval(degree,coef,x+(0.2*j))   << "                   " << eval(degree-1,deriv,x+(0.2*j));}
		
	cout << "\n\n\n\n\n\n\n\n\n\n\nEnter an integer to view the next polynomial:";
	cin >> input;
	cout<< "\n====================================================================";}
	//Prompt to continue
	cout << "\nEnd of data sets.  Enter an integer to quit.\nHave a nice day!";
	cin >> input;	
	
	return 0;}
int readpoly(float poly[]) {
	//Coefficients into array.and check max power and display warning if too large,
	//Extra coeffecients placed into the Unused Extra variable
	float extra;
	for(int i=0; i<=degree; i++)
	    {if(i <= MAX_POWER){poly[i] = getinput(KEYBOARD);}
	     if(i > MAX_POWER){extra = getinput(KEYBOARD);
							if(degree>MAX_POWER){cout << "\n \n ***ERROR: Polynomial degree to large, will be reduced";
							if(i==degree){degree=MAX_POWER;}}}
		 
	    }
	cout <<"\nThe Polynomial is:"; 
	return  0;
	}
int derivpoly(int degree,float poly[], float deriv[]){
	//Derive polynomial using a for loop, if degree = 0 deriv=0
	for(int j=0; j<NUMBER_OF_COEFFICIENTS; j++){
if(j==0) {deriv[j]=0;}
if(j>0) {deriv[j-1]=j*poly[j];}
else if(j>degree+1) {poly[j] =0;}
}
//Output Derivative
	cout << "\n \nThe derivative of the polynomial is: ";
return 0;}
int printpoly (float coef[],int degree)
	//Print Polynomial with correct formating using a forloop
{for( int j=0; j<=degree; j++)
	{cout << coef[j];
	for(int i=0; i<j; i++)
	{cout << "*x";}
	if(j < degree){cout << "+";}}
			
return 0;}
float eval(int degree,float poly[],float x) {
 //Evaluate Polynomial with x value using for loop
	float ans = 0, temp = 0;
 for(int j=0; j<= degree; j++){
	 if (degree>=1){
	 ans=ans * x + poly[degree-j];}
	 else if(degree == 0) {ans = poly[j];}}
return ans ;}
float getinput(int src){float input;
	//Decide source for input, depending on KEYBOARD current definition
	if(KEYBOARD){
	cin >> input;
				}
else
{inp >> input;}

return input;
}