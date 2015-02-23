#include "StdAfx.h"
#include "zebraPattern.h"
#include "vecMath.h"

#include <fstream>
#include <sstream>

//enum LightColor {
//	GRAY 
//}

using namespace std;

vector<vector<vecMath>> DataFile;  //This data is arrenged as a matrix 

zebraPattern::zebraPattern( string fileN )
{
	fileName = fileN;
	readData();
	getContainingBox();
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


std::vector<Vertice> zebraPattern::getContainingBox ( void ){
	
	//Vector 0 for min values
	//Vector 1 for max values
	//Vector 2 for dimentions of the bounding box
	std::vector<Vertice> ContainingBox(3);
 
	for(int i = 0; i < DataFile.size(); i++){
		for(int j = 0; j < DataFile.at(i).size(); j++){

			if ( DataFile.at(i).at(j).Vertex.x < ContainingBox[0].x ){
				ContainingBox[0].x = DataFile.at(i).at(j).Vertex.x;
			}
			if ( DataFile.at(i).at(j).Vertex.y < ContainingBox[0].y ){
				ContainingBox[0].y = DataFile.at(i).at(j).Vertex.y;
			}
			if ( DataFile.at(i).at(j).Vertex.z < ContainingBox[0].z ){
				ContainingBox[0].z = DataFile.at(i).at(j).Vertex.z;
			}

			if ( ContainingBox[1].x < DataFile.at(i).at(j).Vertex.x ){
				ContainingBox[1].x = DataFile.at(i).at(j).Vertex.x;
			}
			if ( ContainingBox[1].y < DataFile.at(i).at(j).Vertex.y ){
				ContainingBox[1].y = DataFile.at(i).at(j).Vertex.y;
			}
			if ( ContainingBox[1].z < DataFile.at(i).at(j).Vertex.z ){
				ContainingBox[1].z = DataFile.at(i).at(j).Vertex.z;
			}
		}
	}
	
	ContainingBox[2].x = ContainingBox[1].x - ContainingBox[0].x;
	ContainingBox[2].y = ContainingBox[1].y - ContainingBox[0].y; 
	ContainingBox[2].z = ContainingBox[1].z - ContainingBox[0].z; 
	return ContainingBox;
}

void getLightPlain ( void ){

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
	for(int i = 0; i < DataFile.size(); i++){
		for(int j = 0; j < DataFile.at(i).size(); j++){
			std::cout<<DataFile.at(i).at(j).Vertex.x;
		}
		std::cout<<'\n';
	}
}

