#include "StdAfx.h"
#include "Bezier.h"
#include <fstream>

enum AxisName{
	X,
	Y,
	Z,
};

//Bezier::Bezier ( void/*vector<vector<vecMath>> curves*/ ){
//	drawCurves();
//	cout << "Inside the brezier \n";
//}

void Bezier::getTangentColor( void ){
	Bezier::numberOfTangents = 20;

	int total = 255;
	int R = 0, G = total, B = 0;

	vector<int> oneColor (3);

	for (int i = 0; i<numberOfTangents; i++){

		if (total/numberOfTangents < G){
			G -= total/numberOfTangents;
		}
		if (B < total ){
			B += total/numberOfTangents;
		}
		oneColor[0] = R;
		oneColor[1] = G;
		oneColor[2] = B;
		Colors.push_back(oneColor);
	}

	for (int i=0; i<numberOfTangents; i++){
		cout<< Colors[i][0] <<" "<< Colors[i][1] <<" "<< Colors[i][2] <<"\n";
	}

}

void Bezier::drawCurves ( void ){
	
	cout << "Inside the brezier \n";
	//vector<vector<int>> Faces;
	//vector<int> face;

	//vector<vector<E_Color>> colorFaces;
	//vector<E_Color> colorface;

	cout<< "inside the drawing process \n";

	std::ofstream outfile ("Lines.wrl");
	outfile << "#VRML V2.0 utf8" << std::endl;
	outfile << "#" << std::endl;
	outfile << "#by Javier Chauvin" << std::endl<< std::endl<< std::endl;

	outfile << "Shape{" << std::endl;
	outfile << "	geometry IndexedLineSet{" << std::endl;
	outfile << "		coord Coordinate{" << std::endl;
	outfile << "			point[" << std::endl;
	outfile << "                0.0000  0.0000  0.000" << std::endl;
   outfile << "	             10.0000  10.0000  10.0000" << std::endl;
   outfile << "	             10.0000  10.0000  30.0000" << std::endl;
	outfile << "					]" << std::endl;
	outfile << "		}" << std::endl;

	outfile << "		coordIndex[" << std::endl;;

	outfile << "		            0   1   -1" << std::endl;    
   outfile << "						1   2   -1" << std::endl; 
   outfile << "						0   2   -1" << std::endl; 

	//for(unsigned int i = 0; i < Faces.size(); i++){
	//	outfile << "				  ";
	//	for(unsigned int j = 0; j < Faces.at(i).size(); j++){
	//		outfile << Faces[i][j];
	//		outfile <<", ";
	//	}
	//	outfile <<"-1,"<< std::endl;
	//}

	outfile << "					 ]" << std::endl;

	outfile << "		color Color{" << std::endl;
	outfile << "			color[" << std::endl;
	outfile << "               1.0000  0.0000  0.0000" << std::endl;
   outfile << "					0.0000  1.0000  0.0000" << std::endl;
   outfile << "					0.0000  0.0000  1.0000" << std::endl;
	outfile << "				  ]" << std::endl;
	outfile << "		}" << std::endl;

	//outfile << "		colorIndex[" << std::endl;;
	//for(unsigned int i = 0; i < colorFaces.size(); i++){
	//	outfile << "					";
	//	for(unsigned int j = 0; j < colorFaces.at(i).size(); j++){
	//		outfile << colorFaces[i][j];
	//		outfile <<", ";
	//	}
	//	outfile <<"-1,"<< std::endl;
	//}
	//outfile << "					 ]" << std::endl;

	//outfile << "		solid FALSE" << std::endl;
	outfile << "	}" << std::endl;
	outfile << "}" << std::endl;

for ( int i = 0; i < 3 ; i++){

outfile << "Shape" << std::endl;
outfile << "{" << std::endl;
outfile << "	geometry Extrusion" << std::endl;
outfile << "		{" << std::endl;

	switch (i)
	{
		case 0: 
			outfile << "		spine	  [	0 0 0, 24 0 0, 24 0 0, 28 0 0 ]" << std::endl; 
			break;
		case 1: 
			outfile << "		spine	  [	0 0 0, 0 24 0, 0 24 0, 0 28 0 ]" << std::endl; 
			break;
		case 2: 
			outfile << "		spine	  [	0 0 0, 0 0 24, 0 0 24, 0 0 28 ]" << std::endl; 
			break;
	}
outfile << "		crossSection [ 1 0, 0 1, -1 0, 0 -1, 1 0]" << std::endl;
outfile << "		scale	  [	0.1 0.1, 0.1 0.1, .4 .4, 0 0 ]" << std::endl;
outfile << "		}	" << std::endl;

outfile << "	appearance Appearance" << std::endl;
outfile << "	{" << std::endl;
outfile << "		material Material" << std::endl;
outfile << "		{" << std::endl;
outfile << "			diffuseColor 0 0 0" << std::endl;
outfile << "		}" << std::endl;
outfile << "	}" << std::endl;
outfile << "}" << std::endl;

}

for ( int i = 0; i < 3 ; i++){

	cout << i <<"\n";

	outfile << "	Transform" << std::endl;
	outfile << "	{" << std::endl;

	switch (i)
	{
		case 0: 
			outfile << "		translation 32 0 0" << std::endl; 
			break;
		case 1: 
			outfile << "		translation 0 32 0" << std::endl; 
			break;
		case 2: 
			outfile << "		translation 0 0 32" << std::endl; 
			break;
	}
	outfile << "		children Shape" << std::endl;
	outfile << "				{" << std::endl;
	outfile << "					geometry Text" << std::endl;
	outfile << "					{" << std::endl;

	switch (i){
		case 0: 
			outfile << "						string [ \" X \"]" << std::endl;
			break;
		case 1: 
			outfile << "						string [ \" Y \"]" << std::endl;
			break;
		case 2: 
			outfile << "						string [ \" Z \"]" << std::endl;
			break;
	}

	outfile << "						fontStyle FontStyle" << std::endl;
	outfile << "						{" << std::endl;
	outfile << "							family	\"SANS\" " << std::endl;
	outfile << "							justify	\"MIDDLE\" " << std::endl;
	outfile << "							style	\"BOLD\" " << std::endl;
	outfile << "							size 4 " << std::endl;
	outfile << "						} " << std::endl;
	outfile << "					} " << std::endl;

	outfile << "					appearance Appearance " << std::endl;
	outfile << "					{ " << std::endl;
	outfile << "						material Material " << std::endl;
	outfile << "						{ " << std::endl;
	outfile << "							diffuseColor 0 0 0" << std::endl;
	outfile << "						}" << std::endl;
	outfile << "					}" << std::endl;	
	outfile << "				}" << std::endl;
	outfile << "	}" << std::endl;
}

outfile << "NavigationInfo " << std::endl;
outfile << "{ " << std::endl;
outfile << "	type \"EXAMINE\" " << std::endl;
outfile << "} " << std::endl;

outfile << "Background "<< std::endl;
outfile << "{"<< std::endl;
outfile << "	skyColor 1 1 1 "<< std::endl; 
outfile << "} "<< std::endl;

	cout << "The .wlr file was created\n";
}

