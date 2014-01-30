#ifndef _PARSER_H
#define _PARSER_H


std::string ParArg(int argc, char const *argv[]);

std::string ParArgB(int argc, char const *argv[]);

void ParObsInfo(std::string data[], std::string path);

void ParRmobFile(int hcount[], std::string ObsInfo[20]);

void ParBolidozorFile(int hcount[], std::string ObsInfo[20]);

void ParBolidozor14File(int hcount[], std::string ObsInfo[20]);

void ParMySQL(int hcount[]);

#endif