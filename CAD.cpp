// CAD.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "vecMath.h"
#include "zebraPattern.h"


#include <iostream>
#include <stdio.h>
#include <vector>

#define FILE_NAME "ps6_sample.txt"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	zebraPattern Surface(string(FILE_NAME));
	
	std::cin.get();
	return 0;
}

void readData ();
