//////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//		||||||||\	||\	   /||	//||||||\\	||||||\\		//||||||\\	||||||||	||\	   ||		//
//		||		||	||\\  //||	||		||	||	  ||		||			||			||\\   ||		//
//		||		||	|| \\// ||	||		||	||__ //			||			||____		|| \\  ||		//
//		||||||||<	||		||	||		||	||   \\			||	||||\\	||			||	\\ ||		//	
//		||	  \\	||		||	||		||	||    ||		||		||	||			||	 \\||		//
//		||	   \\	||		||	\\||||||//	||||||//		\\||||||//	||||||||	||	  \||		//
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Run whit -input parameter whit path to .info file as: ./RmobGen -input-./io/Observatory.info
//
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <Magick++.h>

#include "incl/SvgGen.h"
#include "incl/Parser.h"

using namespace std;

int main(int argc, char const *argv[]){

	string ObsInfo[13];
	int HourCount[744];


	for (int i = 0; i < 744; ++i){
		HourCount[i]=0;
	}


	ParObsInfo(ObsInfo, ParArg(argc, argv) );

	if (ObsInfo[12] == "Bolidozor")
	{
		ParBolidozorFile(HourCount,ObsInfo[11]);
	}
	if (ObsInfo[12] == "Rmob")
	{
		ParRmobFile(HourCount,ObsInfo[11]);
	}


	//ParBolidozorFile(HourCount,ObsInfo[12]);
	//ParRmobFile(HourCount,ObsInfo[12]);
	TxtGen(ObsInfo,HourCount);
	SvgGen(ObsInfo,HourCount);


	for (int i = 0; i < 743; ++i){
		//HourCount[i] = rand() % 100;
		//cout<<i<<" - " << HourCount[i] << endl;
		//HourCount[i]=0;
	}

	SvgPng("./io/");
	SvgJpg("./io/");
	return 0;
}
