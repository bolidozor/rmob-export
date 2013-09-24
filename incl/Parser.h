
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>

void ParObsInfo(std::string data[]){

	std::ifstream file ( "io/Observatory.info" );
	
	std::string value;
	int line;
	line = 0;
	while ( file.good() )
	{
		getline ( file, value);
		if (value!="" && value!="#")
		{
			std::cout <<line<<"-"<< value<<""<<std::endl;
			data[line]=value;
			line++;
		}
		
	}

}