// CAD.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "vecMath.h"
#include "zebraPattern.h"


#include <iostream>
#include <stdio.h>
#include <vector>

#define FILE_NAME /*"car-panel1.txt"*/"ps6_sample.txt"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string fileName;
	std::cout << "Please insert the name of the file to use: ";
	std::cin >> fileName;
	//fileName = FILE_NAME;
	zebraPattern Surface(fileName);
	
	std::cin.get();
	return 0;
}
