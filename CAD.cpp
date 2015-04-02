// CAD.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "vecMath.h"
#include "zebraPattern.h"
#include "Bezier.h"

#include <iostream>
#include <stdio.h>
#include <vector>

#define FILE_NAME "face.txt"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//string fileName;
	//int rep;
	//std::cout << "Please insert the name of the file to use: ";
	//std::cin >> fileName;
	//std::cout << "Insert Laplacian Smoothing applications: ";
	//std::cin >> rep;
	////fileName = FILE_NAME;
	//zebraPattern Surface(fileName, rep);
	
	Bezier Curves;
	Curves.drawCurves();	
	std::cout << "Drawing";

	std::cin.get();
	return 0;
}
