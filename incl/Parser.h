
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <ctime>

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

void ParRmobFile(int hcount[], std::string RelPath){

	int him =0;
	std::stringstream ident;

	time_t now = time(0);  
	tm *ltm = localtime(&now);
	

	std::stringstream date;
	date << ltm->tm_year+ 1900;

	std::stringstream month;
	if ((ltm->tm_mon + 1) << 10)
	{
		month << "0"<< ltm->tm_mon + 1;
	}else{
		month << ltm->tm_mon + 1;
	}

	RelPath = RelPath + "RMOB-" + date.str() + month.str() + ".dat";
	char* den;
	char* hodina;
	char* hodnota;

	std::string line;
	std::ifstream myfile ("./../Spectrum/RMOB-201310.dat");
	
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			/*idnet << ltm->tm_year+ 1900;
			if ((ltm->tm_mon + 1) << 10)
			{
				idnet << "0"<< ltm->tm_mon + 1;
			}else{
				idnet << ltm->tm_mon + 1;
			}
			if( line.substr (0,10) == "")
			{
				std::cout<< "--" << line.substr(0,10) <<"-aaa  ";
			}*/


				//atoi(dob.substr(2,3).c_str());


		//	den = line.substr(6,2);
		//	hodina = line.substr(8,2);
		//	hodnota = line.substr(18,18-line.length());
			std::cout << line.substr(6,2) << ";" << line.substr(8,2) << ";" << line.substr(18,18-line.length()) << std::endl;
			
			hcount[atoi(line.substr(6,2).c_str())*atoi(line.substr(8,2).c_str())]=atoi(line.substr(18,18-line.length()).c_str());

			//std::cout << line << std::endl;
		}
		myfile.close();
	}
}