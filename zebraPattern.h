#pragma once
#include <iostream>
#include <vector>

#include "vecMath.h"

using namespace std; 

class zebraPattern
{
	std::string fileName; 
private:
	void readData ( void );
	vector<float> getContainingBox ( void );
	void getLightPlain ( void );
	vector<Vertice> getNormal ( Vertice ActualPoint );
	bool getNodeColor ( Vertice ActualPoint );

public:
	zebraPattern(std::string fileN);
	~zebraPattern(void);
};

