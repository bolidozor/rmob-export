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


	std::cout << ObsInfo[1] << std::endl;
	std::cout << ObsInfo[2] << std::endl;


	for (int i = 0; i < 743; ++i){
		//HourCount[i] = rand() % 100;
		//cout<< HourCount[i]<<endl;
		HourCount[i]=0;
	}

	ParObsInfo(ObsInfo);
	ParRmobFile(HourCount,ObsInfo[11]);
	SvgGen(ObsInfo,HourCount);
	SvgPng("./io/");

	return 0;
}