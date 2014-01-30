#ifndef _SVGGEN_H
#define _SVGGEN_H

int SvgColRed(int num);

int SvgColBlue(int num);

int SvgColGreen(int num);

std::string SvgColAll(int max, int min, int actual);

std::string SvgColAll_new(int max, int min, int actual);

int SvgGen(std::string svginfo[15], int hourcount[745]);

int SvgPng(std::string path);

int SvgJpg(std::string path, std::string svginfo[15]);

void TxtGen(std::string svginfo[15], int hourcount[745],std::string path);

#include "SvgGen.c"
#endif