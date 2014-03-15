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
#include <curl/curl.h>

#include "incl/SvgGen.h"
#include "incl/Parser.h"

using namespace std;

int main(int argc, char const *argv[]){

	string ObsInfo[16] = {""};
	int HourCount[745] = {0};

	ParArg(argc, argv, ObsInfo);

	if (ObsInfo[14].compare("BolidozorOnline") == 0)
	{
		std::cout <<"----------------"<<std::endl;
		GetObsInfo(ObsInfo,HourCount);
		TxtGen(ObsInfo,HourCount, "./io/gen/");
		SvgGen(ObsInfo,HourCount);
		SvgJpg("./io/gen/",ObsInfo);
	}else
	{
		ParObsInfo(ObsInfo, ParArg(argc, argv, ObsInfo));
	}

	if (ObsInfo[14].compare("Bolidozor_14") == 0)
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

	return 0;
}
