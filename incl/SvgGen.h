#include <iostream>
#include <fstream>
#include <string.h>


//using namespace std;


std::string SvgCol(int Value, int Min, int Max)
{   
	int r, g, b;
	int hodnot, krok, aktualne;

	hodnot=Max-Min;
	krok=hodnot/24;

	aktualne=Value/krok;

	//std::cout<<Value <<"aa"<< aktualne<<std::endl;
	//return krok;

	switch (aktualne) {
		case 0:
			r= 0;
			g= 0;
			b= 255;
		case 1:
			r= 0;
			g= 42;
			b= 255;

			break;
		case 2:
			r= 0;
			g= 85;
			b= 255;

			break;
		case 3:
			r= 0;
			g= 127;
			b= 255;

			break;
		case 4:
			
			r= 0;
			g= 169;
			b= 255;
			break;
		case 5:
			r= 0;
			g= 211;
			b= 255;

			break;
		case 6:
			r= 0;
			g= 255;
			b= 255;

			break;
		case 7:
			r= 0;
			g= 255;
			b= 211;

			break;
		case 8:
			r= 0;
			g= 255;
			b= 169;

			break;
		case 9:
			r= 0;
			g= 255;
			b= 127;

			break;
		case 10:
			r= 0;
			g= 255;
			b= 85;

			break;
		case 11:
			r= 0;
			g= 255;
			b= 42;

			break;
		case 12:
			r= 0;
			g= 255;
			b= 0;

			break;
		case 13:
			r= 42;
			g= 255;
			b= 0;

			break;
		case 14:
			r= 85;
			g= 255;
			b= 0;

			break;
		case 15:
			r= 127;
			g= 255;
			b= 0;

			break;
		case 16:
			r= 169;
			g= 255;
			b= 0;

			break;
		case 17:
			r= 211;
			g= 255;
			b= 0;

			break;
		case 18:
			r= 255;
			g= 255;
			b= 0;

			break;
		case 19:
			r= 255;
			g= 211;
			b= 0;

			break;
		case 20:
			r= 255;
			g= 169;
			b= 0;

			break;
		case 21:
			r= 255;
			g= 127;
			b= 0;

			break;
		case 22:
			r= 255;
			g= 85;
			b= 0;

			break;
		case 23:
			r= 255;
			g= 42;
			b= 0;

			break;
		case 24:
			r= 255;
			g= 0;
			b= 0;
			break;
		default:
			break;
	}

	//std::cout << "color" << r << " g " << g << " b " << b << std::endl;
	//char hexcol[16];
	//snprintf(hexcol, sizeof hexcol, "%02x%02x%02x", r, g, b);
	
	//std::stringstream ss;
	//ss  << "rgb(" << r << "," << g << "," << b << ")";
	//std::strig out = ss.str();
	//return out;
}



int SvgGen(std::string svginfo[11], int hourcount[744]){

int MINhourcount = 999;
int MAXhourcount = 0;

std::cout << svginfo[0] << std::endl;
std::cout << svginfo[1] << std::endl;
std::cout << svginfo[10] << std::endl;
std::cout << svginfo[3] << std::endl;

for (int i = 0; i < 743; ++i){

	if (MINhourcount > hourcount[i]){
		MINhourcount = hourcount[i];
	}

	if (MAXhourcount < hourcount[i]){
		MAXhourcount = hourcount[i];
	}
}
int out;
for (int i = 0; i < 743; ++i){
		
		//out=SvgCol(hourcount[i],MINhourcount,MAXhourcount);
		
		//std::cout << "-----" << out << "----" <<std::endl;
}


std::cout<< "minimalni hodnota je:"<<MINhourcount<<"a maximalni hodmota je "<< MAXhourcount<<"To je zatim vse :))"<<std::endl;


std::ofstream svgout;
svgout.open ("io/rmob.svg");

svgout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>	\n";
svgout << "<svg	\n";
svgout << "	  width=\"700\"	\n";
svgout << "	  height=\"220\"	\n";
svgout << "	  docname=\"rmob.svg\">	\n";
svgout << "	 <sodipodi:namedview	\n";
svgout << "	     pagecolor=\"#ffffff\"	\n";
svgout << "	  />	\n";
svgout << "	  <metadata	\n";
svgout << "	     id=\"metadata8\">	\n";
svgout << "		\n";
svgout << "	  </metadata>	\n";
svgout << "	  <defs	\n";
svgout << "	     id=\"defs6\" />	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.460505\"	\n";
svgout << "	     y=\"10.721849\"	\n";
svgout << "	     id=\"texObserver\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3757\"	\n";
svgout << "	       x=\"3.460505\"	\n";
svgout << "	       y=\"10.721849\"	\n";
svgout << "	       style=\"font-size:14px;-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal\">Observer : </tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.460505\"	\n";
svgout << "	     y=\"25.689907\"	\n";
svgout << "	     id=\"texCountry\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3761\"	\n";
svgout << "	       x=\"3.460505\"	\n";
svgout << "	       y=\"25.689907\"	\n";
svgout << "	       style=\"-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal;font-size:14px\">Country :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.460505\"	\n";
svgout << "	     y=\"40.657963\"	\n";
svgout << "	     id=\"texCity\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3765\"	\n";
svgout << "	       x=\"3.460505\"	\n";
svgout << "	       y=\"40.657963\"	\n";
svgout << "	       style=\"-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal;font-size:14px\">City :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"4.0605049\"	\n";
svgout << "	     y=\"55.626019\"	\n";
svgout << "	     id=\"texAntenna\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3769\"	\n";
svgout << "	       x=\"4.0605049\"	\n";
svgout << "	       y=\"55.626019\"	\n";
svgout << "	       style=\"-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal;font-size:14px\">Antenna :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.124505\"	\n";
svgout << "	     y=\"70.594078\"	\n";
svgout << "	     id=\"texPreamp\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3773\"	\n";
svgout << "	       x=\"3.124505\"	\n";
svgout << "	       y=\"70.594078\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">RF Preamp :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.124505\"	\n";
svgout << "	     y=\"85.562134\"	\n";
svgout << "	     id=\"texReciever\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3777\"	\n";
svgout << "	       x=\"3.124505\"	\n";
svgout << "	       y=\"85.562134\"	\n";
svgout << "	       style=\"font-size:14px;-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal\">Reciever :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"3.460505\"	\n";
svgout << "	     y=\"100.53019\"	\n";
svgout << "	     id=\"texComputer\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3781\"	\n";
svgout << "	       x=\"3.460505\"	\n";
svgout << "	       y=\"100.53019\"	\n";
svgout << "	       style=\"font-size:14px;-inkscape-font-specification:Solid Edge ISO;font-family:Solid Edge ISO;font-weight:normal;font-style:normal;font-stretch:normal;font-variant:normal\">Computer:</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"212.0795\"	\n";
svgout << "	     y=\"11.545778\"	\n";
svgout << "	     id=\"texLocation\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3785\"	\n";
svgout << "	       x=\"212.0795\"	\n";
svgout << "	       y=\"11.545778\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">Location :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"212.0795\"	\n";
svgout << "	     y=\"42.635391\"	\n";
svgout << "	     id=\"texFrequency\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3789\"	\n";
svgout << "	       x=\"212.0795\"	\n";
svgout << "	       y=\"42.635391\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">Frequency :</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"211.74992\"	\n";
svgout << "	     y=\"58.546131\"	\n";
svgout << "	     id=\"texEmail\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3793\"	\n";
svgout << "	       x=\"211.74992\"	\n";
svgout << "	       y=\"58.546131\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">E-mail :</tspan></text>	\n";
svgout << "	  <rect	\n";
svgout << "	     style=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:1;stroke-opacity:1;display:inline\"	\n";
svgout << "	     id=\"rect3902\"	\n";
svgout << "	     width=\"245.20146\"	\n";
svgout << "	     height=\"94.587128\"	\n";
svgout << "	     x=\"120.12895\"	\n";
svgout << "	     y=\"110.91171\" />	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;display:inline;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"11.49481\"	\n";
svgout << "	     y=\"180.42523\"	\n";
svgout << "	     id=\"text3898\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3900\"	\n";
svgout << "	       x=\"11.49481\"	\n";
svgout << "	       y=\"180.42523\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">Hourly count histogram:</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"407.0213\"	\n";
svgout << "	     y=\"217.69299\"	\n";
svgout << "	     id=\"text3944\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3946\"	\n";
svgout << "	       x=\"407.0213\"	\n";
svgout << "	       y=\"217.69299\"	\n";
svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#ff0016;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">Astrozor.cz  -   RMOBgen                                              ver.: 0.2</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"666.98639\"	\n";
svgout << "	     y=\"118.50355\"	\n";
svgout << "	     id=\"text3968\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3970\"	\n";
svgout << "	       x=\"666.98639\"	\n";
svgout << "	       y=\"118.50355\"	\n";
svgout << "	       style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">20</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"666.72394\"	\n";
svgout << "	     y=\"207.47627\"	\n";
svgout << "	     id=\"text3972\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3974\"	\n";
svgout << "	       x=\"666.72394\"	\n";
svgout << "	       y=\"207.47627\"	\n";
svgout << "	       style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">min</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:center;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:middle;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"242.85931\"	\n";
svgout << "	     y=\"108.27513\"	\n";
svgout << "	     id=\"text3840\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3842\"	\n";
svgout << "	       x=\"242.85931\"	\n";
svgout << "	       y=\"108.27513\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Verdana;-inkscape-font-specification:Verdana\">2013 - 12 - 21</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;opacity:0.77999998;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
svgout << "	     x=\"110.62619\"	\n";
svgout << "	     y=\"205.91681\"	\n";
svgout << "	     id=\"text3856\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3858\"	\n";
svgout << "	       x=\"110.62619\"	\n";
svgout << "	       y=\"205.91681\"	\n";
svgout << "	       style=\"font-size:14px;font-weight:normal;text-align:start;text-anchor:start;stroke:none;-inkscape-font-specification:Solid Edge ISO\">0</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
svgout << "	     x=\"117.10566\"	\n";
svgout << "	     y=\"217.36342\"	\n";
svgout << "	     id=\"text3860\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3862\"	\n";
svgout << "	       x=\"117.10566\"	\n";
svgout << "	       y=\"217.36342\"	\n";
svgout << "	       style=\"font-size:14px\">0h        4h         8h         12h        16h       20h      24h </tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:end;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:end;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
svgout << "	     x=\"115.36838\"	\n";
svgout << "	     y=\"115.8082\"	\n";
svgout << "	     id=\"text3864\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3866\"	\n";
svgout << "	       x=\"115.36838\"	\n";
svgout << "	       y=\"115.8082\">max</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;display:inline;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"666.72394\"	\n";
svgout << "	     y=\"22.712807\"	\n";
svgout << "	     id=\"text3972-9\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3974-5\"	\n";
svgout << "	       x=\"666.72394\"	\n";
svgout << "	       y=\"22.712807\"	\n";
svgout << "	       style=\"font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">min</tspan></text>	\n";
svgout << "	  <rect	\n";
svgout << "	     style=\"fill:#000000;fill-opacity:1;stroke:none\"	\n";
svgout << "	     id=\"rect3818\"	\n";
svgout << "	     width=\"247.94917\"	\n";
svgout << "	     height=\"191.48126\"	\n";
svgout << "	     x=\"406.69171\"	\n";
svgout << "	     y=\"15.335854\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     style=\"fill:#000000;fill-opacity:1;stroke:none\"	\n";
svgout << "	     id=\"rect3824\"	\n";
svgout << "	     width=\"7.9482584\"	\n";
svgout << "	     height=\"191.97607\"	\n";
svgout << "	     x=\"656.72479\"	\n";
svgout << "	     y=\"15.262415\" />	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"406.69168\"	\n";
svgout << "	     y=\"10.721848\"	\n";
svgout << "	     id=\"texDays\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3828\"	\n";
svgout << "	       x=\"406.69168\"	\n";
svgout << "	       y=\"10.721848\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">1    Days ---&gt;               15                                   31</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"385.26953\"	\n";
svgout << "	     y=\"24.893438\"	\n";
svgout << "	     id=\"tex00h\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       x=\"385.26953\"	\n";
svgout << "	       y=\"24.893438\"	\n";
svgout << "	       id=\"tspan3860\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">00h</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"385.26953\"	\n";
svgout << "	     y=\"70.291969\"	\n";
svgout << "	     id=\"tex06h\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3884\"	\n";
svgout << "	       x=\"385.26953\"	\n";
svgout << "	       y=\"70.291969\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">06h</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"385.26953\"	\n";
svgout << "	     y=\"115.69049\"	\n";
svgout << "	     id=\"tex12h\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3888\"	\n";
svgout << "	       x=\"385.26953\"	\n";
svgout << "	       y=\"115.69049\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">12h</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"385.26953\"	\n";
svgout << "	     y=\"161.08902\"	\n";
svgout << "	     id=\"tex18h\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3892\"	\n";
svgout << "	       x=\"385.26953\"	\n";
svgout << "	       y=\"161.08902\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">18h</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"385.26953\"	\n";
svgout << "	     y=\"206.48755\"	\n";
svgout << "	     id=\"tex23h\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3896\"	\n";
svgout << "	       x=\"385.26953\"	\n";
svgout << "	       y=\"206.48755\"	\n";
svgout << "	       style=\"font-size:14px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\">23h</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#7800e9;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"54.049789\"	\n";
svgout << "	     y=\"10.803881\"	\n";
svgout << "	     id=\"editObserker\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3986\"	\n";
svgout << "	       x=\"54.049789\"	\n";
svgout << "	       y=\"10.803881\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[0] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"54.531723\"	\n";
svgout << "	     y=\"25.662733\"	\n";
svgout << "	     id=\"editCountry\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3990\"	\n";
svgout << "	       x=\"54.531723\"	\n";
svgout << "	       y=\"25.662733\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[1] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"54.531723\"	\n";
svgout << "	     y=\"40.521584\"	\n";
svgout << "	     id=\"editCity\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3994\"	\n";
svgout << "	       x=\"54.531723\"	\n";
svgout << "	       y=\"40.521584\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[2] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"54.087875\"	\n";
svgout << "	     y=\"55.380436\"	\n";
svgout << "	     id=\"editAntenna\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan3998\"	\n";
svgout << "	       x=\"54.087875\"	\n";
svgout << "	       y=\"55.380436\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[3] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"54.527328\"	\n";
svgout << "	     y=\"70.239288\"	\n";
svgout << "	     id=\"editPreamp\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4002\"	\n";
svgout << "	       x=\"54.527328\"	\n";
svgout << "	       y=\"70.239288\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[4] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"55.015121\"	\n";
svgout << "	     y=\"85.098145\"	\n";
svgout << "	     id=\"editReciever\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4006\"	\n";
svgout << "	       x=\"55.015121\"	\n";
svgout << "	       y=\"85.098145\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[5] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"55.015121\"	\n";
svgout << "	     y=\"99.956993\"	\n";
svgout << "	     id=\"editComputer\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4010\"	\n";
svgout << "	       x=\"55.015121\"	\n";
svgout << "	       y=\"99.956993\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[6] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"272.31873\"	\n";
svgout << "	     y=\"10.062026\"	\n";
svgout << "	     id=\"editLat\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4014\"	\n";
svgout << "	       x=\"272.31873\"	\n";
svgout << "	       y=\"10.062026\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[7] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"267.68707\"	\n";
svgout << "	     y=\"23.245579\"	\n";
svgout << "	     id=\"editLon\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4018\"	\n";
svgout << "	       x=\"267.68707\"	\n";
svgout << "	       y=\"23.245579\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[8] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"267.69147\"	\n";
svgout << "	     y=\"42.362961\"	\n";
svgout << "	     id=\"editFrequency\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4022\"	\n";
svgout << "	       x=\"267.69147\"	\n";
svgout << "	       y=\"42.362961\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[9] << "</tspan></text>	\n";
svgout << "	  <text	\n";
svgout << "	     xml:space=\"preserve\"	\n";
svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
svgout << "	     x=\"267.94196\"	\n";
svgout << "	     y=\"56.532341\"	\n";
svgout << "	     id=\"editEmail\"	\n";
svgout << "	     linespacing=\"125%\"><tspan	\n";
svgout << "	       role=\"line\"	\n";
svgout << "	       id=\"tspan4026\"	\n";
svgout << "	       x=\"267.94196\"	\n";
svgout << "	       y=\"56.532341\"	\n";
svgout << "	       style=\"font-size:9px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Verdana;-inkscape-font-specification:Verdana\">" << svginfo[10] << "</tspan></text>	\n";
svgout << "	  <rect	\n";
svgout << "	     style=\"opacity:0.42049470000000000;fill:#ff0000;fill-opacity:1;stroke:none;stroke-opacity:1\"	\n";
svgout << "	     id=\"rect3868\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     x=\"407.70615\"	\n";
svgout << "	     y=\"16.174425\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"16.22628\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-9\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"24.224943\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-5\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"32.223595\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-0\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"200.19554\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-6\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"192.19688\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-92\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"184.19821\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-44\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"168.20088\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-2\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"176.19955\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-8\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"120.2089\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-25\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"128.20757\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-99\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"136.20622\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-50\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"144.2049\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-1\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"152.20355\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-21\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"160.20222\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-87\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"112.21024\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-49\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"104.21157\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-3\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"96.212906\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-68\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"48.220921\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-7\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"56.219597\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-15\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"64.218254\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-18\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"80.215591\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-41\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"88.214249\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-51\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"40.22226\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-63\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "	  <rect	\n";
svgout << "	     y=\"72.216919\"	\n";
svgout << "	     x=\"657.7077\"	\n";
svgout << "	     height=\"5.9932513\"	\n";
svgout << "	     width=\"5.9932489\"	\n";
svgout << "	     id=\"rect3868-156\"	\n";
svgout << "	     style=\"opacity:0.42049471;fill:#ff0000;fill-opacity:1;stroke:none\" />	\n";
svgout << "</svg>	\n";


svgout.close();


}