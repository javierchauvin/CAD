#include "StdAfx.h"
#include "Export.h"
#using <mscorlib.dll>

//#include "Utils.h"
//#include "vecMath"
//#include <iostream>
//#include <vector>

//using namespace std;
using namespace System;

void createVRML (vector<vector<vecMath>> Nodes, vector<vector<bool>> Colors ){

	vector<vector<int>> Faces;
	vector<int> face;

	ofstream outfile ("Surface.wrl");
	outfile << "#VRML V2.0 utf8" << std::endl;
	outfile << "#" << std::endl;
	outfile << "Surface by Javier Chauvin" << std::endl;
	outfile << "	Shape{" << std::endl;
	outfile << "		geometry IndexedFaceSet{" << std::endl;
	outfile << "			coord Coordinate{" << std::endl;
	outfile << "				point[" <<std::endl;
	
	//print the points

	for(unsigned int i = 0; i < Nodes.size(); i++){
		for(unsigned int j = 0; j < Nodes.at(i).size(); j++){
			outfile << "						"<<Nodes[i][j].Vertex.x<<" "<<Nodes[i][j].Vertex.y<<" "<<Nodes[i][j].Vertex.z<<","<< std::endl;

			
		}
	}


	outfile << "						]" << std::endl;
	outfile << "			}" << std::endl;

	outfile << "			color Color{" << std::endl;
	outfile << "				color[ 0 0 0, 1 1 1 ]" << std::endl;
	outfile << "			}" << std::endl;

	//outfile << "			colorIndex[	" << std::endl;
	//outfile << "							"<<Colors[i][j].Vertex.x<<" "<<Colors[i][j].Vertex.y<<" "Colors[i][j].Vertex.z<<","<< std::endl;
	//outfile << "						 ]" << std::endl;

	outfile << "			Solid FALSE" << std::endl;
	outfile << "	}" << std::endl;
	outfile << "}" << std::endl;
	Console::Clear();
}
