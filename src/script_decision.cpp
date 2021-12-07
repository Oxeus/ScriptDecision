//*****************************************************************************************
//Program by: Adam LaFleur
//Date: May 20, 2019
//Class: CS202 - Programming Systems
//Program: #3 - Script Decisions
//File: assignment03.cpp
//Purpose: The purpose of this program is to load in data from a file specifically a script and
//allow to user to make decisions on which path the user can take to get different results.
//assignment03.cpp has the purpose of controlling the program and sending the data file name to the object.
//*****************************************************************************************
#include "script.h"



//Creates a script object and uses public functions to run and control the object.
int main()
{
	script main("data.txt");
	cout << "------------------------ Assignment 03: Script ------------------------ " << endl;
	cout << "----------------------------------------------------------------------- " << endl << endl;
	//main.display();
	while(main.is_finished())
	{
		main.move();
	}
	cout << "----------------------------------------------------------------------- " << endl;
	cout << "----------------------------------------------------------------------- " << endl;	
	return 1;	
}

