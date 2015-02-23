#include "StdAfx.h"
#include "zebraPattern.h"
#include "vecMath.h"

#include <fstream>
#include <sstream>

#define STRIP_FACTOR 0.1

//enum LightColor {
//	GRAY 
//}

using namespace std;

vector<vector<vecMath>> DataFile;  //This data is arrenged as a matrix

struct LightPlane{
   vecMath a;
   vecMath b;
   vecMath Po;
	float	  stripWidth;
}Plane;

zebraPattern::zebraPattern( string fileN )
{
	fileName = fileN;
	readData();
	getLightPlain(getContainingBox());	
	printData();
}

zebraPattern::~zebraPattern(void)
{
}

void zebraPattern::readData ( void ){
	string line;
	ifstream surfaceFile (fileName);
	vector<int> MatrixDimension;

	if (surfaceFile.is_open()){ 
		getline (surfaceFile,line);

		std::vector<int> Dimensions =vectorStringToInt(split(line));
		MatrixDimension.assign( Dimensions.begin(),Dimensions.end());

		int i = 0, j = 0;  //Is not used yet 
		std::vector<vecMath> auxVec;

		while(getline (surfaceFile,line)){
			if (MatrixDimension.at(1) > i){
				auxVec.push_back(vectorStringToVertice(split(line)));
				i++;
			} 
			if( MatrixDimension.at(1) <= i ){
				DataFile.push_back(auxVec);
				auxVec.clear();
				i = 0;
				j++;
			}
		}
	}
}

CBox zebraPattern::getContainingBox ( void ){
	
	//Vector 0 for min values
	//Vector 1 for max values
	//Vector 2 for dimentions of the bounding box
	CBox Box = {0};
 
	for(unsigned int i = 0; i < DataFile.size(); i++){
		for(unsigned int j = 0; j < DataFile.at(i).size(); j++){

			if ( DataFile.at(i).at(j).Vertex.x < Box.min.x ){
				Box.min.x = DataFile.at(i).at(j).Vertex.x;
			}
			if ( DataFile.at(i).at(j).Vertex.y < Box.min.y ){
				Box.min.y = DataFile.at(i).at(j).Vertex.y;
			}
			if ( DataFile.at(i).at(j).Vertex.z < Box.min.z ){
				Box.min.z = DataFile.at(i).at(j).Vertex.z;
			}

			if ( Box.max.x < DataFile.at(i).at(j).Vertex.x ){
				Box.max.x = DataFile.at(i).at(j).Vertex.x;
			}
			if ( Box.max.y < DataFile.at(i).at(j).Vertex.y ){
				Box.max.y = DataFile.at(i).at(j).Vertex.y;
			}
			if ( Box.max.z < DataFile.at(i).at(j).Vertex.z ){
				Box.max.z = DataFile.at(i).at(j).Vertex.z;
			}
		}
	}
	
	Box.dimensions.x = Box.max.x - Box.min.x;
	Box.dimensions.y = Box.max.y - Box.min.y;
	Box.dimensions.z = Box.max.z - Box.min.z; 
	return Box;
}

///////////////////////////////////////////////////////
// The plain is defined as P(u,v) = Po + ua + vb
//	The plain is parallel to the plain xz so a and b are unitary vectors on x and z
// Po is placed with coordinates minX and minZ from teh containing box.
// y is maxY + the side of the containing box
///////////////////////////////////////////////////////

void zebraPattern::getLightPlain ( CBox Box ){

	vecMath Vectors;
	//vector a
	Plane.a.Vertex.x = 1; Plane.a.Vertex.y = 0; Plane.a.Vertex.z = 0; 

	//vector b
	Plane.b.Vertex.x = 0; Plane.b.Vertex.y = 0; Plane.b.Vertex.z = 1; 
	//Po
	Plane.Po.Vertex.x = Box.min.x; Plane.Po.Vertex.z = Box.min.z;
	Plane.Po.Vertex.y = Box.max.y + Box.dimensions.y;

	Plane.stripWidth = Box.dimensions.z * STRIP_FACTOR;
}

std::vector<Vertice> zebraPattern::getNormal ( Vertice ActualPoint ){
	std::vector<Vertice> Normal;

	return Normal;
}

bool zebraPattern::getNodeColor ( Vertice ActualPoint ){
	bool Color; 
	return Color; 
}

  
void zebraPattern::printData ( void ){

	//std::cout << "The contents of fifth are:\n";
	//vector<vector<vecMath>>::iterator row;
	//vector<vecMath>::iterator colum;

	//for (	row = DataFile.begin(); row < DataFile.end(); row++ ){
	//	for (	colum = (*row).begin();	colum != (*row).end(); colum++ ){
	//		std::cout<< (*colum).Vertex.x;
	//	}
	//	std::cout<<'\n';
	//}

	std::cout<< "DataFile\n";
	for(unsigned int i = 0; i < DataFile.size(); i++){
		for(unsigned int j = 0; j < DataFile.at(i).size(); j++){
			std::cout<<DataFile.at(i).at(j).Vertex.x;
		}
		std::cout<<'\n';
	}

	std::cout<< "Plane: ";
	std::cout<<Plane.a.Vertex.x <<" " <<Plane.a.Vertex.y <<" " <<Plane.a.Vertex.z <<" - ";
	std::cout<<Plane.b.Vertex.x <<" " <<Plane.b.Vertex.y <<" " <<Plane.b.Vertex.z <<" - ";
	std::cout<<Plane.Po.Vertex.x <<" " <<Plane.Po.Vertex.y <<" " <<Plane.Po.Vertex.z <<" - ";
	cout<< Plane.stripWidth;
	cout << '\n';
}

