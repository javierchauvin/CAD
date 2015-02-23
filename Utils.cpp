//This file contains all the utility functions

#include "StdAfx.h"
#include "Utils.h"

#include <iterator>
#include <sstream>

using namespace std;

std::vector<std::string> split (std::string line){
	std::vector<string> tokens; 
	copy(	istream_iterator<string>(istringstream(line)),
			istream_iterator<string>(),
			back_inserter(tokens));
	return tokens;
}

//Just transforms a vector of string into a vector of int.
std::vector<int> vectorStringToInt ( std::vector<string>tokens )
{
	std::vector<int> TransformedTokens (tokens.size());

	if (!tokens.empty())
	{
		for (int i = 0 ; i<int(tokens.size()) ; i++){
			TransformedTokens[i] = std::stoi(tokens[i]);
		}
	} else {
		cout << "transformToInt has received an empty vector\n";	
	}
	return TransformedTokens;
}

//Receives the tokens in a string vector, translate them to float and store the coordinates on vertice 
Vertice vectorStringToVertice ( vector<string>tokens ){
	Vertice TransformedTokens;
	if (!tokens.empty())
	{
		TransformedTokens.x = std::stof(tokens[0]);
		TransformedTokens.y = std::stof(tokens[1]);
		TransformedTokens.z = std::stof(tokens[2]);
	}
	return TransformedTokens;
}
