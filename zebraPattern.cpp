#include "StdAfx.h"
#include "zebraPattern.h"
#include "vecMath.h"

//#using <mscorlib.dll>
//#using <System.dll>
#include <fstream>
#include <sstream>

#include <iostream>

#define STRIP_FACTOR 0.1
#define B_FACTOR		0.9
#define NORMAL_RANGE 3

using namespace std;
//using namespace System;

struct LightPlane{
   vecMath a;
   vecMath b;
   vecMath Po;
	float	  stripWidth;
}Plane;

enum Color{
	C_BLACK,	
	C_GREY,	
	C_WHITE,	
};

vector<vector<vecMath>> DataFile;  //This data is arrenged as a matrix
vector<vector<bool>>	Color;
Vertice Eye;

zebraPattern::zebraPattern( string fileN )
{
	vecMath Normal;
	Vertice v, P, aCrossb;
	vector<bool>colColor;

	cout << "The .vrl is being generated\n";

	fileName = fileN;
	readData();
	getLightPlain(getContainingBox());
	aCrossb = crossProduct(Plane.a.Vertex, Plane.b.Vertex);

	for(unsigned int i = 0; i < DataFile.size(); i++){
		for(unsigned int j = 0; j < DataFile.at(i).size(); j++){
			Normal = getNormal ( i, j );

			/*
				Q(t) = P + tv  where
				v = 2(Eye - ActualPoint)UniNormal UniNormal
			*/
			v = multiScalar(	dotProduct( multiScalar(2.0, 
																	sub(Eye , DataFile[i][j].Vertex) ), 
													Normal.unitVector()), 
									Normal.unitVector() 
								);

			/*
				P(u,v) = Po + ua + vb
				where: 
					Po = Plane.Po	a = Plane.a b = Plane.b

					Finding where the line and plane intersecs:

										 (Plane.Po - ActualPoint)(a x b)
				P = ActualPoint -  -------------------------------  v
													v ( a x b )
			
			*/
			P = add( DataFile[i][j].Vertex,
						multiScalar( dotProduct( sub(Plane.Po.Vertex,DataFile[i][j].Vertex),aCrossb) / 
										 dotProduct(v,aCrossb),
										 v));

			colColor.push_back(getNodeColor(P));
		}
		Color.push_back(colColor);
		colColor.clear();
	}
	//printData();

	createVRML();
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
	Plane.Po.Vertex.x = Box.min.x; 
	Plane.Po.Vertex.y = Box.max.y + Box.dimensions.y;
	Plane.Po.Vertex.z = Box.min.z;

	Plane.stripWidth = Box.dimensions.z * STRIP_FACTOR;

	Eye.x = Box.min.x;
	Eye.y = Box.min.y - Box.dimensions.y; 
	Eye.z = Box.min.z; 
}

// The normals could be positive or negative, the important part is to get the unit vector 
// in order to 
vecMath zebraPattern::getNormal ( int row, int col ){
	vecMath Normal,proxNorm;
	Normal.Vertex.x = 0; Normal.Vertex.y = 0; Normal.Vertex.z = 0;

	for ( int i = row - NORMAL_RANGE; i < row + NORMAL_RANGE; i++)
	{
		for ( int j = col - NORMAL_RANGE; j < col + NORMAL_RANGE; j++)
		{
			if ( i < 0 ){
				i = 0; j = 0;
			}
			if ( j < 0 ){
				j = 0;
			}

			if ( i < DataFile.size()-1 && j < DataFile.at(i).size()-1){
				proxNorm.Vertex = crossProduct( sub(DataFile[i][j+1].Vertex , DataFile[i][j].Vertex),
														  sub(DataFile[i+1][j].Vertex , DataFile[i][j].Vertex));
				Normal.Vertex.x = ( Normal.Vertex.x + proxNorm.Vertex.x) / 2;
				Normal.Vertex.y = ( Normal.Vertex.y + proxNorm.Vertex.y) / 2;
				Normal.Vertex.z = ( Normal.Vertex.z + proxNorm.Vertex.z) / 2;
			}
		}
	}
	return Normal;
}

bool zebraPattern::getNodeColor ( Vertice InterPoint ){
	bool IsBlack = false;
	if ( fmod(InterPoint.y,Plane.stripWidth) < Plane.stripWidth*B_FACTOR ){
		IsBlack = true;
	} 
	return IsBlack;
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
			std::cout<<DataFile.at(i).at(j).Vertex.x<<" " <<DataFile.at(i).at(j).Vertex.y <<" " <<DataFile.at(i).at(j).Vertex.z <<" - ";;
		}
		std::cout<<'\n';
	}

	std::cout<< "Plane: ";
	std::cout<<Plane.a.Vertex.x <<" " <<Plane.a.Vertex.y <<" " <<Plane.a.Vertex.z <<" - ";
	std::cout<<Plane.b.Vertex.x <<" " <<Plane.b.Vertex.y <<" " <<Plane.b.Vertex.z <<" - ";
	std::cout<<Plane.Po.Vertex.x <<" " <<Plane.Po.Vertex.y <<" " <<Plane.Po.Vertex.z <<" - ";
	cout<< Plane.stripWidth;
	cout << '\n';

	std::cout<< "Color\n";
	for(unsigned int i = 0; i < Color.size(); i++){
		for(unsigned int j = 0; j < Color.at(i).size(); j++){
			std::cout<<Color.at(i).at(j) <<" ";
		}
		std::cout<<'\n';
	}
}

//#include "StdAfx.h"
//#include "Export.h"
//#using <mscorlib.dll>
////#include "Utils.h"
////#include "vecMath"
////#include <iostream>
////#include <vector>
//
////using namespace std;
//using namespace System;

void zebraPattern::createVRML ( void ){

	vector<vector<int>> Faces;
	vector<int> face;

	std::ofstream outfile ("Surface.wrl");
	outfile << "#VRML V2.0 utf8" << std::endl;
	outfile << "#" << std::endl;
	outfile << "Surface by Javier Chauvin" << std::endl<< std::endl<< std::endl;
	outfile << "	Shape{" << std::endl;
	outfile << "		geometry IndexedFaceSet{" << std::endl;
	outfile << "			coord Coordinate{" << std::endl;
	outfile << "				point[";
	
	//print the points

	for(unsigned int i = 0; i < DataFile.size(); i++){
		for(unsigned int j = 0; j < DataFile.at(i).size(); j++){
			outfile << DataFile[i][j].Vertex.x;
			outfile <<" ";
			outfile <<  DataFile[i][j].Vertex.y;
			outfile <<" ";
			outfile << DataFile[i][j].Vertex.z<<","<< std::endl;

			//sub(DataFile[i][j+1].Vertex , DataFile[i][j].Vertex),
			//sub(DataFile[i+1][j].Vertex , DataFile[i][j].Vertex));

			if ( i < DataFile.size()-1 && j < DataFile.at(i).size()-1 ){
				int l, k;
				l=i;	k=j;		face.push_back(l*DataFile.size()+k);   
				l=i;	k=j+1;	face.push_back(l*DataFile.size()+k);
				l=i+1;k=j+1;	face.push_back(l*DataFile.size()+k);
				l=i+1;k=j;		face.push_back(l*DataFile.size()+k);
				Faces.push_back(face);
				face.clear();
			}
		}
	}
	outfile << "						]" << std::endl;
	outfile << "			}" << std::endl;

	outfile << "			coordIndex[";

	for(unsigned int i = 0; i < Faces.size(); i++){
		//outfile << "						"<< std::endl;
		for(unsigned int j = 0; j < Faces.at(i).size(); j++){
			outfile << Faces[i][j];
			outfile <<", ";
		}
		outfile <<"-1,"<< std::endl;
	}
	outfile << "						 ]" << std::endl;

	outfile << "			color Color{" << std::endl;
	outfile << "				color[ 1 1 1, 0 0 0 ]" << std::endl;
	outfile << "			}" << std::endl;

	outfile << "			colorIndex["<< std::endl;
	for(unsigned int i = 0; i < Color.size(); i++){
		//outfile << "						";
		for(unsigned int j = 0; j < Color.at(i).size(); j++){
			outfile << Color[i][j]<<", "<< std::endl;
		}
	}
	outfile << "						 ]" << std::endl;

	outfile << "			Solid FALSE" << std::endl;
	outfile << "	}" << std::endl;
	outfile << "}" << std::endl;

	cout << "The .wlr file was created\n";
}
