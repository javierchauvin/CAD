#pragma once

#include "vecMath.h"
#include "StdAfx.h"

using namespace std; 

struct CBox{
	Vertice min;
	Vertice max;
	Vertice dimensions;
};

class zebraPattern{
	 
public:
	zebraPattern(string fileN);
	~zebraPattern(void);

private:
	string fileName;

	//Reads all the data from a ascii file and arenge it on a matrix
	//teh dimension of the matrix is set by the first line in the .txt file
	void readData ( void );
	
	//Just print the array readed.
	void printData ( void );

	//Calculates the containing box of the inforamtion ridden
	//It returns a vector of vertices with 3 elements:
	//0: min values on x,y,z
	//1: max values on x,y,z
	//2: dimensions of the containing box on x,y,z
	CBox getContainingBox ( void );
	void getLightPlain ( CBox Box );
	vecMath getNormal ( int i, int j );
	bool zebraPattern::getNodeColor ( Vertice InterPoint );
};

