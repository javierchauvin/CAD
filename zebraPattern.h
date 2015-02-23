#pragma once

#include "vecMath.h"
#include "StdAfx.h"

using namespace std; 

class zebraPattern{
	 
public:
	zebraPattern(string fileN);
	~zebraPattern(void);
	void readData ( void );
	void zebraPattern::printData ( void );

private:
	string fileName;
	vector<float> getContainingBox ( void );
	void getLightPlain ( void );
	vector<Vertice> getNormal ( Vertice ActualPoint );
	bool getNodeColor ( Vertice ActualPoint );
};

