
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <iomanip>


std::string ParArg(int argc, char const *argv[]){
	
	std::string arv;
	for (int i = 1; i < argc; ++i)
	{
		arv = argv[i];

		if (arv.substr(0,6)=="-input")
		{	
			std::cout << "Vstup -- " << arv.substr( 7 , arv.length()-7) <<std::endl;
		}
	}
	return arv.substr( 7 , arv.length()-7);
}

void ParObsInfo(std::string data[], std::string path){

	std::ifstream file ( path.c_str() );
	std::string value;
	int line;
	line = 0;
	while ( file.good() )
	{
		getline ( file, value);
		if (value!="" && value!="#" && value.substr(0,1)!="#")
		{
			//std::cout <<line<<"-"<< value<<""<<std::endl;
			data[line]=value;
			line++;
		}
	}
}

void ParRmobFile(int hcount[], std::string RelPath){

	for (int i = 0; i < 744; ++i){
		hcount[i]=1111; // Black
	}

	int him =0;
	std::stringstream ident;

	time_t now = time(0);  
	tm *ltm = localtime(&now);

	std::stringstream date;
	date << ltm->tm_year+ 1900;

	std::stringstream month;
	//if ((ltm->tm_mon + 1) << 10)
	//{
	//	month << "0"<< ltm->tm_mon + 1;
	//}else{
		month << ltm->tm_mon + 1;
	//}

	RelPath = RelPath + "RMOB-" + date.str() + month.str() + ".dat";

	char* den;
	char* hodina;
	char* hodnota;

	std::string line;
	std::ifstream myfile (RelPath.c_str());
	
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			//std::cout << line.substr(6,2) << ";" << line.substr(8,2) << ";" << line.substr(18,18-line.length()) << std::endl;
			hcount[(atoi(line.substr(6,2).c_str())-1)*24 + atoi(line.substr(8,2).c_str())]=atoi(line.substr(18,18-line.length()).c_str());
		}
		myfile.close();
	}
}


void ParBolidozorFile(int hcount[], std::string RelPath){	

	std::string RPath;
	std::stringstream ss;
	std::string line;

	time_t rawtime;
  	struct tm * utc;

  	time ( &rawtime );
  	utc = gmtime ( &rawtime );

	for (int i = 0; i < 744; ++i){
		hcount[i]=1111; // Black
	}


  	std::cout << "UTC čas je " << utc->tm_hour << " hodin a " << utc->tm_min << " minut. den je " << utc->tm_yday << std::endl;

  	//// for (int i = 0; i < (utc->tm_hour+(24*utc->tm_mday-1)); ++i){
  	for (int x = 0; x < utc->tm_mon+1; ++x)	// mesic
  	{
  	for (int y = 0; y < 31; ++y)			// den
  	{
  	for (int z = 0; z < 24; ++z)			// hodina
  	{

  		

  		line="";
  		ss.str("");
  		ss << "ZVPP" 
  		   << utc->tm_year+1900;
  		ss << std::setw(2)<<std::setfill('0')<<x+1
  		   << std::setw(2)<<std::setfill('0')<<y+1
  		   << std::setw(2)<<std::setfill('0')<<z 
  		   << ".dat";


  		RPath = RelPath + ss.str();	

  		
		std::ifstream myfile (RPath.c_str());
		if (myfile.is_open()){
			hcount[y*24 + z] = 0;
			std::cout << "File exist ";
			while ( getline (myfile,line) ){
				
				if ( line.substr(17,6)!="no_met" )
				{
					hcount[y*24 + z] ++;
				}
				
			
			}
			std::cout << "hodina" <<y*24 + z<< "-" << hcount[y*24 + z] << " ";
			myfile.close();
		}
		else{
			std::cout << "File is NOT exist ";
		}

  		

  		std::cout << RelPath << ss.str() << std::endl;
  	//// }
  	}
	}
	}

}