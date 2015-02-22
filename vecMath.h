#pragma once

union Vertice {
	float m_vVec[3];
	struct {
			float x;
			float y;
			float z;
	};
};

class vecMath
{
	Vertice Vertex;
	vecMath() {};
public:
	vecMath(Vertice newPoint);
	~vecMath();

	float magnitude ();
	Vertice unitVector ();
};



