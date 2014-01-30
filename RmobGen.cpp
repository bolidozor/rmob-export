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
#include <mysql/mysql.h>


#include "incl/SvgGen.h"
#include "incl/Parser.h"

using namespace std;

int main(int argc, char const *argv[]){

	string ObsInfo[16];
	int HourCount[745];

	for (int i = 0; i < 745; ++i)
	{
		HourCount[i]=0;
	}


	ParArgB(argc, argv);

	ParObsInfo(ObsInfo, ParArg(argc, argv));

	if(ObsInfo[14] == "Bolidozor_14"){
		ParBolidozor14File(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);

	}
	if (ObsInfo[14] == "Bolidozor")
	{
		ParBolidozorFile(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);
	}
	if (ObsInfo[14] == "Rmob")
	{
		ParRmobFile(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);
	}
	if (ObsInfo[14] == "MySQL")
	{
		ParMySQL(HourCount);
	}


	//ParBolidozorFile(HourCount,ObsInfo[15]);
	//ParRmobFile(HourCount,ObsInfo[15]);

	//SvgPng("./io/");

	return 0;
}
