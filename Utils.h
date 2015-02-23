//This file contains all the utility functions

#include <iostream>
#include <vector>
#include <string>

using namespace std;

union Vertice {
	float m_vVec[3];  
	struct {
			float x;
			float y;
			float z;
	};
};

std::vector<std::string> split (std::string line);
std::vector<int> vectorStringToInt ( std::vector<std::string>tokens );
Vertice vectorStringToVertice ( std::vector<std::string>tokens );


