
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <iomanip>


std::string ParArg(int argc, char const *argv[], std::string ObsInfo[20]){
	
	std::string arv;
	for (int i = 1; i < argc; ++i)
	{
		arv = argv[i];

		if (arv.substr(0,6)=="-input")
		{	
			std::cout << "Locale Vstup >>" << arv.substr( 7 , arv.length()-7) <<std::endl;
			return arv.substr( 7 , arv.length()-7);
		}
		if (arv.substr(0,7)=="http://")
		{	
			std::cout << "Remote Input >>" << arv <<std::endl;
			ObsInfo[14]="BolidozorOnline";
			ObsInfo[13]=arv;
			return arv;
		}
	}
	
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) { 
	size_t written; 
	written = fwrite(ptr, size, nmemb, stream);
	return written; 
} 


int GetObsInfo(std::string ObsInfo[20], int hcount[]){
	int datatyp;
	datatyp = 0; // 0-neni urcene, 1-Speclab, 2-RadObs
	std::string url = ObsInfo[13]+"rmob.cfg";
	std::cout << "rmob.cfg parsing " << url << std::endl;
	CURL *curl;
	CURLcode res;
	std::string readBuffer = "";
 
	curl = curl_easy_init();
	if(curl) {
		FILE * fp;
		fp = fopen(".tmp","w"); 
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); 
		res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		fclose(fp);
	}
	std::string Poradi[15] = {"stationname", "country", "city", "antenna", "preamp", "reciver", "computer", "latitudedeg", "longtitudedeg", "latitudens", "longtitudeew", "frequency", "email"};
	std::string line;
	std::ifstream myfile (".tmp");
	if (myfile.is_open())
	{
		while (getline (myfile,line))
		{
			//std::cout << line << "|  |" << line.substr(0,line.find("=")-1) << "|  |" << line.substr(line.find("=")+2,line.length()-line.find("=")+2)<<'\n';
			//line.find("=");
			if (line.find("=") != std::string::npos)
			{
				for (int i = 0; i < 15; ++i)
				{
					if (Poradi[i].compare(line.substr(0,line.find("=")-1)) == 0)
					{
					    ObsInfo[i] = line.substr((line.find("=")+2), (line.length()-line.find("=")+2));
					    std::cout << "SHODA " << i << ":  " << ObsInfo[i] << std::endl;
						//ObsInfo[i] = line.substr(5, 5);
					}
				}
			}

		}
		myfile.close();
	}

	std::stringstream ss;
	std::stringstream ssRadObs;

	time_t rawtime;
	struct tm * utc;

	time ( &rawtime );
	utc = gmtime ( &rawtime );

	for (int i = 0; i < 744; ++i)
	{
		hcount[i]=1111; // Black
	}


	std::cout << "UTC čas je " << utc->tm_hour << " hodin a " << utc->tm_min << " minut. den je " << utc->tm_yday << std::endl;

	int r = utc->tm_year+1900;


	for (int y = 0; y < 31; ++y)			// den
	{
	for (int z = 0; z < 24; ++z)			// hodina
	{

		int numOfChar = 0;


		line="";
		ss.str("");

		ss << utc->tm_year+1900 << "/";

		if (utc->tm_mon+1 < 10)
		{
			ss << "0" << utc->tm_mon+1;
		}else{
			ss << utc->tm_mon+1;
		}
		ss << "/";

		if (y+1 < 10)
		{
			ss << "0" << y+1;
		}else{
			ss << y+1;
		}
		ss << "/";

		ss << utc->tm_year+1900;

		if (utc->tm_mon+1 < 10)
		{
			ss << "0" << utc->tm_mon+1;
		}else{
			ss << utc->tm_mon+1;
		}

		if (y+1 < 10)
		{
			ss << "0" << y+1;
		}else{
			ss << y+1;
		}
		
		ss	<< std::setw(2)<<std::setfill('0') << z
			<< "_"
			<< ObsInfo[0]
			<< ".dat";

		line="";
		ssRadObs.str("");

		ssRadObs << utc->tm_year+1900 << "/";

		if (utc->tm_mon+1 < 10)
		{
			ssRadObs << "0" << utc->tm_mon+1;
		}else{
			ssRadObs << utc->tm_mon+1;
		}
		ssRadObs << "/";

		if (y+1 < 10)
		{
			ssRadObs << "0" << y+1;
		}else{
			ssRadObs << y+1;
		}
		ssRadObs << "/";

		ssRadObs << utc->tm_year+1900;

		if (utc->tm_mon+1 < 10)
		{
			ssRadObs << "0" << utc->tm_mon+1;
		}else{
			ssRadObs << utc->tm_mon+1;
		}

		if (y+1 < 10)
		{
			ssRadObs << "0" << y+1;
		}else{
			ssRadObs << y+1;
		}
		
		ssRadObs	<< std::setw(2)<<std::setfill('0') << z
			<< "0000_"
			<< ObsInfo[0]
			<< "_meta.csv";

		//	RPath = ObsInfo[13] + ss.str();
		if (datatyp == 1 || datatyp ==0)
		{
			url = ObsInfo[13] + "data/" + ss.str();
			curl = curl_easy_init();
			if(curl) {
				FILE * fp;
				fp = fopen(".tmp","w"); 
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); 
				res = curl_easy_perform(curl);

				curl_easy_cleanup(curl);
				fclose(fp);
			}

			std::ifstream myfile (".tmp");

			if (myfile.is_open())
			{
				
				hcount[y*24 + z] = 0;
				std::cout << "File exist ";
				while (getline (myfile,line))
				{
					if (line.find("404 Not Found") != std::string::npos)
					{
						std::cout << "File is NOT on server ";
						hcount[y*24 + z] = 1111;
						break;
					}

					if (line.find("_met;") != std::string::npos) {
						hcount[y*24 + z] ++;
						datatyp=1;
					}

					if (line.find("_fb") != std::string::npos) {
						hcount[y*24 + z] ++;
						datatyp=1;
					}

				}
				std::cout << "hodina " << y*24 + z<< "; pocet " << hcount[y*24 + z] << "; ";
				myfile.close();
			}
			else
			{
				std::cout << "Nelze otevrit SpecLab soubor; ";
			}
		}
		if (datatyp == 2 || datatyp == 0)
		{
			url = ObsInfo[13] + "data/" + ssRadObs.str();
			std::cout << ObsInfo[13] + "data/" + ssRadObs.str();
			curl = curl_easy_init();
			if(curl) {
				FILE * fp;
				fp = fopen(".tmp","w"); 
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); 
				curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); 
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); 
				res = curl_easy_perform(curl);

				curl_easy_cleanup(curl);
				fclose(fp);

				std::ifstream myfile (".tmp");

				if (myfile.is_open())
				{
					
					hcount[y*24 + z] = 0;
					std::cout << "File RadObs exist ";
					while (getline (myfile,line))
					{
						if (line.find("404 Not Found") != std::string::npos)
						{
							std::cout << "File is NOT on server ";
							hcount[y*24 + z] = 1111;
							break;
						}

						if (line.find("_met.fits") != std::string::npos) {
							hcount[y*24 + z] ++;
							datatyp=2;
						}
					}
					std::cout << "hodina " << y*24 + z<< "; pocet " << hcount[y*24 + z] << "; ";
					myfile.close();
				}
				else
				{
					std::cout << "Nelze otevrit RadObs soubor; ";
				}
			}
		}

		std::cout << ObsInfo[13] << ss.str() << std::endl;

	}	// konec hodina
	}	// konec mesic
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
			std::cout <<line<<" - "<< value<<""<<std::endl;
			data[line]=value;
			line++;
		}
	}
}

void ParRmobFile(int hcount[], std::string ObsInfo[20]){

	for (int i = 0; i < 744; ++i)
	{
		hcount[i]=1111; // Black
	}

	int him =0;
	std::stringstream ident;

	//time_t now = time(0);
	//tm *ltm = localtime(&now);

	

	time_t rawtime;
	struct tm * utc;
	
	time ( &rawtime );
	utc = gmtime ( &rawtime );

	std::stringstream year;
	year << utc->tm_year+ 1900;

	std::stringstream month;
	if ((utc->tm_mon + 1) << 10)
	{
		month << "0" << utc->tm_mon + 1;
	}else
	{
	month << utc->tm_mon + 1;
	}



	std::string RelPath;
	RelPath = ObsInfo[13] + "RMOB-" + year.str() + month.str() + ".dat";

	std::cout<< "Cesta k souboru:" << RelPath << std::endl;

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


void ParBolidozorFile(int hcount[], std::string ObsInfo[20]){

	std::string RPath;
	std::stringstream ss;
	std::string line;

	time_t rawtime;
	struct tm * utc;

	time ( &rawtime );
	utc = gmtime ( &rawtime );

	for (int i = 0; i < 744; ++i)
	{
		hcount[i]=1111; // Black
	}


	std::cout << "UTC čas je " << utc->tm_hour << " hodin a " << utc->tm_min << " minut. den je " << utc->tm_yday << std::endl;


	for (int x = 0; x < utc->tm_mon+1; ++x)	// mesic
	{
	for (int y = 0; y < 32; ++y)			// den
	{
	for (int z = 0; z < 24; ++z)			// hodina
	{



		line="";
		ss.str("");
		ss << ObsInfo[15]
			<< utc->tm_year+1900;
		ss << std::setw(2)<<std::setfill('0')<<x+1
			<< std::setw(2)<<std::setfill('0')<<y+1
			<< std::setw(2)<<std::setfill('0')<<z
			<< ".dat";

		RPath = ObsInfo[13] + ss.str();

		std::ifstream myfile (RPath.c_str());
		if (x+1 == utc->tm_mon+1)
		{
			if (myfile.is_open())
			{
				hcount[y*24 + z] = 0;
				std::cout << "File exist ";
				while ( getline (myfile,line) )
				{
					if (line.substr(17,6)!="no_met")
					{
						hcount[y*24 + z] ++;
					}
				}
				std::cout << "hodina" <<y*24 + z<< "-" << hcount[y*24 + z] << " ";
				myfile.close();
			}
		}
		else
		{
			std::cout << "File is NOT exist ";
		}

		std::cout << ObsInfo[13] << ss.str() << std::endl;

	}	// konec hodina
	}	// konec mesic
	}	// konec rok
}

void ParBolidozor14File(int hcount[], std::string ObsInfo[20]){

	std::string RPath;
	std::stringstream ss;
	std::string line;

	time_t rawtime;
	struct tm * utc;

	time ( &rawtime );
	utc = gmtime ( &rawtime );

	for (int i = 0; i < 744; ++i)
	{
		hcount[i]=1111; // Black
	}


	std::cout << "UTC čas je " << utc->tm_hour << " hodin a " << utc->tm_min << " minut. den je " << utc->tm_yday << std::endl;

	int r = utc->tm_year+1900;

	for (int y = 0; y < 32; ++y)			// den
	{
	for (int z = 0; z < 24; ++z)			// hodina
	{



int numOfChar = 0;


		line="";
		ss.str("");

		ss << utc->tm_year+1900 << "/";

		if (utc->tm_mon+1 < 10)
		{
			ss << "0" << utc->tm_mon+1;
		}else{
			ss << utc->tm_mon+1;
		}
		ss << "/";

		if (y+1 < 10)
		{
			ss << "0" << y+1;
		}else{
			ss << y+1;
		}
		ss << "/";

		ss << utc->tm_year+1900;

		if (utc->tm_mon+1 < 10)
		{
			ss << "0" << utc->tm_mon+1;
		}else{
			ss << utc->tm_mon+1;
		}

		if (y+1 < 10)
		{
			ss << "0" << y+1;
		}else{
			ss << y+1;
		}
		
		ss	<< std::setw(2)<<std::setfill('0') << z
			<< "_"
			<< ObsInfo[15]
			<< ".dat";

		RPath = ObsInfo[13] + ss.str();

		std::ifstream myfile (RPath.c_str());

		if (utc->tm_mon == utc->tm_mon)
		{
			if (myfile.is_open())
			{
				hcount[y*24 + z] = 0;
				std::cout << "File exist ";
				while ( getline (myfile,line) )
				{

					if (line.find("_met") != std::string::npos) {
						hcount[y*24 + z] ++;
					}

					if (line.find("_fb") != std::string::npos) {
						hcount[y*24 + z] ++;
					}

				}
				std::cout << "hodina " << y*24 + z<< "; pocet " << hcount[y*24 + z] << "; ";
				myfile.close();
			}
			else
			{
				std::cout << "File is NOT exist ";
			}
		}
		

		std::cout << ObsInfo[13] << ss.str() << std::endl;

	}	// konec hodina
	}	// konec mesic
}

/*
void ParMySQL(int hcount[]){

	std::ifstream file ("./io/SqlAccess.in");
	std::string value;
	std::string SQLconf[3];
	int line = 0;

	while ( file.good() )
	{
		getline ( file, value);
		if (value!="" && value!="#" && value.substr(0,1)!="#")
		{
			std::cout <<line<<" - "<< value<<""<<std::endl;
			SQLconf[line] = value;
			line++;
		}
	}

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	//char *server = SQLconf[1].str();
	//char *user = SQLconf[2].c_str();
	//char *password = SQLconf[3].c_str();
	//char *database = SQLconf[4].c_str();


	const char *server = "localhost";
	const char *user = "root";
	const char *password = "heslo";
	const char *database = "Bolidozor";


	conn = mysql_init(NULL);

	// Pripojeni
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	// MySQL dotaz
	if (mysql_query(conn, "show tables"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	//tabulka
	printf("tabulek: \n");
	while ((row = mysql_fetch_row(res)) != NULL)
	printf("%s \n", row[0]);

	// ukoncit pripojeni
	mysql_free_result(res);
	mysql_close(conn);

}*/