

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <Magick++.h>

#include "incl/SvgGen.h"
#include "incl/Parser.h"

using namespace std;


int main(int argc, char const *argv[]){

	string ObsInfo[11];
	int HourCount[744];

	ObsInfo[0]	=	"obs";
	ObsInfo[1]	=	"Czech republic";
	ObsInfo[2]	=	"City";
	ObsInfo[3]	=	"Ant";
	ObsInfo[4]	=	"LNA";
	ObsInfo[5]	=	"SDR";
	ObsInfo[6]	=	"computer";
	ObsInfo[7]	=	"lat";
	ObsInfo[8]	=	"lon";
	ObsInfo[9]	=	"143 050 000 Hz";
	ObsInfo[10]	=	"email@email.xx";


	std::cout << ObsInfo[1] << std::endl;
	std::cout << ObsInfo[2] << std::endl;


	for (int i = 0; i < 743; ++i)
	{
		HourCount[i] = rand() % 100;
		cout<< HourCount[i]<<endl;
	}

	ParObsInfo(ObsInfo);
	SvgGen(ObsInfo,HourCount);

	Magick::Image svgImage("./io/rmob.svg");
	svgImage.magick("png");
	svgImage.write("./io/rmob.png");

	return 0;
}