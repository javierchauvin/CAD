#pragma once

#include "vecMath.h"
#include "StdAfx.h"

using namespace std; 

class zebraPattern{
	 
public:
	zebraPattern(string fileN);
	~zebraPattern(void);

private:
	string fileName;
	void readData ( void );
	void printData ( void );
	vector<Vertice> getContainingBox ( void );
	void getLightPlain ( void );
	vector<Vertice> getNormal ( Vertice ActualPoint );
	bool getNodeColor ( Vertice ActualPoint );
};

