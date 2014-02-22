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

	string ObsInfo[16] = {""};
	int HourCount[745] = {0};

	ParArgB(argc, argv);

	ParObsInfo(ObsInfo, ParArg(argc, argv));

	if(ObsInfo[14].compare("Bolidozor_14") == 0)
	{
		ParBolidozor14File(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);

	}
	if (ObsInfo[14].compare("Bolidozor") == 0)
	{
		ParBolidozorFile(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);
	}
	if (ObsInfo[14].compare("Rmob") == 0)
	{
		ParRmobFile(HourCount,ObsInfo);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);
	}
	if (ObsInfo[14].compare("MySQL") == 0)
	{
		ParMySQL(HourCount);
	}


	//ParBolidozorFile(HourCount,ObsInfo[15]);
	//ParRmobFile(HourCount,ObsInfo[15]);

	//SvgPng("./io/");

	return 0;
}
