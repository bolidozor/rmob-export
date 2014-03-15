#include <iostream>
#include <fstream>
#include <string.h>
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip>

std::string DecDegToDDMMSS (std::string DecDeg){

	std::stringstream ssout;
	double deg, min, sec, minb, secb, out;

	ssout << atoi(DecDeg.substr(0,3).c_str()) << "°";
	deg=(double)atoi(DecDeg.substr(4,6).c_str())/1000000;
	min=deg*60;
	sec= modf(deg*60, &minb);
	out= modf(sec*60, &secb);

	ssout << minb << "'" << secb << "\"";
	return ssout.str();
}


int SvgColRed(int num){
	int out;
	if (num <= 12)
	{
		out = 0;
	}
	if(num > 12 && num < 18)
	{
		out = ((num - 12) * 51);
	}
	if (num >= 18)
	{
		out = 255;
	}
	return out;
}


int SvgColBlue(int num){
	int out;
	if (num <= 6)
	{
		out = 255;
	}
	if(num > 6 && num < 12)
	{
		out = 255 - ((num -6 ) * 51);
	}
	if (num >= 12)
	{
		out = 0;
	}
	return out;
}


int SvgColGreen(int num){
	int out;
	if (num <= 0)
	{
		out = 0;
	}
	if(num > 0 && num < 6)
	{
		out = (num * 51);
	}
	if (num >= 6 && num <= 18)
	{
		out = 255;
	}
	if (num > 18)
	{
		out = 255 - ((num - 18) * 42);
	}

	return out;
}


std::string SvgColAll(int max, int min, int actual){
	std::string out;
	float krok;
	int num;

	krok=(max - min)/23;
	num=actual/krok;
	std::ostringstream ss;

	if (actual == 1111)
	{
		ss<< "rgb(0,0,0)";
	}
	else
	{
		ss << "rgb("<< SvgColRed(num) <<","<< SvgColGreen(num) <<","<< SvgColBlue(num)<<")"; 
	}
	return ss.str();
}

std::string SvgColAll_new(int max, int min, int actual){
	std::string out;
	float krok;
	int num;

	krok=(max - min)/23;
	num=actual/krok;
	std::ostringstream ss;

	if (actual == 1111)
	{
		ss<< "rgb(0,0,0)";
	}
	else
	{
		ss << "rgb("<< SvgColRed(num) <<","<< SvgColGreen(num) <<","<< SvgColBlue(num)<<")"; 
	}
	return ss.str();
}


int SvgGen(std::string svginfo[15], int hourcount[745]){

	int MINhourcount = 999;
	int MAXhourcount = 0;

	int DayMINhourcount = 999;
	int DayMAXhourcount = 0;

	float x = 408.596;
	float y = 17.174;

	int out;
	time_t now = time(0);  
	tm *ltm = localtime(&now);

	time_t rawtime;
	struct tm * utc;
	
	time ( &rawtime );
	utc = gmtime ( &rawtime );


	int f = 0;
	int MonthAvgr = 0;
	for (int i = 0; i < 744; ++i)
	{
		if (hourcount[i] != 1111)
		{	
			f++;
			MonthAvgr =+ MonthAvgr;
		}
	}
	MonthAvgr = MonthAvgr/f;

	for (int i = 0; i < 744; ++i)
	{

		if (MINhourcount > hourcount[i] && hourcount[i] != 1111)
		{
			MINhourcount = hourcount[i];
		}

		if (MAXhourcount < hourcount[i] && hourcount[i] != 1111)
		{
			MAXhourcount = hourcount[i];
		}
	}

	MINhourcount = 0;

	for (int i = (utc->tm_mday-1) * 24; i < (utc->tm_mday-1)*24 + 24; ++i)
	{

		if (DayMINhourcount > hourcount[i] && hourcount[i] != 1111)
		{
			DayMINhourcount = hourcount[i];
		}

		if (DayMAXhourcount < hourcount[i] && hourcount[i] != 1111)
		{
			DayMAXhourcount = hourcount[i];
		}
	}


	//std::cout<< "minimalni hodnota je:"<<MINhourcount<<"a maximalni hodmota je "<< MAXhourcount<<" A deni minimalni hodnota je:"<<DayMINhourcount<<"a maximalni deni hodmota je "<< DayMAXhourcount<<" To je zatim vse :))"<<std::endl;


	std::ofstream svgout;
	svgout.open ("io/rmob.svg");


	svgout << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>	\n";
	svgout << "<svg	\n";
	svgout << "	   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"	\n";
	svgout << "	   xmlns:cc=\"http://creativecommons.org/ns#\"	\n";
	svgout << "	   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"	\n";
	svgout << "	   xmlns:svg=\"http://www.w3.org/2000/svg\"	\n";
	svgout << "	   xmlns=\"http://www.w3.org/2000/svg\"	\n";
	svgout << "	   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"	\n";
	svgout << "	   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"	\n";
	svgout << "	   width=\"700\"	\n";
	svgout << "	   height=\"220\"	\n";
	svgout << "	   docname=\"rmob.svg\"	\n";
	svgout << "	   id=\"svg3146\"	\n";
	svgout << "	   version=\"1.1\"	\n";
	svgout << "	   inkscape:version=\"0.48.3.1 r9886\"	\n";
	svgout << "	   sodipodi:docname=\"formb_krivky.svg\">	\n";
	svgout << "	  <sodipodi:namedview	\n";
	svgout << "	     pagecolor=\"#ffffff\"	\n";
	svgout << "	     bordercolor=\"#666666\"	\n";
	svgout << "	     borderopacity=\"1\"	\n";
	svgout << "	     objecttolerance=\"10\"	\n";
	svgout << "	     gridtolerance=\"10\"	\n";
	svgout << "	     guidetolerance=\"10\"	\n";
	svgout << "	     inkscape:pageopacity=\"0\"	\n";
	svgout << "	     inkscape:pageshadow=\"2\"	\n";
	svgout << "	     inkscape:window-width=\"1551\"	\n";
	svgout << "	     inkscape:window-height=\"876\"	\n";
	svgout << "	     id=\"namedview3252\"	\n";
	svgout << "	     showgrid=\"false\"	\n";
	svgout << "	     inkscape:zoom=\"3.0432464\"	\n";
	svgout << "	     inkscape:cx=\"213.20369\"	\n";
	svgout << "	     inkscape:cy=\"104.10705\"	\n";
	svgout << "	     inkscape:window-x=\"49\"	\n";
	svgout << "	     inkscape:window-y=\"24\"	\n";
	svgout << "	     inkscape:window-maximized=\"1\"	\n";
	svgout << "	     inkscape:current-layer=\"svg3146\"	\n";
	svgout << "	     showguides=\"true\"	\n";
	svgout << "	     inkscape:guide-bbox=\"true\" />	\n";
	svgout << "	  <namedview	\n";
	svgout << "	     pagecolor=\"#ffffff\"	\n";
	svgout << "	     id=\"namedview3148\" />	\n";
	svgout << "	  <metadata	\n";
	svgout << "	     id=\"metadata8\">	\n";
	svgout << "	    <rdf:RDF>	\n";
	svgout << "	      <cc:Work	\n";
	svgout << "	         rdf:about=\"\">	\n";
	svgout << "	        <dc:format>image/svg+xml</dc:format>	\n";
	svgout << "	        <dc:type	\n";
	svgout << "	           rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />	\n";
	svgout << "	        <dc:title></dc:title>	\n";
	svgout << "	      </cc:Work>	\n";
	svgout << "	    </rdf:RDF>	\n";
	svgout << "	  </metadata>	\n";
	svgout << "	  <defs	\n";
	svgout << "	     id=\"defs6\" />	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texObserver\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.78863,9.7254658 c -5.3e-6,0.5677092 -0.2395884,1.0364592 -0.71875,1.4062502 -0.4427125,0.338542 -0.9557328,0.507812 -1.5390625,0.507812 -0.5833358,0 -1.1041686,-0.171875 -1.5625,-0.515625 -0.500001,-0.380207 -0.7500007,-0.851561 -0.75,-1.4140622 l 0,-6.140625 c -7e-7,-0.6197831 0.2552073,-1.1119701 0.765625,-1.4765625 0.4166647,-0.2968653 0.9322892,-0.4453026 1.546875,-0.4453125 0.5833297,9.9e-6 1.09635,0.1718847 1.5390625,0.515625 0.4791616,0.3698007 0.7187447,0.8385502 0.71875,1.40625 l 0,6.15625 m -0.71875,-0.1484375 0,-5.859375 C 8.0698754,3.3114115 7.9162297,2.9806827 7.6089425,2.7254658 7.3224803,2.4858915 6.9709182,2.3661 6.554255,2.3660908 6.1636273,2.3661 5.8224818,2.4546415 5.5308175,2.6317158 c -0.4166683,0.2500086 -0.6250014,0.6093833 -0.625,1.078125 l 0,5.8671875 c -1.4e-6,0.4166682 0.2057275,0.7552097 0.6171875,1.0156247 0.3333309,0.213543 0.6770806,0.320313 1.03125,0.320313 0.3645799,0 0.6953087,-0.104166 0.9921875,-0.3125 C 7.8953964,10.355675 8.0698754,10.01453 8.06988,9.5770283\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4614\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 14.22613,10.209841 c -5e-6,0.567709 -0.166671,0.950521 -0.5,1.148437 -0.208337,0.125 -0.565108,0.1875 -1.070312,0.1875 l -2.515625,0 0,-9.8437497 0.695312,0 0,2.6640625 1.78125,-0.00781 c 0.515621,7.2e-6 0.921871,0.1276112 1.21875,0.3828125 0.14062,0.1250067 0.249995,0.3177148 0.328125,0.578125 l 0.0625,0.359375 0,4.5312502 m -0.710937,0.03906 0,-4.4609372 c -5e-6,-0.4999938 -0.244796,-0.7499935 -0.734375,-0.75 l -1.921875,0 0,5.8125002 1.867187,0 c 0.526038,0 0.789058,-0.20052 0.789063,-0.601563\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4616\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 19.108943,5.5379658 -0.71875,0 c -0.265629,-0.3541603 -0.585941,-0.5312435 -0.960938,-0.53125 -0.229169,6.5e-6 -0.424481,0.036465 -0.585937,0.109375 -0.07813,0.05209 -0.125002,0.080735 -0.140625,0.085938 -0.03646,0.026048 -0.09636,0.075527 -0.179688,0.1484375 -0.171876,0.1145894 -0.257814,0.3802141 -0.257812,0.796875 -2e-6,0.4166716 0.192706,0.7838588 0.578125,1.1015625 l 1.1875,0.7265625 c 0.734371,0.4479198 1.101558,0.9869817 1.101562,1.6171875 -4e-6,0.5104177 -0.156254,0.9583347 -0.46875,1.3437497 -0.359378,0.442709 -0.83594,0.664063 -1.429687,0.664063 -0.994793,0 -1.640626,-0.549479 -1.9375,-1.6484377 l 0.679687,0 c 0.249999,0.6614597 0.677082,0.9921877 1.28125,0.9921877 0.343747,0 0.630205,-0.114583 0.859375,-0.34375 0.229163,-0.234374 0.343746,-0.523436 0.34375,-0.8671877 -4e-6,-0.4114561 -0.242191,-0.7760391 -0.726562,-1.09375 L 16.85113,8.0614033 C 16.75217,7.9989068 16.504774,7.8061987 16.108943,7.4832783 15.765192,7.113491 15.593317,6.668179 15.593318,6.1473408 c -10e-7,-0.5468691 0.16927,-0.9869728 0.507812,-1.3203125 0.33854,-0.3385346 0.783852,-0.5078053 1.335938,-0.5078125 0.864579,7.2e-6 1.421871,0.4062568 1.671875,1.21875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4618\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 24.60113,8.1785908 -3.414062,0 0,1.59375 c -2e-6,0.7291672 0.367185,1.0937502 1.101562,1.0937502 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.166668,-0.296874 -0.250001,-0.640623 -0.25,-1.0312497 l 0,-3.453125 c -1e-6,-0.5885359 0.203124,-1.0781188 0.609375,-1.46875 0.406248,-0.3958263 0.906247,-0.5937428 1.5,-0.59375 0.572913,7.2e-6 1.057287,0.1901112 1.453125,0.5703125 0.395828,0.3750063 0.593745,0.8489641 0.59375,1.421875 l -0.0078,1.875 M 23.890193,6.4520283 c -5e-6,-0.4114529 -0.117192,-0.7499942 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.4062435 -0.960937,-0.40625 -0.343753,6.5e-6 -0.640628,0.096361 -0.890625,0.2890625 -0.333335,0.2552143 -0.500002,0.6302139 -0.5,1.125 l 0,1.0546875 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4620\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 29.47613,6.2645283 -0.671875,0 c -3e-6,-0.8124939 -0.466149,-1.2187435 -1.398437,-1.21875 l -0.601563,0 0,6.5078127 -0.726562,0 0,-7.1796877 1.0625,0 c 0.83333,7.1e-6 1.4401,0.1380278 1.820312,0.4140625 0.260413,0.1875065 0.432288,0.4739646 0.515625,0.859375 l 0,0.6171875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4622\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 32.577693,11.561403 -0.53125,0 -1.867188,-7.2265622 0.671875,0 1.484375,5.5 1.445313,-5.484375 0.664062,0 -1.867187,7.2109372\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4624\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 39.60113,8.1785908 -3.414062,0 0,1.59375 c -2e-6,0.7291672 0.367185,1.0937502 1.101562,1.0937502 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.166668,-0.296874 -0.250001,-0.640623 -0.25,-1.0312497 l 0,-3.453125 c -10e-7,-0.5885359 0.203124,-1.0781188 0.609375,-1.46875 0.406248,-0.3958263 0.906247,-0.5937428 1.5,-0.59375 0.572913,7.2e-6 1.057287,0.1901112 1.453125,0.5703125 0.395828,0.3750063 0.593745,0.8489641 0.59375,1.421875 l -0.0078,1.875 M 38.890193,6.4520283 c -5e-6,-0.4114529 -0.117192,-0.7499942 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.4062435 -0.960937,-0.40625 -0.343753,6.5e-6 -0.640628,0.096361 -0.890625,0.2890625 -0.333335,0.2552143 -0.500002,0.6302139 -0.5,1.125 l 0,1.0546875 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4626\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 44.47613,6.2645283 -0.671875,0 c -3e-6,-0.8124939 -0.466149,-1.2187435 -1.398437,-1.21875 l -0.601563,0 0,6.5078127 -0.726562,0 0,-7.1796877 1.0625,0 c 0.83333,7.1e-6 1.4401,0.1380278 1.820312,0.4140625 0.260413,0.1875065 0.432288,0.4739646 0.515625,0.859375 l 0,0.6171875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4628\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 50.16363,7.1629658 -0.710937,0 0,-0.7109375 0.71875,0 -0.0078,0.7109375 m 0,3.7734372 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4630\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texCountry\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.22613,26.392139 -2.8359375,0 c -0.3489599,0 -0.6328138,-0.09375 -0.8515625,-0.28125 -0.2343758,-0.197916 -0.3515632,-0.468749 -0.3515625,-0.8125 l 0,-7.492187 c -7e-7,-0.395824 0.1302075,-0.700512 0.390625,-0.914063 0.1249988,-0.09895 0.2499986,-0.174469 0.375,-0.226562 0.2083316,-0.08332 0.4661439,-0.12499 0.7734375,-0.125 l 2.5,0 0,0.726562 -2.5,0 c -0.5572934,10e-6 -0.8359389,0.257822 -0.8359375,0.773438 l 0,7.101562 c -1.4e-6,0.375001 0.2682275,0.562501 0.8046875,0.5625 l 2.53125,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4597\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 13.72613,24.321827 c -5e-6,0.583335 -0.197921,1.083334 -0.59375,1.5 -0.395837,0.411458 -0.882816,0.617187 -1.460937,0.617187 -0.572919,0 -1.067711,-0.210937 -1.484375,-0.632812 -0.4114598,-0.427082 -0.6171887,-0.927082 -0.617188,-1.5 l 0,-3.03125 c -7e-7,-0.593744 0.2005199,-1.096348 0.601563,-1.507813 0.406248,-0.416659 0.906247,-0.624992 1.5,-0.625 0.578121,8e-6 1.0651,0.210945 1.460937,0.632813 0.395829,0.416673 0.593745,0.916672 0.59375,1.5 l 0,3.046875 m -0.726562,-0.15625 0,-2.742188 c -5e-6,-0.421869 -0.10938,-0.77864 -0.328125,-1.070312 -0.244796,-0.328119 -0.570316,-0.492181 -0.976563,-0.492188 -0.343753,7e-6 -0.64844,0.117194 -0.914062,0.351563 -0.328127,0.291672 -0.492189,0.69011 -0.492188,1.195312 l 0,2.757813 c -10e-7,0.489585 0.166665,0.882814 0.5,1.179687 0.276039,0.250001 0.578122,0.375001 0.90625,0.375 0.39583,1e-6 0.721351,-0.164061 0.976563,-0.492187 0.218745,-0.281249 0.32812,-0.635415 0.328125,-1.0625\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4599\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 19.06988,26.392139 -2.195312,0 c -1.119793,0 -1.679689,-0.507812 -1.679688,-1.523437 l -0.0078,-5.679688 0.726562,0 0,5.265625 c -10e-7,0.515627 0.07812,0.843752 0.234375,0.984375 0.166665,0.16146 0.398435,0.242189 0.695313,0.242188 l 1.507812,0 0,-6.492188 0.71875,0 0,7.203125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4601\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 24.35113,26.407764 -0.710937,0 0,-5.273437 c -4e-6,-0.421869 -0.07552,-0.729161 -0.226563,-0.921875 -0.161462,-0.171869 -0.395837,-0.257806 -0.703125,-0.257813 l -1.5,0 0,6.453125 -0.710937,-0.01563 0,-7.195312 2.1875,0 c 1.119787,7e-6 1.679682,0.507819 1.679687,1.523437 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4603\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 28.866755,19.884327 -1.320312,0 0,6.507812 -0.71875,0 0,-6.507812 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4605\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 33.50738,21.095264 -0.671875,0 c -3e-6,-0.812493 -0.466149,-1.218743 -1.398437,-1.21875 l -0.601563,0 0,6.507813 -0.726562,0 0,-7.179688 1.0625,0 c 0.83333,8e-6 1.4401,0.138028 1.820312,0.414063 0.260413,0.187507 0.432288,0.473965 0.515625,0.859375 l 0,0.617187\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4607\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 38.624568,19.181202 -2.632813,9.101562 c -0.125002,0.43229 -0.403647,0.648435 -0.835937,0.648438 l -0.632813,0 0,-0.65625 0.359375,0 c 0.291665,-2e-6 0.49479,-0.205731 0.609375,-0.617188 l 0.664063,-2.398437 -1.734375,-6.078125 0.734375,0 1.398437,4.828125 1.351563,-4.828125 0.71875,0\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4609\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 44.13238,21.993702 -0.710937,0 0,-0.710938 0.71875,0 -0.0078,0.710938 m 0,3.773437 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4611\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texCity\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.22613,41.222874 -2.8359375,0 c -0.3489599,0 -0.6328138,-0.09375 -0.8515625,-0.28125 -0.2343758,-0.197917 -0.3515632,-0.46875 -0.3515625,-0.8125 l 0,-7.492188 c -7e-7,-0.395824 0.1302075,-0.700511 0.390625,-0.914062 0.1249988,-0.09895 0.2499986,-0.17447 0.375,-0.226563 0.2083316,-0.08332 0.4661439,-0.12499 0.7734375,-0.125 l 2.5,0 0,0.726563 -2.5,0 c -0.5572934,9e-6 -0.8359389,0.257821 -0.8359375,0.773437 l 0,7.101563 c -1.4e-6,0.375001 0.2682275,0.5625 0.8046875,0.5625 l 2.53125,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4586\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 10.648005,32.410374 -0.7265625,0 0,-1.039063 0.7265625,0 0,1.039063 m 0.0078,8.796875 -0.7343755,0 0,-7.164063 0.7343755,0 0,7.164063\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4588\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 15.491755,34.715061 -1.320312,0 0,6.507813 -0.71875,0 0,-6.507813 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4590\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 20.624568,34.011936 -2.632813,9.101563 c -0.125002,0.432289 -0.403647,0.648435 -0.835937,0.648437 l -0.632813,0 0,-0.65625 0.359375,0 c 0.291665,-2e-6 0.49479,-0.205731 0.609375,-0.617187 l 0.664063,-2.398438 -1.734375,-6.078125 0.734375,0 1.398437,4.828125 1.351563,-4.828125 0.71875,0\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4592\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 26.13238,36.824436 -0.710937,0 0,-0.710937 0.71875,0 -0.0078,0.710937 m 0,3.773438 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4594\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texAntenna\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 9.4198799,56.037983 -0.6953125,0 -0.703125,-2.96875 -2.390625,0 -0.734375,2.96875 -0.6875,0 2.3984375,-9.835938 0.5390625,0 2.2734375,9.835938 M 7.8651924,52.34267 6.8730049,48.006733 5.8808174,52.34267 l 1.984375,0\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4569\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 14.13863,56.069233 -0.710938,0 0,-5.273438 c -3e-6,-0.421869 -0.07552,-0.72916 -0.226562,-0.921875 -0.161462,-0.171868 -0.395837,-0.257806 -0.703125,-0.257812 l -1.5,0 0,6.453125 -0.710938,-0.01563 0,-7.195313 2.1875,0 c 1.119788,8e-6 1.679683,0.50782 1.679688,1.523438 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4571\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 18.654255,49.545795 -1.320313,0 0,6.507813 -0.71875,0 0,-6.507813 -1.273437,0 0,-0.6875 1.273437,0 0,-2.65625 0.71875,0 0,2.65625 1.320313,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4573\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 24.01363,52.670795 -3.414063,0 0,1.59375 c -1e-6,0.729168 0.367186,1.093751 1.101563,1.09375 l 2.203125,0 0,0.6875 -2.507813,0 c -0.593751,0 -1.020834,-0.23177 -1.28125,-0.695312 -0.166667,-0.296874 -0.25,-0.640624 -0.25,-1.03125 l 0,-3.453125 c 0,-0.588536 0.203124,-1.078119 0.609375,-1.46875 0.406249,-0.395826 0.906248,-0.593743 1.5,-0.59375 0.572914,7e-6 1.057288,0.190111 1.453125,0.570312 0.395829,0.375007 0.593746,0.848965 0.59375,1.421875 l -0.0078,1.875 m -0.710938,-1.726562 c -4e-6,-0.411453 -0.117191,-0.749994 -0.351562,-1.015625 -0.234379,-0.270827 -0.554691,-0.406244 -0.960938,-0.40625 -0.343752,6e-6 -0.640627,0.09636 -0.890625,0.289062 -0.333335,0.255215 -0.500001,0.630214 -0.5,1.125 l 0,1.054688 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4575\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 29.35738,56.069233 -0.710938,0 0,-5.273438 c -3e-6,-0.421869 -0.07552,-0.72916 -0.226562,-0.921875 -0.161462,-0.171868 -0.395837,-0.257806 -0.703125,-0.257812 l -1.5,0 0,6.453125 -0.710938,-0.01563 0,-7.195313 2.1875,0 c 1.119788,8e-6 1.679683,0.50782 1.679688,1.523438 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4577\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 34.66988,56.069233 -0.710938,0 0,-5.273438 c -3e-6,-0.421869 -0.07552,-0.72916 -0.226562,-0.921875 -0.161462,-0.171868 -0.395837,-0.257806 -0.703125,-0.257812 l -1.5,0 0,6.453125 -0.710938,-0.01563 0,-7.195313 2.1875,0 c 1.119788,8e-6 1.679683,0.50782 1.679688,1.523438 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4579\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 40.990192,56.03017 -0.414062,0 c -0.322922,0 -0.598963,-0.177083 -0.828125,-0.53125 -0.307296,0.354167 -0.718754,0.53125 -1.234375,0.53125 l -1.179688,0 c -0.817709,0 -1.226563,-0.445312 -1.226562,-1.335937 l 0,-4.195313 c -10e-7,-1.10416 0.536457,-1.656242 1.609375,-1.65625 l 2.46875,0 -0.0078,5.398438 c -4e-6,0.729168 0.270829,1.093751 0.8125,1.09375 l 0,0.695312 m -1.515625,-1.710937 0,-4.796875 -1.789062,0 c -0.578127,6e-6 -0.867189,0.312506 -0.867188,0.9375 l 0,4.273437 c -10e-7,0.406251 0.239582,0.609376 0.71875,0.609375 l 0.726563,0 c 0.807288,1e-6 1.210933,-0.341144 1.210937,-1.023437\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4581\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 46.60738,51.65517 -0.710938,0 0,-0.710937 0.71875,0 -0.0078,0.710937 m 0,3.773438 -0.710938,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4583\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texPreamp\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.7573175,70.868721 -0.78125,0 -2.296875,-4.320312 -1.0625,0 0,4.320312 -0.7265625,0 0,-9.835937 2.3046875,0 c 0.2552051,9e-6 0.507809,0.05209 0.7578125,0.15625 1.0260369,0.427092 1.5390572,1.278654 1.5390625,2.554687 -5.3e-6,0.640631 -0.1796926,1.226568 -0.5390625,1.757813 -0.3958377,0.583338 -0.8958372,0.916671 -1.5,1 l 2.3046875,4.367187 m -0.9609375,-7.125 c -4.6e-6,-0.624992 -0.1875044,-1.1302 -0.5625,-1.515625 C 6.9213762,61.905188 6.5620016,61.74373 6.155755,61.743721 l -1.546875,0 0,4.078125 1.671875,0 c 0.3072882,5e-6 0.6197879,-0.169266 0.9375,-0.507812 0.3854122,-0.406245 0.5781204,-0.929682 0.578125,-1.570313\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4550\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 13.991693,61.735909 -3.4375,0 0,3.375 3.234375,0 0,0.703125 -3.234375,0 0,5.085937 -0.7031255,0 0,-9.867187 4.1406255,0 0,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4552\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 23.788568,63.774971 c -6e-6,0.875006 -0.270839,1.575526 -0.8125,2.101563 -0.458338,0.447921 -0.968754,0.674483 -1.53125,0.679687 l -1.539063,0.01563 0,4.3125 -0.726562,0 0,-9.851562 2.226562,0 c 0.23958,9e-6 0.507809,0.0573 0.804688,0.171875 1.052078,0.406259 1.578119,1.263029 1.578125,2.570312 m -0.703125,0 c -5e-6,-0.541659 -0.151047,-1.0052 -0.453125,-1.390625 -0.322921,-0.421866 -0.7474,-0.632803 -1.273438,-0.632812 l -1.460937,0 0,4.101562 1.53125,0 c 0.395829,5e-6 0.755204,-0.169266 1.078125,-0.507812 0.385412,-0.401036 0.57812,-0.924473 0.578125,-1.570313\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4554\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 28.26513,65.587471 -0.671875,0 c -3e-6,-0.812494 -0.466149,-1.218743 -1.398437,-1.21875 l -0.601563,0 0,6.507813 -0.726562,0 0,-7.179688 1.0625,0 c 0.83333,7e-6 1.4401,0.138028 1.820312,0.414063 0.260413,0.187506 0.432288,0.473964 0.515625,0.859375 l 0,0.617187\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4556\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 33.60888,67.501534 -3.414062,0 0,1.59375 c -2e-6,0.729167 0.367185,1.09375 1.101562,1.09375 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.166668,-0.296874 -0.250001,-0.640624 -0.25,-1.03125 l 0,-3.453125 c -1e-6,-0.588536 0.203124,-1.078119 0.609375,-1.46875 0.406248,-0.395826 0.906247,-0.593743 1.5,-0.59375 0.572913,7e-6 1.057287,0.190111 1.453125,0.570313 0.395828,0.375006 0.593745,0.848964 0.59375,1.421875 l -0.0078,1.875 m -0.710937,-1.726563 c -5e-6,-0.411453 -0.117192,-0.749994 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.406243 -0.960937,-0.40625 -0.343753,7e-6 -0.640628,0.09636 -0.890625,0.289063 -0.333335,0.255214 -0.500002,0.630213 -0.5,1.125 l 0,1.054687 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4558\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 39.960443,70.860909 -0.414063,0 c -0.322922,0 -0.598963,-0.177084 -0.828125,-0.53125 -0.307296,0.354166 -0.718754,0.53125 -1.234375,0.53125 l -1.179687,0 c -0.81771,0 -1.226564,-0.445313 -1.226563,-1.335938 l 0,-4.195312 c -10e-7,-1.104161 0.536457,-1.656243 1.609375,-1.65625 l 2.46875,0 -0.0078,5.398437 c -5e-6,0.729168 0.270828,1.093751 0.8125,1.09375 l 0,0.695313 m -1.515625,-1.710938 0,-4.796875 -1.789063,0 c -0.578127,7e-6 -0.867189,0.312506 -0.867187,0.9375 l 0,4.273438 c -2e-6,0.40625 0.239581,0.609375 0.71875,0.609375 l 0.726562,0 c 0.807288,0 1.210933,-0.341145 1.210938,-1.023438\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4560\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 47.124505,70.868721 -0.710937,0 0,-5.273437 c -6e-6,-0.630203 -0.174485,-1.002598 -0.523438,-1.117188 -0.119797,-0.03645 -0.255214,-0.05468 -0.40625,-0.05469 l -1.007812,0 0,6.445312 -0.726563,0 0,-6.445312 -1.929687,0 0,6.445312 -0.726563,0 0,-7.179687 4.390625,0 c 1.10416,7e-6 1.656243,0.497402 1.65625,1.492187 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4562\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 52.64013,69.571846 c -0.01563,0.135418 -0.03646,0.255209 -0.0625,0.359375 -0.130213,0.484375 -0.419275,0.78125 -0.867187,0.890625 -0.192712,0.04687 -0.463546,0.07031 -0.8125,0.07031 l -1.65625,-0.0078 0,2.609375 -0.6875,0 0,-9.820312 2.929687,0 c 0.286454,7e-6 0.544267,0.111986 0.773438,0.335937 0.255203,0.255215 0.382807,0.588548 0.382812,1 l 0,4.5625 m -0.71875,-0.101562 0,-4.484375 c -0.07292,-0.427078 -0.3099,-0.640619 -0.710937,-0.640625 l -1.945313,0.0078 0,5.875 1.921875,0 c 0.48958,1e-6 0.734371,-0.252603 0.734375,-0.757812\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4564\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 54.57763,66.485909 -0.710937,0 0,-0.710938 0.71875,0 -0.0078,0.710938 m 0,3.773437 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4566\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texReciever\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.7573175,85.699455 -0.78125,0 -2.296875,-4.320312 -1.0625,0 0,4.320312 -0.7265625,0 0,-9.835937 2.3046875,0 c 0.2552051,1e-5 0.507809,0.05209 0.7578125,0.15625 1.0260369,0.427092 1.5390572,1.278654 1.5390625,2.554687 -5.3e-6,0.640632 -0.1796926,1.226569 -0.5390625,1.757813 -0.3958377,0.583338 -0.8958372,0.916671 -1.5,1 l 2.3046875,4.367187 M 7.79638,78.574455 C 7.7963754,77.949463 7.6088756,77.444255 7.23388,77.05883 6.9213762,76.735923 6.5620016,76.574464 6.155755,76.574455 l -1.546875,0 0,4.078125 1.671875,0 c 0.3072882,5e-6 0.6197879,-0.169265 0.9375,-0.507812 0.3854122,-0.406244 0.5781204,-0.929681 0.578125,-1.570313\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4512\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 13.95263,82.332268 -3.414062,0 0,1.59375 c -2e-6,0.729167 0.367185,1.09375 1.101562,1.09375 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.1666679,-0.296874 -0.2500012,-0.640623 -0.2500005,-1.03125 l 0,-3.453125 c -7e-7,-0.588536 0.2031245,-1.078118 0.6093755,-1.46875 0.406248,-0.395826 0.906247,-0.593743 1.5,-0.59375 0.572913,7e-6 1.057287,0.190111 1.453125,0.570313 0.395828,0.375006 0.593745,0.848964 0.59375,1.421875 l -0.0078,1.875 m -0.710937,-1.726563 c -5e-6,-0.411453 -0.117192,-0.749994 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.406243 -0.960937,-0.40625 -0.343753,7e-6 -0.640628,0.09636 -0.890625,0.289063 -0.333335,0.255214 -0.500002,0.630214 -0.5,1.125 l 0,1.054687 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4514\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 19.007318,85.707268 -2.421875,0 c -0.375002,0 -0.669273,-0.132813 -0.882813,-0.398438 -0.197917,-0.244791 -0.296876,-0.55729 -0.296875,-0.9375 l 0,-4.546875 0.05469,-0.359375 c 0.06771,-0.44791 0.335936,-0.739576 0.804687,-0.875 0.177082,-0.05208 0.411456,-0.07812 0.703125,-0.07813 l 2.039063,0 0,0.671875 -2.140625,0 c -0.500002,7e-6 -0.750002,0.265632 -0.75,0.796875 l 0,4.414063 c 0.07291,0.411459 0.312498,0.617188 0.71875,0.617187 l 2.171875,0.0078 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4516\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 21.468255,76.90258 -0.726562,0 0,-1.039062 0.726562,0 0,1.039062 m 0.0078,8.796875 -0.734375,0 0,-7.164062 0.734375,0 0,7.164062\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4518\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 27.35888,82.332268 -3.414062,0 0,1.59375 c -2e-6,0.729167 0.367185,1.09375 1.101562,1.09375 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.166668,-0.296874 -0.250001,-0.640623 -0.25,-1.03125 l 0,-3.453125 c -1e-6,-0.588536 0.203124,-1.078118 0.609375,-1.46875 0.406248,-0.395826 0.906247,-0.593743 1.5,-0.59375 0.572913,7e-6 1.057287,0.190111 1.453125,0.570313 0.395828,0.375006 0.593745,0.848964 0.59375,1.421875 l -0.0078,1.875 m -0.710937,-1.726563 c -5e-6,-0.411453 -0.117192,-0.749994 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.406243 -0.960937,-0.40625 -0.343753,7e-6 -0.640628,0.09636 -0.890625,0.289063 -0.333335,0.255214 -0.500002,0.630214 -0.5,1.125 l 0,1.054687 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4520\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 30.710443,85.71508 -0.53125,0 -1.867188,-7.226562 0.671875,0 1.484375,5.5 1.445313,-5.484375 0.664062,0 -1.867187,7.210937\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4522\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 37.73388,82.332268 -3.414062,0 0,1.59375 c -2e-6,0.729167 0.367185,1.09375 1.101562,1.09375 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.231771 -1.28125,-0.695313 -0.166668,-0.296874 -0.250001,-0.640623 -0.25,-1.03125 l 0,-3.453125 c -10e-7,-0.588536 0.203124,-1.078118 0.609375,-1.46875 0.406248,-0.395826 0.906247,-0.593743 1.5,-0.59375 0.572913,7e-6 1.057287,0.190111 1.453125,0.570313 0.395828,0.375006 0.593745,0.848964 0.59375,1.421875 l -0.0078,1.875 m -0.710937,-1.726563 c -5e-6,-0.411453 -0.117192,-0.749994 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.406243 -0.960937,-0.40625 -0.343753,7e-6 -0.640628,0.09636 -0.890625,0.289063 -0.333335,0.255214 -0.500002,0.630214 -0.5,1.125 l 0,1.054687 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4524\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 42.60888,80.418205 -0.671875,0 c -3e-6,-0.812494 -0.466149,-1.218743 -1.398437,-1.21875 l -0.601563,0 0,6.507813 -0.726562,0 0,-7.179688 1.0625,0 c 0.83333,7e-6 1.4401,0.138028 1.820312,0.414063 0.260413,0.187506 0.432288,0.473964 0.515625,0.859375 l 0,0.617187\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4526\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 48.29638,81.316643 -0.710937,0 0,-0.710938 0.71875,0 -0.0078,0.710938 m 0,3.773437 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4528\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texComputer\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 8.22613,100.54581 -2.8359375,0 c -0.3489599,0 -0.6328138,-0.0937 -0.8515625,-0.28125 -0.2343758,-0.19791 -0.3515632,-0.468745 -0.3515625,-0.812495 l 0,-7.492188 c -7e-7,-0.395824 0.1302075,-0.700512 0.390625,-0.914062 0.1249988,-0.09895 0.2499986,-0.17447 0.375,-0.226563 0.2083316,-0.08332 0.4661439,-0.12499 0.7734375,-0.125 l 2.5,0 0,0.726563 -2.5,0 c -0.5572934,9e-6 -0.8359389,0.257821 -0.8359375,0.773437 l 0,7.101563 c -1.4e-6,0.375 0.2682275,0.5625 0.8046875,0.5625 l 2.53125,0 0,0.687495\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4531\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 13.72613,98.475502 c -5e-6,0.583335 -0.197921,1.083334 -0.59375,1.5 -0.395837,0.411458 -0.882816,0.617188 -1.460937,0.617188 -0.572919,0 -1.067711,-0.21094 -1.484375,-0.632813 -0.4114598,-0.427082 -0.6171887,-0.927082 -0.617188,-1.5 l 0,-3.03125 c -7e-7,-0.593744 0.2005199,-1.096348 0.601563,-1.507812 0.406248,-0.41666 0.906247,-0.624993 1.5,-0.625 0.578121,7e-6 1.0651,0.210944 1.460937,0.632812 0.395829,0.416673 0.593745,0.916672 0.59375,1.5 l 0,3.046875 m -0.726562,-0.15625 0,-2.742187 c -5e-6,-0.42187 -0.10938,-0.778641 -0.328125,-1.070313 -0.244796,-0.328119 -0.570316,-0.492181 -0.976563,-0.492187 -0.343753,6e-6 -0.64844,0.117193 -0.914062,0.351562 -0.328127,0.291673 -0.492189,0.69011 -0.492188,1.195313 l 0,2.757812 c -10e-7,0.489585 0.166665,0.882814 0.5,1.179688 0.276039,0.25 0.578122,0.375 0.90625,0.375 0.39583,0 0.721351,-0.164062 0.976563,-0.492188 0.218745,-0.281249 0.32812,-0.635415 0.328125,-1.0625\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4533\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 21.210505,100.53019 -0.710937,0 0,-5.273438 c -7e-6,-0.630202 -0.174486,-1.002598 -0.523438,-1.117187 -0.119797,-0.03645 -0.255214,-0.05468 -0.40625,-0.05469 l -1.007812,0 0,6.445313 -0.726563,0 0,-6.445313 -1.929687,0 0,6.445313 -0.726563,0 0,-7.179688 4.390625,0 c 1.10416,7e-6 1.656243,0.497403 1.65625,1.492188 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4535\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 26.72613,99.233315 c -0.01563,0.135417 -0.03646,0.255209 -0.0625,0.359375 -0.130213,0.48437 -0.419275,0.78125 -0.867187,0.89062 -0.192713,0.0469 -0.463546,0.0703 -0.8125,0.0703 l -1.65625,-0.008 0,2.60938 -0.6875,0 0,-9.820313 2.929687,0 c 0.286454,7e-6 0.544267,0.111986 0.773438,0.335938 0.255203,0.255214 0.382807,0.588547 0.382812,1 l 0,4.5625 m -0.71875,-0.101563 0,-4.484375 c -0.07292,-0.427077 -0.3099,-0.640618 -0.710937,-0.640625 l -1.945313,0.0078 0,5.875 1.921875,0 c 0.489579,0 0.734371,-0.252604 0.734375,-0.757813\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4537\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 32.03863,100.54581 -2.195312,0 c -1.119793,0 -1.679689,-0.50781 -1.679688,-1.523433 l -0.0078,-5.679687 0.726562,0 0,5.265625 c -1e-6,0.515626 0.07812,0.843751 0.234375,0.984375 0.166665,0.161459 0.398435,0.242188 0.695313,0.242187 l 1.507812,0 0,-6.492187 0.71875,0 0,7.20312\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4539\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 36.523005,94.038002 -1.320312,0 0,6.507808 -0.71875,0 0,-6.507808 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4541\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 41.88238,97.163002 -3.414062,0 0,1.59375 c -2e-6,0.729168 0.367185,1.093751 1.101562,1.09375 l 2.203125,0 0,0.687498 -2.507812,0 c -0.593752,0 -1.020835,-0.23177 -1.28125,-0.69531 -0.166668,-0.296875 -0.250001,-0.640624 -0.25,-1.03125 l 0,-3.453125 c -10e-7,-0.588536 0.203124,-1.078119 0.609375,-1.46875 0.406248,-0.395827 0.906247,-0.593743 1.5,-0.59375 0.572913,7e-6 1.057287,0.190111 1.453125,0.570312 0.395828,0.375006 0.593745,0.848964 0.59375,1.421875 l -0.0078,1.875 M 41.171443,95.43644 c -5e-6,-0.411453 -0.117192,-0.749995 -0.351563,-1.015625 -0.234379,-0.270827 -0.554691,-0.406244 -0.960937,-0.40625 -0.343753,6e-6 -0.640628,0.09636 -0.890625,0.289062 -0.333335,0.255214 -0.500002,0.630214 -0.5,1.125 l 0,1.054688 2.703125,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4543\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 46.75738,95.24894 -0.671875,0 c -3e-6,-0.812494 -0.466149,-1.218744 -1.398437,-1.21875 l -0.601563,0 0,6.50781 -0.726562,0 0,-7.179685 1.0625,0 c 0.83333,7e-6 1.4401,0.138027 1.820312,0.414062 0.260413,0.187507 0.432288,0.473965 0.515625,0.859375 l 0,0.617188\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4545\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 48.47613,96.147377 -0.710937,0 0,-0.710937 0.71875,0 -0.0078,0.710937 m 0,3.773438 -0.710937,0 0,-0.703125 0.71875,0 -0.0078,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4547\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texLocation\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 216.31387,11.561403 -3.47656,0 0,-9.8515622 0.69531,0 0,9.1484372 2.78125,0 0,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4457\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 221.56387,9.4910908 c 0,0.5833352 -0.19792,1.0833342 -0.59375,1.5000002 -0.39583,0.411458 -0.88281,0.617187 -1.46093,0.617187 -0.57292,0 -1.06771,-0.210937 -1.48438,-0.632812 -0.41146,-0.427083 -0.61719,-0.927082 -0.61719,-1.5000002 l 0,-3.03125 c 0,-0.5937443 0.20052,-1.096348 0.60157,-1.5078125 0.40624,-0.4166597 0.90624,-0.6249928 1.5,-0.625 0.57812,7.2e-6 1.0651,0.2109445 1.46093,0.6328125 0.39583,0.4166728 0.59375,0.9166723 0.59375,1.5 l 0,3.046875 m -0.72656,-0.15625 0,-2.7421875 c 0,-0.4218697 -0.10938,-0.7786401 -0.32812,-1.0703125 -0.2448,-0.3281187 -0.57032,-0.492181 -0.97657,-0.4921875 -0.34375,6.5e-6 -0.64844,0.1171939 -0.91406,0.3515625 -0.32813,0.2916725 -0.49219,0.6901096 -0.49219,1.1953125 l 0,2.7578125 c 0,0.489585 0.16667,0.8828142 0.5,1.1796872 0.27604,0.250001 0.57813,0.375001 0.90625,0.375 0.39583,10e-7 0.72135,-0.164061 0.97657,-0.492187 0.21874,-0.281249 0.32812,-0.6354151 0.32812,-1.0625002\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4459\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 226.61856,11.553591 -2.42187,0 c -0.37501,0 -0.66928,-0.132813 -0.88282,-0.398438 -0.19791,-0.244791 -0.29687,-0.55729 -0.29687,-0.9375 l 0,-4.5468747 0.0547,-0.359375 c 0.0677,-0.44791 0.33593,-0.7395764 0.80468,-0.875 0.17708,-0.052076 0.41146,-0.078118 0.70313,-0.078125 l 2.03906,0 0,0.671875 -2.14062,0 c -0.50001,6.5e-6 -0.75001,0.2656312 -0.75,0.796875 l 0,4.4140627 c 0.0729,0.411459 0.31249,0.617188 0.71875,0.617187 l 2.17187,0.0078 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4461\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 232.88419,11.537966 -0.41407,0 c -0.32292,0 -0.59896,-0.177083 -0.82812,-0.53125 -0.3073,0.354167 -0.71876,0.53125 -1.23438,0.53125 l -1.17968,0 c -0.81771,0 -1.22657,-0.445312 -1.22657,-1.335938 l 0,-4.1953122 c 0,-1.10416 0.53646,-1.6562428 1.60938,-1.65625 l 2.46875,0 -0.008,5.3984375 c -1e-5,0.7291677 0.27082,1.0937507 0.8125,1.0937497 l 0,0.695313 m -1.51563,-1.7109377 0,-4.796875 -1.78906,0 c -0.57813,6.5e-6 -0.86719,0.3125062 -0.86719,0.9375 l 0,4.2734377 c 0,0.406251 0.23958,0.609375 0.71875,0.609375 l 0.72656,0 c 0.80729,0 1.21094,-0.341145 1.21094,-1.0234377\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4463\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 237.11075,5.0535908 -1.32031,0 0,6.5078122 -0.71875,0 0,-6.5078122 -1.27344,0 0,-0.6875 1.27344,0 0,-2.65625 0.71875,0 0,2.65625 1.32031,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4465\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 239.42325,2.7489033 -0.72656,0 0,-1.0390625 0.72656,0 0,1.0390625 m 0.008,8.7968747 -0.73437,0 0,-7.1640622 0.73437,0 0,7.1640622\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4467\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 245.34512,9.4910908 c 0,0.5833352 -0.19792,1.0833342 -0.59375,1.5000002 -0.39583,0.411458 -0.88281,0.617187 -1.46093,0.617187 -0.57292,0 -1.06771,-0.210937 -1.48438,-0.632812 -0.41146,-0.427083 -0.61719,-0.927082 -0.61719,-1.5000002 l 0,-3.03125 c 0,-0.5937443 0.20052,-1.096348 0.60157,-1.5078125 0.40624,-0.4166597 0.90624,-0.6249928 1.5,-0.625 0.57812,7.2e-6 1.0651,0.2109445 1.46093,0.6328125 0.39583,0.4166728 0.59375,0.9166723 0.59375,1.5 l 0,3.046875 m -0.72656,-0.15625 0,-2.7421875 c 0,-0.4218697 -0.10938,-0.7786401 -0.32812,-1.0703125 -0.2448,-0.3281187 -0.57032,-0.492181 -0.97657,-0.4921875 -0.34375,6.5e-6 -0.64844,0.1171939 -0.91406,0.3515625 -0.32813,0.2916725 -0.49219,0.6901096 -0.49219,1.1953125 l 0,2.7578125 c 0,0.489585 0.16667,0.8828142 0.5,1.1796872 0.27604,0.250001 0.57813,0.375001 0.90625,0.375 0.39583,10e-7 0.72135,-0.164061 0.97657,-0.492187 0.21874,-0.281249 0.32812,-0.6354151 0.32812,-1.0625002\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4469\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 250.68887,11.577028 -0.71093,0 0,-5.2734372 c -1e-5,-0.4218694 -0.0755,-0.7291607 -0.22657,-0.921875 -0.16146,-0.1718687 -0.39583,-0.2578061 -0.70312,-0.2578125 l -1.5,0 0,6.4531247 -0.71094,-0.01563 0,-7.1953122 2.1875,0 c 1.11979,7.2e-6 1.67968,0.5078191 1.67969,1.5234375 l -0.0156,5.6874997\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4471\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 256.59512,7.1629658 -0.71093,0 0,-0.7109375 0.71875,0 -0.008,0.7109375 m 0,3.7734372 -0.71093,0 0,-0.703125 0.71875,0 -0.008,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4473\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texFrequency\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 216.97794,33.746536 -3.4375,0 0,3.375 3.23437,0 0,0.703125 -3.23437,0 0,5.085938 -0.70313,0 0,-9.867188 4.14063,0 0,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4476\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 221.59512,37.598099 -0.67187,0 c -1e-5,-0.812494 -0.46615,-1.218744 -1.39844,-1.21875 l -0.60156,0 0,6.507812 -0.72656,0 0,-7.179687 1.0625,0 c 0.83333,7e-6 1.4401,0.138028 1.82031,0.414062 0.26041,0.187507 0.43229,0.473965 0.51562,0.859375 l 0,0.617188\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4478\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 226.93887,39.512161 -3.41406,0 0,1.59375 c 0,0.729168 0.36719,1.093751 1.10156,1.09375 l 2.20313,0 0,0.6875 -2.50781,0 c -0.59376,0 -1.02084,-0.23177 -1.28125,-0.695312 -0.16667,-0.296874 -0.25,-0.640624 -0.25,-1.03125 l 0,-3.453125 c 0,-0.588536 0.20312,-1.078119 0.60937,-1.46875 0.40625,-0.395827 0.90625,-0.593743 1.5,-0.59375 0.57291,7e-6 1.05729,0.190111 1.45313,0.570312 0.39582,0.375007 0.59374,0.848964 0.59375,1.421875 l -0.008,1.875 m -0.71093,-1.726562 c -1e-5,-0.411453 -0.1172,-0.749994 -0.35157,-1.015625 -0.23438,-0.270827 -0.55469,-0.406244 -0.96093,-0.40625 -0.34376,6e-6 -0.64063,0.09636 -0.89063,0.289062 -0.33333,0.255215 -0.5,0.630214 -0.5,1.125 l 0,1.054688 2.70313,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4480\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 232.49356,45.512161 -0.69531,0 0,-2.617187 -1.17188,0.0078 c -0.84896,0.02604 -1.45833,-0.117187 -1.82812,-0.429687 -0.14063,-0.119791 -0.25,-0.315104 -0.32813,-0.585938 l -0.0625,-0.359375 0,-4.492187 c 0,-0.432286 0.13281,-0.776035 0.39844,-1.03125 0.21354,-0.203118 0.46615,-0.304681 0.75781,-0.304688 l 2.92969,0 0,9.8125 m -0.71875,-3.335937 0,-5.773438 -1.9375,0 c -0.40625,7e-6 -0.64583,0.200527 -0.71875,0.601563 l 0,4.421875 c 0,0.500001 0.24219,0.75 0.72656,0.75 l 1.92969,0\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4482\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 237.84512,42.894974 -2.19531,0 c -1.11979,0 -1.67969,-0.507812 -1.67969,-1.523438 l -0.008,-5.679687 0.72656,0 0,5.265625 c 0,0.515626 0.0781,0.843751 0.23438,0.984375 0.16666,0.161459 0.39843,0.242188 0.69531,0.242187 l 1.50781,0 0,-6.492187 0.71875,0 0,7.203125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4484\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 243.37637,39.512161 -3.41406,0 0,1.59375 c 0,0.729168 0.36719,1.093751 1.10156,1.09375 l 2.20313,0 0,0.6875 -2.50781,0 c -0.59376,0 -1.02084,-0.23177 -1.28125,-0.695312 -0.16667,-0.296874 -0.25,-0.640624 -0.25,-1.03125 l 0,-3.453125 c 0,-0.588536 0.20312,-1.078119 0.60937,-1.46875 0.40625,-0.395827 0.90625,-0.593743 1.5,-0.59375 0.57291,7e-6 1.05729,0.190111 1.45313,0.570312 0.39582,0.375007 0.59374,0.848964 0.59375,1.421875 l -0.008,1.875 m -0.71093,-1.726562 c -1e-5,-0.411453 -0.1172,-0.749994 -0.35157,-1.015625 -0.23438,-0.270827 -0.55469,-0.406244 -0.96093,-0.40625 -0.34376,6e-6 -0.64063,0.09636 -0.89063,0.289062 -0.33333,0.255215 -0.5,0.630214 -0.5,1.125 l 0,1.054688 2.70313,0 0,-1.046875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4486\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 248.72012,42.910599 -0.71093,0 0,-5.273438 c -1e-5,-0.421869 -0.0755,-0.72916 -0.22657,-0.921875 -0.16146,-0.171868 -0.39583,-0.257806 -0.70312,-0.257812 l -1.5,0 0,6.453125 -0.71094,-0.01563 0,-7.195313 2.1875,0 c 1.11979,7e-6 1.67968,0.507819 1.67969,1.523438 l -0.0156,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4488\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 253.74356,42.887161 -2.42187,0 c -0.37501,0 -0.66928,-0.132812 -0.88282,-0.398437 -0.19791,-0.244791 -0.29687,-0.557291 -0.29687,-0.9375 l 0,-4.546875 0.0547,-0.359375 c 0.0677,-0.44791 0.33593,-0.739577 0.80468,-0.875 0.17708,-0.05208 0.41146,-0.07812 0.70313,-0.07813 l 2.03906,0 0,0.671875 -2.14062,0 c -0.50001,6e-6 -0.75001,0.265631 -0.75,0.796875 l 0,4.414062 c 0.0729,0.411459 0.31249,0.617188 0.71875,0.617188 l 2.17187,0.0078 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4490\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 259.02481,35.684036 -2.63281,9.101563 c -0.125,0.432289 -0.40365,0.648435 -0.83594,0.648437 l -0.63281,0 0,-0.65625 0.35937,0 c 0.29167,-2e-6 0.49479,-0.205731 0.60938,-0.617187 l 0.66406,-2.398438 -1.73437,-6.078125 0.73437,0 1.39844,4.828125 1.35156,-4.828125 0.71875,0\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4492\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 264.53262,38.496536 -0.71093,0 0,-0.710937 0.71875,0 -0.008,0.710937 m 0,3.773438 -0.71093,0 0,-0.703125 0.71875,0 -0.008,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4494\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texEmail\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 216.64836,58.553944 -4.15625,0 0,-9.835938 4.15625,0 0,0.703125 -3.46094,0 0,3.351563 2.15625,0 0,0.6875 -2.15625,0 0,4.429687 3.46094,0 0,0.664063\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4497\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 222.2968,55.514881 -4.46875,0 0,-0.671875 4.46875,0 0,0.671875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4499\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 229.68742,58.546131 -0.71093,0 0,-5.273437 c -1e-5,-0.630203 -0.17449,-1.002598 -0.52344,-1.117188 -0.1198,-0.03645 -0.25521,-0.05468 -0.40625,-0.05469 l -1.00781,0 0,6.445312 -0.72657,0 0,-6.445312 -1.92968,0 0,6.445312 -0.72657,0 0,-7.179687 4.39063,0 c 1.10416,7e-6 1.65624,0.497402 1.65625,1.492187 l -0.0156,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4501\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 235.99211,58.538319 -0.41406,0 c -0.32292,0 -0.59896,-0.177084 -0.82813,-0.53125 -0.30729,0.354166 -0.71875,0.53125 -1.23437,0.53125 l -1.17969,0 c -0.81771,0 -1.22656,-0.445312 -1.22656,-1.335938 l 0,-4.195312 c 0,-1.10416 0.53646,-1.656243 1.60937,-1.65625 l 2.46875,0 -0.008,5.398437 c 0,0.729168 0.27083,1.093751 0.8125,1.09375 l 0,0.695313 m -1.51562,-1.710938 0,-4.796875 -1.78907,0 c -0.57812,7e-6 -0.86719,0.312506 -0.86718,0.9375 l 0,4.273438 c -1e-5,0.406251 0.23958,0.609375 0.71875,0.609375 l 0.72656,0 c 0.80729,0 1.21093,-0.341145 1.21094,-1.023438\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4503\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 238.21867,49.749256 -0.72656,0 0,-1.039062 0.72656,0 0,1.039062 m 0.008,8.796875 -0.73438,0 0,-7.164062 0.73438,0 0,7.164062\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4505\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 242.27336,57.819569 0,0.726562 c -0.98958,0 -1.63542,-0.125 -1.9375,-0.375 -0.21354,-0.177083 -0.32031,-0.510416 -0.32031,-1 l -0.008,-8.460937 0.71875,0 -0.008,8.429687 c 0,0.307293 0.19531,0.513022 0.58594,0.617188 0.16146,0.04167 0.48437,0.0625 0.96875,0.0625\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4507\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 247.89055,54.163319 -0.71094,0 0,-0.710938 0.71875,0 -0.008,0.710938 m 0,3.773437 -0.71094,0 0,-0.703125 0.71875,0 -0.008,0.703125\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4509\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <rect	\n";
	svgout << "	     style=\"fill:#ffffff;fill-opacity:1;stroke:#000000;stroke-width:1;stroke-opacity:1;display:inline;opacity:1\"	\n";
	svgout << "	     id=\"rect3902\"	\n";
	svgout << "	     width=\"252.43059\"	\n";
	svgout << "	     height=\"94.587128\"	\n";
	svgout << "	     x=\"112.89983\"	\n";
	svgout << "	     y=\"110.91171\" />	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:11px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;display:inline;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texHourlyCount\">	\n";
	svgout << "	     transform=\"matrix(0.94063047,0,0,0.94063047,0.32778914,9.8148985)\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 10.302417,162.75627 -0.7031247,0 0,-5.08594 -3.34375,0 0,5.08594 -0.734375,0 0,-9.84375 0.734375,0 0,4.0625 3.34375,0 0,-4.0625 0.7031247,0 0,9.84375\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4414\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 15.989917,160.69377 c -5e-6,0.58334 -0.197921,1.08334 -0.59375,1.5 -0.395837,0.41146 -0.882816,0.61719 -1.460937,0.61719 -0.572919,0 -1.06771,-0.21094 -1.484375,-0.63281 -0.411459,-0.42709 -0.617188,-0.92709 -0.617188,-1.5 l 0,-3.03125 c 0,-0.59375 0.20052,-1.09635 0.601563,-1.50782 0.406248,-0.41666 0.906248,-0.62499 1.5,-0.625 0.578121,1e-5 1.0651,0.21095 1.460937,0.63282 0.395829,0.41667 0.593745,0.91667 0.59375,1.5 l 0,3.04687 m -0.726562,-0.15625 0,-2.74219 c -4e-6,-0.42187 -0.109379,-0.77864 -0.328125,-1.07031 -0.244795,-0.32812 -0.570316,-0.49218 -0.976563,-0.49219 -0.343752,1e-5 -0.648439,0.1172 -0.914062,0.35157 -0.328127,0.29167 -0.492189,0.69011 -0.492188,1.19531 l 0,2.75781 c -1e-6,0.48959 0.166665,0.88282 0.5,1.17969 0.27604,0.25 0.578123,0.375 0.90625,0.375 0.39583,0 0.721351,-0.16406 0.976563,-0.49219 0.218746,-0.28125 0.328121,-0.63541 0.328125,-1.0625\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4416\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 21.333667,162.76408 -2.195312,0 c -1.119793,0 -1.679688,-0.50781 -1.679688,-1.52343 l -0.0078,-5.67969 0.726562,0 0,5.26562 c -1e-6,0.51563 0.07812,0.84375 0.234375,0.98438 0.166665,0.16146 0.398436,0.24219 0.695313,0.24219 l 1.507812,0 0,-6.49219 0.71875,0 0,7.20312\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4418\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 26.146167,157.46721 -0.671875,0 c -3e-6,-0.8125 -0.466149,-1.21874 -1.398437,-1.21875 l -0.601563,0 0,6.50781 -0.726562,0 0,-7.17969 1.0625,0 c 0.83333,1e-5 1.440101,0.13803 1.820312,0.41407 0.260413,0.1875 0.432288,0.47396 0.515625,0.85937 l 0,0.61719\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4420\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 29.65398,162.0219 0,0.72656 c -0.989586,0 -1.635418,-0.125 -1.9375,-0.375 -0.213543,-0.17708 -0.320313,-0.51042 -0.320313,-1 l -0.0078,-8.46094 0.71875,0 -0.0078,8.42969 c -10e-7,0.30729 0.195311,0.51302 0.585938,0.61719 0.161456,0.0417 0.484372,0.0625 0.96875,0.0625\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4422\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 34.700855,155.55315 -2.632813,9.10156 c -0.125002,0.43229 -0.403647,0.64843 -0.835937,0.64844 l -0.632813,0 0,-0.65625 0.359375,0 c 0.291666,-10e-6 0.494791,-0.20573 0.609375,-0.61719 l 0.664063,-2.39844 -1.734375,-6.07812 0.734375,0 1.398437,4.82812 1.351563,-4.82812 0.71875,0\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4424\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 43.294605,162.75627 -2.421875,0 c -0.375002,0 -0.669272,-0.13281 -0.882813,-0.39844 -0.197917,-0.24479 -0.296875,-0.55729 -0.296875,-0.9375 l 0,-4.54687 0.05469,-0.35938 c 0.06771,-0.44791 0.335936,-0.73957 0.804687,-0.875 0.177082,-0.0521 0.411457,-0.0781 0.703125,-0.0781 l 2.039063,0 0,0.67187 -2.140625,0 c -0.500002,10e-6 -0.750002,0.26564 -0.75,0.79688 l 0,4.41406 c 0.07292,0.41146 0.312498,0.61719 0.71875,0.61719 l 2.171875,0.008 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4426\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 48.833667,160.69377 c -5e-6,0.58334 -0.197921,1.08334 -0.59375,1.5 -0.395837,0.41146 -0.882816,0.61719 -1.460937,0.61719 -0.572919,0 -1.06771,-0.21094 -1.484375,-0.63281 -0.411459,-0.42709 -0.617188,-0.92709 -0.617188,-1.5 l 0,-3.03125 c 0,-0.59375 0.20052,-1.09635 0.601563,-1.50782 0.406248,-0.41666 0.906248,-0.62499 1.5,-0.625 0.578121,1e-5 1.0651,0.21095 1.460937,0.63282 0.395829,0.41667 0.593745,0.91667 0.59375,1.5 l 0,3.04687 m -0.726562,-0.15625 0,-2.74219 c -4e-6,-0.42187 -0.109379,-0.77864 -0.328125,-1.07031 -0.244795,-0.32812 -0.570316,-0.49218 -0.976563,-0.49219 -0.343752,1e-5 -0.648439,0.1172 -0.914062,0.35157 -0.328127,0.29167 -0.492189,0.69011 -0.492188,1.19531 l 0,2.75781 c -10e-7,0.48959 0.166665,0.88282 0.5,1.17969 0.27604,0.25 0.578123,0.375 0.90625,0.375 0.39583,0 0.721351,-0.16406 0.976563,-0.49219 0.218746,-0.28125 0.328121,-0.63541 0.328125,-1.0625\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4428\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 54.177417,162.76408 -2.195312,0 c -1.119793,0 -1.679688,-0.50781 -1.679688,-1.52343 l -0.0078,-5.67969 0.726562,0 0,5.26562 c -10e-7,0.51563 0.07812,0.84375 0.234375,0.98438 0.166665,0.16146 0.398436,0.24219 0.695313,0.24219 l 1.507812,0 0,-6.49219 0.71875,0 0,7.20312\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4430\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 59.458667,162.77971 -0.710937,0 0,-5.27344 c -4e-6,-0.42187 -0.07552,-0.72916 -0.226563,-0.92187 -0.161462,-0.17187 -0.395836,-0.25781 -0.703125,-0.25782 l -1.5,0 0,6.45313 -0.710937,-0.0156 0,-7.19531 2.1875,0 c 1.119787,1e-5 1.679683,0.50782 1.679687,1.52344 l -0.01563,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4432\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 63.974292,156.25627 -1.320312,0 0,6.50781 -0.71875,0 0,-6.50781 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4434\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 73.036792,162.75627 -0.703125,0 0,-5.39844 c -4e-6,-0.74999 -0.382816,-1.12499 -1.148437,-1.125 l -1.3125,0 0,6.52344 -0.71875,0 0,-9.83594 0.71875,-0.008 0,2.65625 1.476562,0 c 1.119788,1e-5 1.679683,0.4974 1.679688,1.49219 l 0.0078,5.69531\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4436\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 75.599292,153.95158 -0.726562,0 0,-1.03906 0.726562,0 0,1.03906 m 0.0078,8.79688 -0.734375,0 0,-7.16406 0.734375,0 0,7.16406\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4438\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 80.81023,156.74065 -0.71875,0 c -0.265628,-0.35416 -0.585941,-0.53125 -0.960938,-0.53125 -0.229169,0 -0.424481,0.0365 -0.585937,0.10937 -0.07813,0.0521 -0.125002,0.0807 -0.140625,0.0859 -0.03646,0.026 -0.09636,0.0755 -0.179688,0.14844 -0.171876,0.11459 -0.257814,0.38021 -0.257812,0.79687 -2e-6,0.41667 0.192707,0.78386 0.578125,1.10156 l 1.1875,0.72657 c 0.734371,0.44792 1.101558,0.98698 1.101562,1.61718 -4e-6,0.51042 -0.156254,0.95834 -0.46875,1.34375 -0.359378,0.44271 -0.83594,0.66407 -1.429687,0.66407 -0.994793,0 -1.640626,-0.54948 -1.9375,-1.64844 l 0.679687,0 c 0.249999,0.66146 0.677082,0.99219 1.28125,0.99219 0.343748,0 0.630206,-0.11459 0.859375,-0.34375 0.229164,-0.23438 0.343747,-0.52344 0.34375,-0.86719 -3e-6,-0.41146 -0.242191,-0.77604 -0.726562,-1.09375 l -0.882813,-0.57813 c -0.09896,-0.0625 -0.346355,-0.2552 -0.742187,-0.57812 -0.343751,-0.36979 -0.515626,-0.8151 -0.515625,-1.33594 -10e-7,-0.54687 0.16927,-0.98697 0.507812,-1.32031 0.33854,-0.33854 0.783852,-0.50781 1.335938,-0.50781 0.86458,0 1.421871,0.40625 1.671875,1.21875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4440\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 85.255542,156.25627 -1.320312,0 0,6.50781 -0.71875,0 0,-6.50781 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4442\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 90.646167,160.69377 c -5e-6,0.58334 -0.197921,1.08334 -0.59375,1.5 -0.395837,0.41146 -0.882816,0.61719 -1.460937,0.61719 -0.572919,0 -1.06771,-0.21094 -1.484375,-0.63281 -0.411459,-0.42709 -0.617188,-0.92709 -0.617188,-1.5 l 0,-3.03125 c 0,-0.59375 0.20052,-1.09635 0.601563,-1.50782 0.406248,-0.41666 0.906248,-0.62499 1.5,-0.625 0.578121,1e-5 1.0651,0.21095 1.460937,0.63282 0.395829,0.41667 0.593745,0.91667 0.59375,1.5 l 0,3.04687 m -0.726562,-0.15625 0,-2.74219 c -4e-6,-0.42187 -0.109379,-0.77864 -0.328125,-1.07031 -0.244795,-0.32812 -0.570316,-0.49218 -0.976563,-0.49219 -0.343752,1e-5 -0.648439,0.1172 -0.914062,0.35157 -0.328127,0.29167 -0.492189,0.69011 -0.492188,1.19531 l 0,2.75781 c -1e-6,0.48959 0.166665,0.88282 0.5,1.17969 0.27604,0.25 0.578123,0.375 0.90625,0.375 0.39583,0 0.721351,-0.16406 0.976563,-0.49219 0.218746,-0.28125 0.328121,-0.63541 0.328125,-1.0625\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4444\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 96.177417,163.95158 c -5e-6,0.36979 -0.1224,0.69011 -0.367187,0.96094 -0.239588,0.27083 -0.541671,0.40625 -0.90625,0.40625 l -2.804688,0 0,-0.71094 2.71875,0 0.210938,-0.0391 c 0.312496,-0.125 0.468746,-0.42969 0.46875,-0.91406 l 0,-0.89844 -2.007813,0 c -0.593751,0 -1.002605,-0.21875 -1.226562,-0.65625 -0.06771,-0.13021 -0.125001,-0.35677 -0.171875,-0.67969 l 0,-4.38281 c -10e-7,-0.98437 0.455728,-1.47655 1.367187,-1.47656 l 2.71875,0 0,8.39062 m -0.710937,-1.91406 0,-5.78906 -1.875,0 c -0.520835,1e-5 -0.781252,0.32032 -0.78125,0.96094 l 0,4.03906 c -2e-6,0.23438 0.07812,0.42448 0.234375,0.57031 0.161456,0.14584 0.359373,0.21875 0.59375,0.21875 l 1.828125,0\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4446\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 101.02117,157.46721 -0.67188,0 c 0,-0.8125 -0.466147,-1.21874 -1.398435,-1.21875 l -0.601563,0 0,6.50781 -0.726562,0 0,-7.17969 1.0625,0 c 0.83333,1e-5 1.4401,0.13803 1.82031,0.41407 0.26042,0.1875 0.43229,0.47396 0.51563,0.85937 l 0,0.61719\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4448\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 107.12273,162.74065 -0.41406,0 c -0.32292,0 -0.59897,-0.17709 -0.82813,-0.53125 -0.30729,0.35416 -0.71875,0.53125 -1.23437,0.53125 l -1.17969,0 c -0.81771,0 -1.22656,-0.44532 -1.22656,-1.33594 l 0,-4.19531 c 0,-1.10416 0.53645,-1.65625 1.60937,-1.65625 l 2.46875,0 -0.008,5.39843 c -1e-5,0.72917 0.27083,1.09375 0.8125,1.09375 l 0,0.69532 m -1.51563,-1.71094 0,-4.79688 -1.78906,0 c -0.57812,1e-5 -0.86719,0.31251 -0.86719,0.9375 l 0,4.27344 c 0,0.40625 0.23959,0.60938 0.71875,0.60938 l 0.72657,0 c 0.80729,0 1.21093,-0.34115 1.21093,-1.02344\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4450\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 114.28679,162.74846 -0.71094,0 0,-5.27344 c 0,-0.6302 -0.17448,-1.0026 -0.52343,-1.11719 -0.1198,-0.0365 -0.25522,-0.0547 -0.40625,-0.0547 l -1.00782,0 0,6.44531 -0.72656,0 0,-6.44531 -1.92969,0 0,6.44531 -0.72656,0 0,-7.17969 4.39063,0 c 1.10416,1e-5 1.65624,0.4974 1.65625,1.49219 l -0.0156,5.6875\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4452\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 116.20867,158.36565 -0.71094,0 0,-0.71094 0.71875,0 -0.008,0.71094 m 0,3.77343 -0.71094,0 0,-0.70312 0.71875,0 -0.008,0.70312\"	\n";
	svgout << "	       style=\"font-size:16px;fill:#000000;fill-opacity:1;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4454\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	  </g>	\n";

	svgout << "	<g  \n";
	svgout << "		id=\"Version\">  \n";
	svgout << "	<text  \n";
	svgout << "		xml:space=\"preserve\"  \n";
	svgout << "		style=\"font-size:20px;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;fill:#ff0016;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Sans Bold\"  \n";
	svgout << "		x=\"405.43259\"  \n";
	svgout << "		y=\"217.30455\"  \n";
	svgout << "		id=\"text4735\"  \n";
	svgout << "		sodipodi:linespacing=\"125%\"><tspan  \n";
	svgout << "			sodipodi:role=\"line\"  \n";
	svgout << "			id=\"tspan4737\"  \n";
	svgout << "			x=\"405.43259\"  \n";
	svgout << "			y=\"217.30455\"  \n";
	svgout << "			style=\"font-size:10px;font-weight:normal;fill:#ff0016;fill-opacity:1;-inkscape-font-specification:Ubuntu\">Bolidozor.cz  -   RMOBgen</tspan></text>  \n";
	svgout << "	<text  \n";
	svgout << "		xml:space=\"preserve\"  \n";
	svgout << "		style=\"font-size:11px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:end;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:end;fill:#ff0016;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"  \n";
	svgout << "		x=\"638.93542\"  \n";
	svgout << "		y=\"217.30455\"  \n";
	svgout << "		id=\"text4739\"  \n";
	svgout << "		sodipodi:linespacing=\"125%\"><tspan  \n";
	svgout << "			sodipodi:role=\"line\"  \n";
	svgout << "			id=\"tspan4741\"  \n";
	svgout << "			x=\"638.93542\"  \n";
	svgout << "			y=\"217.30455\"  \n";
	svgout << "			style=\"font-size:9px;fill:#ff0016;fill-opacity:1\">ver.:</tspan></text>  \n";
	svgout << "	<text  \n";
	svgout << "		xml:space=\"preserve\"  \n";
	svgout << "		style=\"font-size:20px;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:end;fill:#ff0016;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Sans Bold\"  \n";
	svgout << "		x=\"672\"  \n";
	svgout << "		y=\"217.30455\"  \n";
	svgout << "		id=\"text4743\"  \n";
	svgout << "		sodipodi:linespacing=\"125%\"><tspan  \n";
	svgout << "			sodipodi:role=\"line\"  \n";
	svgout << "			id=\"tspan4745\"  \n";
	svgout << "			x=\"672\"  \n";
	svgout << "			y=\"217.30455\"  \n";

	///// Ver ver version verze Ver.: Ver.:
	svgout << "			style=\"font-size:10px;font-weight:normal;fill:#ff0016;fill-opacity:1;text-align:start;-inkscape-font-specification:Ubuntu\">1.6 MultiGen</tspan></text>  \n";
	svgout << "	</g>  \n";


	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"666.98639\"	\n";
	svgout << "	     y=\"118.50355\"	\n";
	svgout << "	     id=\"editAvgMonth\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3970\"	\n";
	svgout << "	       x=\"666.98639\"	\n";
	svgout << "	       y=\"118.50355\"	\n";
	svgout << "	       style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">"<< MINhourcount + ((MAXhourcount - MINhourcount) / 2) <<"</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"666.72394\"	\n";
	svgout << "	     y=\"207.47627\"	\n";
	svgout << "	     id=\"editMaxMonth\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3974\"	\n";
	svgout << "	       x=\"666.72394\"	\n";
	svgout << "	       y=\"207.47627\"	\n";
	svgout << "	       style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">"<< MAXhourcount <<"</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:center;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:middle;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"238.83513\"	\n";
	svgout << "	     y=\"108.27513\"	\n";
	svgout << "	     id=\"text3840\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3842\"	\n";
	svgout << "	       x=\"238.83513\"	\n";
	svgout << "	       y=\"108.27513\"	\n";
	svgout << "	       style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;font-family:Ubuntu;-inkscape-font-specification:Ubuntu;fill:#9000d3;fill-opacity:1\">" << utc->tm_year+1900 << " - " << utc->tm_mon+1 << " - " <<  utc->tm_mday << " </tspan></text>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;opacity:0.77999998;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	     id=\"text3856\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 115.23361,201.617 c 0,1.00261 -0.11849,1.88673 -0.35547,2.65235 -0.35547,1.15299 -0.92513,1.72949 -1.70898,1.72949 -0.75651,0 -1.31478,-0.58105 -1.67481,-1.74316 -0.24153,-0.7793 -0.3623,-1.65885 -0.3623,-2.63868 0,-2.8802 0.68587,-4.3203 2.05762,-4.32031 1.36262,10e-6 2.04394,1.44011 2.04394,4.32031 m -0.61523,0 c -1e-5,-0.81575 -0.0729,-1.5358 -0.21875,-2.16015 -0.23699,-1.02083 -0.6403,-1.53124 -1.20996,-1.53125 -0.56055,1e-5 -0.96843,0.51042 -1.22364,1.53125 -0.1595,0.63802 -0.23925,1.35808 -0.23925,2.16015 0,0.76108 0.082,1.48341 0.24609,2.167 0.24609,1.02995 0.64485,1.54492 1.19629,1.54492 0.55143,0 0.95475,-0.5127 1.20996,-1.53809 0.1595,-0.64257 0.23925,-1.36718 0.23926,-2.17383\"	\n";
	svgout << "	       style=\"font-size:14px;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4394\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	     id=\"text3860\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 121.71308,213.06361 c 0,1.00261 -0.11849,1.88673 -0.35547,2.65235 -0.35547,1.15299 -0.92513,1.72949 -1.70898,1.72949 -0.75651,0 -1.31478,-0.58105 -1.67481,-1.74316 -0.24153,-0.7793 -0.3623,-1.65886 -0.3623,-2.63868 0,-2.8802 0.68587,-4.3203 2.05762,-4.32031 1.36262,1e-5 2.04394,1.44011 2.04394,4.32031 m -0.61523,0 c -10e-6,-0.81575 -0.0729,-1.5358 -0.21875,-2.16015 -0.23699,-1.02083 -0.64031,-1.53124 -1.20996,-1.53125 -0.56055,1e-5 -0.96843,0.51042 -1.22364,1.53125 -0.1595,0.63802 -0.23926,1.35808 -0.23925,2.16015 -1e-5,0.76108 0.082,1.48341 0.24609,2.167 0.24609,1.02995 0.64485,1.54492 1.19629,1.54492 0.55143,0 0.95475,-0.5127 1.20996,-1.53809 0.1595,-0.64257 0.23925,-1.36718 0.23926,-2.17383\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4357\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 126.29316,217.37025 -0.61523,0 0,-4.72363 c -1e-5,-0.65624 -0.33497,-0.98437 -1.00489,-0.98437 l -1.14844,0 0,5.708 -0.6289,0 0,-8.60644 0.6289,-0.007 0,2.32422 1.292,0 c 0.97981,1e-5 1.46972,0.43523 1.46972,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4359\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 159.67304,215.381 -1.31933,0 -0.007,1.98925 -0.63574,0 0,-1.98925 -2.55664,0 0,-0.56739 1.81836,-6.06347 0.6289,0 -1.81152,5.98144 1.9209,0 0,-1.85937 0.63574,0 0,1.85937 1.3125,0 0.0137,0.64942\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4361\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 163.89082,217.37025 -0.61524,0 0,-4.72363 c 0,-0.65624 -0.33496,-0.98437 -1.00488,-0.98437 l -1.14844,0 0,5.708 -0.62891,0 0,-8.60644 0.62891,-0.007 0,2.32422 1.29199,0 c 0.97982,1e-5 1.46973,0.43523 1.46973,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4363\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 200.70918,215.4015 c -1e-5,1.01628 -0.4603,1.65886 -1.38086,1.92774 -0.26433,0.0775 -0.52865,0.11621 -0.79297,0.11621 -1.33073,0 -2.04851,-0.67904 -2.15332,-2.03711 l -0.0273,-0.35547 c -0.005,-0.0775 -0.007,-0.15267 -0.007,-0.22558 0,-0.92969 0.4261,-1.6543 1.27832,-2.17383 -0.59245,-0.4694 -0.88868,-1.07324 -0.88867,-1.81153 -1e-5,-0.57876 0.15722,-1.06639 0.47168,-1.46289 0.33723,-0.43293 0.7884,-0.6494 1.35351,-0.64941 0.57422,1e-5 1.02994,0.23015 1.36719,0.69043 0.29166,0.39649 0.43749,0.87045 0.4375,1.42187 -1e-5,0.7155 -0.30079,1.31935 -0.90235,1.81153 0.82943,0.47852 1.24414,1.39453 1.24415,2.74804 m -0.91602,-4.5664 c 0,-0.42838 -0.098,-0.77701 -0.29395,-1.0459 -0.21875,-0.30077 -0.53548,-0.45116 -0.95019,-0.45117 -0.4056,1e-5 -0.72006,0.15268 -0.94336,0.45801 -0.20052,0.27344 -0.30078,0.61979 -0.30078,1.03906 0,0.48308 0.14127,0.87045 0.42383,1.16211 0.23697,0.2461 0.51041,0.36914 0.82031,0.36914 0.39648,0 0.70865,-0.16178 0.93652,-0.48535 0.20508,-0.28711 0.30762,-0.63574 0.30762,-1.0459 m 0.36914,4.18359 c 0,-0.5013 -0.139,-0.95247 -0.41699,-1.35351 -0.31446,-0.45117 -0.71094,-0.67676 -1.18946,-0.67676 -0.48763,0 -0.89095,0.22103 -1.20996,0.66308 -0.27799,0.38738 -0.41699,0.83855 -0.41699,1.35352 0,0.51953 0.13444,0.94792 0.40332,1.28516 0.29622,0.36914 0.69499,0.55371 1.19629,0.55371 0.5332,0 0.94336,-0.17546 1.23047,-0.52637 0.26888,-0.32357 0.40332,-0.75651 0.40332,-1.29883\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4365\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 205.34394,217.37025 -0.61523,0 0,-4.72363 c -1e-5,-0.65624 -0.33497,-0.98437 -1.00489,-0.98437 l -1.14843,0 0,5.708 -0.62891,0 0,-8.60644 0.62891,-0.007 0,2.32422 1.29199,0 c 0.97981,1e-5 1.46972,0.43523 1.46972,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4367\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 240.11152,217.37709 -0.62891,-0.007 0,-7.51953 -1.09375,1.39453 -0.75879,0 1.90723,-2.50195 0.57422,0 0,8.63379\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4369\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 245.81953,217.39076 -4.50489,0 0,-0.6084 3.54786,-5.19531 c 0.19595,-0.2871 0.29394,-0.59016 0.29394,-0.90918 0,-0.23241 -0.0547,-0.45572 -0.16406,-0.66992 l -0.16406,-0.25977 c -0.1185,-0.0957 -0.22104,-0.16405 -0.30762,-0.20507 -0.28256,-0.13671 -0.62207,-0.20507 -1.01856,-0.20508 -0.79297,1e-5 -1.32161,0.45573 -1.58593,1.36719 l -0.62207,0 c 0.29622,-1.31705 1.02994,-1.97558 2.20117,-1.97559 0.70182,1e-5 1.24869,0.16635 1.64062,0.49902 0.41471,0.35092 0.62207,0.86362 0.62207,1.53809 0,0.35092 -0.0775,0.66765 -0.23242,0.95019 l -3.43848,5.04493 3.73243,0 0,0.6289\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4371\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 250.26972,217.37025 -0.61523,0 0,-4.72363 c -1e-5,-0.65624 -0.33497,-0.98437 -1.00489,-0.98437 l -1.14843,0 0,5.708 -0.62891,0 0,-8.60644 0.62891,-0.007 0,2.32422 1.29199,0 c 0.97981,1e-5 1.46972,0.43523 1.46973,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4373\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 281.56464,217.37709 -0.6289,-0.007 0,-7.51953 -1.09375,1.39453 -0.75879,0 1.90723,-2.50195 0.57421,0 0,8.63379\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4375\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 287.02656,214.92299 c -1e-5,1.2806 -0.4489,2.07585 -1.34668,2.38574 -0.2142,0.0729 -0.43523,0.10938 -0.66309,0.10938 -0.49219,0 -0.92969,-0.14356 -1.3125,-0.43067 -0.50586,-0.37825 -0.75879,-0.94336 -0.75879,-1.69531 l 0,-2.0918 c 0,-0.55598 0.016,-0.95019 0.0479,-1.18261 0.17318,-1.2487 0.82487,-2.26041 1.95508,-3.03516 0.26432,-0.18228 0.54915,-0.27343 0.8545,-0.27344 l 0,0.64258 c -0.2461,0.041 -0.49447,0.15268 -0.74512,0.33496 -0.16407,0.1185 -0.39421,0.33725 -0.69043,0.65625 -0.53776,0.57423 -0.80664,1.33757 -0.80664,2.29004 l 1.00488,-0.007 c 0.76107,-0.005 1.35579,0.18458 1.78418,0.56739 0.45117,0.40104 0.67675,0.97754 0.67676,1.72949 m -0.61524,0.0205 c 0,-0.51497 -0.15723,-0.93197 -0.47168,-1.25098 -0.27344,-0.27799 -0.81348,-0.41699 -1.62011,-0.41699 l -0.75196,0 0,2.03711 c 0,0.44206 0.13216,0.79752 0.39649,1.0664 0.26432,0.26888 0.61751,0.40332 1.05957,0.40332 0.92512,0 1.38769,-0.61295 1.38769,-1.83886\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4377\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 291.61347,217.37025 -0.61523,0 0,-4.72363 c -1e-5,-0.65624 -0.33497,-0.98437 -1.00489,-0.98437 l -1.14843,0 0,5.708 -0.62891,0 0,-8.60644 0.62891,-0.007 0,2.32422 1.29199,0 c 0.97981,1e-5 1.46972,0.43523 1.46973,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4379\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 321.53437,217.39076 -4.50488,0 0,-0.6084 3.54785,-5.19531 c 0.19596,-0.2871 0.29394,-0.59016 0.29394,-0.90918 0,-0.23241 -0.0547,-0.45572 -0.16406,-0.66992 l -0.16406,-0.25977 c -0.11849,-0.0957 -0.22103,-0.16405 -0.30762,-0.20507 -0.28255,-0.13671 -0.62207,-0.20507 -1.01855,-0.20508 -0.79297,1e-5 -1.32162,0.45573 -1.58594,1.36719 l -0.62207,0 c 0.29622,-1.31705 1.02995,-1.97558 2.20117,-1.97559 0.70182,1e-5 1.2487,0.16635 1.64063,0.49902 0.41471,0.35092 0.62206,0.86362 0.62207,1.53809 -10e-6,0.35092 -0.0775,0.66765 -0.23242,0.95019 l -3.43848,5.04493 3.73242,0 0,0.6289\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4381\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 326.57246,213.06361 c -10e-6,1.00261 -0.1185,1.88673 -0.35547,2.65235 -0.35548,1.15299 -0.92514,1.72949 -1.70899,1.72949 -0.75651,0 -1.31478,-0.58105 -1.6748,-1.74316 -0.24154,-0.7793 -0.36231,-1.65886 -0.36231,-2.63868 0,-2.8802 0.68588,-4.3203 2.05762,-4.32031 1.36263,1e-5 2.04394,1.44011 2.04395,4.32031 m -0.61524,0 c 0,-0.81575 -0.0729,-1.5358 -0.21875,-2.16015 -0.23698,-1.02083 -0.6403,-1.53124 -1.20996,-1.53125 -0.56055,1e-5 -0.96843,0.51042 -1.22363,1.53125 -0.15951,0.63802 -0.23926,1.35808 -0.23926,2.16015 0,0.76108 0.082,1.48341 0.24609,2.167 0.2461,1.02995 0.64486,1.54492 1.19629,1.54492 0.55143,0 0.95475,-0.5127 1.20996,-1.53809 0.15951,-0.64257 0.23926,-1.36718 0.23926,-2.17383\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4383\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 331.15253,217.37025 -0.61523,0 0,-4.72363 c 0,-0.65624 -0.33496,-0.98437 -1.00488,-0.98437 l -1.14844,0 0,5.708 -0.62891,0 0,-8.60644 0.62891,-0.007 0,2.32422 1.29199,0 c 0.97982,1e-5 1.46972,0.43523 1.46973,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4385\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 357.60078,217.39076 -4.50489,0 0,-0.6084 3.54786,-5.19531 c 0.19595,-0.2871 0.29394,-0.59016 0.29394,-0.90918 0,-0.23241 -0.0547,-0.45572 -0.16406,-0.66992 l -0.16406,-0.25977 c -0.1185,-0.0957 -0.22104,-0.16405 -0.30762,-0.20507 -0.28256,-0.13671 -0.62207,-0.20507 -1.01856,-0.20508 -0.79297,1e-5 -1.32161,0.45573 -1.58593,1.36719 l -0.62207,0 c 0.29622,-1.31705 1.02994,-1.97558 2.20117,-1.97559 0.70182,1e-5 1.24869,0.16635 1.64062,0.49902 0.41471,0.35092 0.62207,0.86362 0.62207,1.53809 0,0.35092 -0.0775,0.66765 -0.23242,0.95019 l -3.43848,5.04493 3.73243,0 0,0.6289\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4387\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 362.97382,215.381 -1.31933,0 -0.007,1.98925 -0.63574,0 0,-1.98925 -2.55664,0 0,-0.56739 1.81836,-6.06347 0.6289,0 -1.81152,5.98144 1.9209,0 0,-1.85937 0.63574,0 0,1.85937 1.3125,0 0.0137,0.64942\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4389\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 367.1916,217.37025 -0.61524,0 0,-4.72363 c 0,-0.65624 -0.33496,-0.98437 -1.00488,-0.98437 l -1.14844,0 0,5.708 -0.6289,0 0,-8.60644 0.6289,-0.007 0,2.32422 1.29199,0 c 0.97982,1e-5 1.46973,0.43523 1.46973,1.30567 l 0.007,4.98339\"	\n";
	svgout << "	       style=\"font-size:14px\"	\n";
	svgout << "	       id=\"path4391\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:end;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:end;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	     x=\"69.500237\"	\n";
	svgout << "	     y=\"117.3799\"	\n";
	svgout << "	     id=\"editMaxDay\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3866\"	\n";
	svgout << "	       x=\"93.500237\"	\n";
	svgout << "	       y=\"117.3799\"	\n";
	svgout << "	       style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;text-anchor:start;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">"<<DayMAXhourcount<<"</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;display:inline;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"666.72394\"	\n";
	svgout << "	     y=\"22.712807\"	\n";
	svgout << "	     id=\"editMinMonth\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3974-5\"	\n";
	svgout << "	       x=\"666.72394\"	\n";
	svgout << "	       y=\"22.712807\"	\n";
	svgout << "	       style=\"font-size:10px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">"<<MINhourcount<<"</tspan></text>	\n";
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
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"texDays\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 409.5491,10.735519 -0.6289,-0.0068 0,-7.5195308 -1.09375,1.3945313 -0.75879,0 1.90722,-2.5019532 0.57422,0 0,8.6337887\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4240\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 428.77859,9.901535 c 0,0.250652 -0.11621,0.45573 -0.34863,0.615234 -0.20964,0.145834 -0.44434,0.21875 -0.7041,0.21875 l -2.89844,0 0,-8.6201168 2.6045,0 c 0.29166,8.6e-6 0.47851,0.020516 0.56054,0.061523 0.52409,0.1367271 0.78613,0.4853596 0.78613,1.0458984 l 0,6.6787109 m -0.61523,-0.2597656 0,-6.2138672 c 0,-0.4511641 -0.24382,-0.6767498 -0.73144,-0.6767578 l -1.98243,0 0,7.3828126 2.0166,0 c 0.46484,0 0.69727,-0.1640618 0.69727,-0.4921876\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4242\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 434.27469,10.715012 -0.36231,0 c -0.28255,0 -0.52409,-0.154948 -0.72461,-0.464844 -0.26888,0.309896 -0.6289,0.464844 -1.08007,0.464844 l -1.03223,0 c -0.7155,0 -1.07324,-0.389648 -1.07324,-1.1689457 l 0,-3.6708985 c 0,-0.96614 0.4694,-1.4492124 1.4082,-1.4492187 l 2.16016,0 -0.007,4.7236328 c 0,0.6380218 0.23698,0.9570321 0.71094,0.9570311 l 0,0.608399 m -1.32617,-1.4970707 0,-4.1972656 -1.56543,0 c -0.50586,5.7e-6 -0.75879,0.2734429 -0.75879,0.8203125 l 0,3.7392578 c 0,0.3554695 0.20963,0.533204 0.6289,0.533203 l 0.63575,0 c 0.70637,1e-6 1.05956,-0.2985016 1.05957,-0.8955077\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4244\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 438.6907,4.4259491 -2.30371,7.9638669 c -0.10937,0.378253 -0.35319,0.567381 -0.73144,0.567383 l -0.55371,0 0,-0.574219 0.31445,0 c 0.25521,-10e-7 0.43294,-0.180014 0.5332,-0.540039 l 0.58106,-2.0986325 -1.51758,-5.3183594 0.64258,0 1.22363,4.2246094 1.18262,-4.2246094 0.6289,0\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4246\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 442.61453,5.4650116 -0.6289,0 c -0.23243,-0.3098903 -0.5127,-0.464838 -0.84082,-0.4648438 -0.20053,5.8e-6 -0.37143,0.031907 -0.5127,0.095703 -0.0684,0.045579 -0.10938,0.070644 -0.12305,0.075195 -0.0319,0.022792 -0.0843,0.066086 -0.15722,0.1298828 -0.15039,0.1002657 -0.22559,0.3326874 -0.22559,0.6972656 0,0.3645877 0.16862,0.6858765 0.50586,0.9638672 l 1.03906,0.6357422 c 0.64258,0.3919298 0.96387,0.863609 0.96387,1.4150391 0,0.4466158 -0.13672,0.8385425 -0.41016,1.1757808 -0.31445,0.38737 -0.73144,0.581055 -1.25097,0.581055 -0.87045,0 -1.43555,-0.480794 -1.69532,-1.4423827 l 0.59473,0 c 0.21875,0.5787768 0.59245,0.8681647 1.1211,0.8681637 0.30077,10e-7 0.55142,-0.100259 0.75195,-0.3007809 0.20052,-0.2050771 0.30078,-0.4580065 0.30078,-0.7587891 0,-0.3600241 -0.21192,-0.6790342 -0.63574,-0.9570312 l -0.77246,-0.5058594 c -0.0866,-0.054684 -0.30306,-0.223304 -0.64942,-0.5058594 -0.30078,-0.3235638 -0.45117,-0.7132118 -0.45117,-1.1689453 0,-0.4785104 0.14811,-0.8636012 0.44434,-1.1552734 0.29622,-0.2962178 0.68587,-0.4443296 1.16894,-0.444336 0.75651,6.4e-6 1.24414,0.3554748 1.46289,1.0664063\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4248\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 451.08426,8.0695038 -3.91016,0 0,-0.5878906 3.91016,0 0,0.5878906\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4250\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 456.08817,8.0695038 -3.91016,0 0,-0.5878906 3.91016,0 0,0.5878906\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4252\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 461.09207,8.0695038 -3.91015,0 0,-0.5878906 3.91015,0 0,0.5878906\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4254\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 465.13211,8.3019257 -2.88477,1.1279296 0,-0.6152343 2.28321,-0.8681641 -2.28321,-1.0117187 0,-0.6083985 2.88477,1.2783203 0,0.6972657\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4256\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 520.64676,10.735519 -0.62891,-0.0068 0,-7.5195308 -1.09375,1.3945313 -0.75879,0 1.90723,-2.5019532 0.57422,0 0,8.6337887\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4258\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 525.78738,8.0626678 c 0,1.2259129 -0.47396,2.0439462 -1.42187,2.4541012 -0.32357,0.141277 -0.64942,0.211914 -0.97754,0.211914 l -1.42188,0 0,-0.608398 1.40137,-0.0068 c 0.57422,-0.0046 1.02539,-0.2096345 1.35352,-0.6152343 0.30989,-0.3873682 0.46484,-0.8658833 0.46484,-1.4355469 0,-0.4283823 -0.11166,-0.7952439 -0.33496,-1.1005859 -0.32813,-0.4420531 -0.8431,-0.6653601 -1.54492,-0.6699219 l -1.25098,-0.00684 0,-4.1699219 3.58887,0 0,0.6220703 -2.95996,0 0,2.9394532 0.86816,0 c 0.68359,5e-6 1.23047,0.230148 1.64063,0.6904296 0.39648,0.437504 0.59472,1.0026076 0.59472,1.6953125\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4260\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 652.00613,8.2267303 c 0,0.7337258 -0.2028,1.3284517 -0.60839,1.7841797 -0.42384,0.473959 -0.99805,0.710938 -1.72266,0.710938 l -1.35352,0 0,-0.601563 1.32618,-0.0068 c 0.5332,-0.0046 0.96386,-0.1914054 1.29199,-0.5605468 0.31445,-0.3554672 0.47167,-0.80436 0.47168,-1.3466797 -1e-5,-0.5468719 -0.13217,-0.993486 -0.39649,-1.3398437 -0.28711,-0.3828083 -0.69727,-0.5742143 -1.23047,-0.5742188 l -0.88183,0 0,-0.6289062 0.88867,0 c 0.50586,5e-6 0.90006,-0.2096302 1.18262,-0.6289063 0.0911,-0.1321556 0.15038,-0.2825461 0.17773,-0.4511718 0.0137,-0.082025 0.0205,-0.2711525 0.0205,-0.5673829 0,-0.3782481 -0.1709,-0.6949795 -0.5127,-0.9501953 -0.30534,-0.2278567 -0.65853,-0.3417888 -1.05957,-0.3417968 l -1.29199,0 0,-0.6083985 1.25781,0 c 0.95248,8.6e-6 1.61328,0.3600343 1.98243,1.0800781 0.15038,0.2916739 0.22558,0.5651112 0.22558,0.8203125 0,0.3919334 -0.0387,0.7132222 -0.11621,0.9638672 -0.11849,0.3828179 -0.36914,0.7063853 -0.75195,0.9707032 0.37369,0.1595098 0.6608,0.4807985 0.86133,0.9638671 0.1595,0.3873733 0.23925,0.8248728 0.23925,1.3125\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4262\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 655.28738,10.735519 -0.6289,-0.0068 0,-7.5195308 -1.09375,1.3945313 -0.75879,0 1.90723,-2.5019532 0.57421,0 0,8.6337887\"	\n";
	svgout << "	       style=\"font-size:14px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4264\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"tex00h\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 390.53516,19.979376 c -1e-5,1.145837 -0.13543,2.156253 -0.40625,3.03125 -0.40626,1.317709 -1.0573,1.976562 -1.95313,1.976562 -0.86458,0 -1.5026,-0.664062 -1.91406,-1.992187 -0.27604,-0.890622 -0.41406,-1.89583 -0.41406,-3.015625 0,-3.291659 0.78385,-4.93749 2.35156,-4.9375 1.55729,10e-6 2.33593,1.645841 2.33594,4.9375 m -0.70313,0 c 0,-0.932286 -0.0833,-1.755202 -0.25,-2.46875 -0.27084,-1.166658 -0.73177,-1.749991 -1.38281,-1.75 -0.64063,9e-6 -1.10677,0.583342 -1.39844,1.75 -0.18229,0.729173 -0.27344,1.552089 -0.27344,2.46875 0,0.869796 0.0937,1.695316 0.28125,2.476562 0.28125,1.177085 0.73698,1.765626 1.36719,1.765625 0.63021,1e-6 1.09114,-0.585936 1.38281,-1.757812 0.18229,-0.734372 0.27344,-1.562496 0.27344,-2.484375\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4343\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 396.44141,19.979376 c -1e-5,1.145837 -0.13543,2.156253 -0.40625,3.03125 -0.40626,1.317709 -1.0573,1.976562 -1.95313,1.976562 -0.86458,0 -1.5026,-0.664062 -1.91406,-1.992187 -0.27604,-0.890622 -0.41406,-1.89583 -0.41406,-3.015625 0,-3.291659 0.78385,-4.93749 2.35156,-4.9375 1.55729,10e-6 2.33593,1.645841 2.33594,4.9375 m -0.70313,0 c 0,-0.932286 -0.0833,-1.755202 -0.25,-2.46875 -0.27084,-1.166658 -0.73177,-1.749991 -1.38281,-1.75 -0.64063,9e-6 -1.10677,0.583342 -1.39844,1.75 -0.18229,0.729173 -0.27344,1.552089 -0.27344,2.46875 0,0.869796 0.0937,1.695316 0.28125,2.476562 0.28125,1.177085 0.73698,1.765626 1.36719,1.765625 0.63021,1e-6 1.09114,-0.585936 1.38281,-1.757812 0.18229,-0.734372 0.27344,-1.562496 0.27344,-2.484375\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4345\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 401.67578,24.901251 -0.70312,0 0,-5.398438 c -1e-5,-0.749994 -0.38282,-1.124993 -1.14844,-1.125 l -1.3125,0 0,6.523438 -0.71875,0 0,-9.835938 0.71875,-0.0078 0,2.65625 1.47656,0 c 1.11979,7e-6 1.67968,0.497402 1.67969,1.492187 l 0.008,5.695313\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4347\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"tex06h\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 390.53516,65.377907 c -1e-5,1.145837 -0.13543,2.156253 -0.40625,3.03125 -0.40626,1.317709 -1.0573,1.976562 -1.95313,1.976562 -0.86458,0 -1.5026,-0.664062 -1.91406,-1.992187 -0.27604,-0.890622 -0.41406,-1.89583 -0.41406,-3.015625 0,-3.291659 0.78385,-4.93749 2.35156,-4.9375 1.55729,10e-6 2.33593,1.645841 2.33594,4.9375 m -0.70313,0 c 0,-0.932286 -0.0833,-1.755202 -0.25,-2.46875 -0.27084,-1.166658 -0.73177,-1.749991 -1.38281,-1.75 -0.64063,9e-6 -1.10677,0.583342 -1.39844,1.75 -0.18229,0.729173 -0.27344,1.552089 -0.27344,2.46875 0,0.869796 0.0937,1.695316 0.28125,2.476562 0.28125,1.177085 0.73698,1.765626 1.36719,1.765625 0.63021,1e-6 1.09114,-0.585936 1.38281,-1.757812 0.18229,-0.734372 0.27344,-1.562496 0.27344,-2.484375\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4350\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 396.55859,67.502907 c 0,1.463543 -0.51302,2.372396 -1.53906,2.726562 -0.24479,0.08333 -0.4974,0.125 -0.75781,0.125 -0.5625,0 -1.0625,-0.164062 -1.5,-0.492187 -0.57813,-0.432291 -0.86719,-1.078124 -0.86719,-1.9375 l 0,-2.390625 c 0,-0.635411 0.0182,-1.085932 0.0547,-1.351563 0.19791,-1.427075 0.94271,-2.583324 2.23437,-3.46875 0.30208,-0.208323 0.6276,-0.31249 0.97657,-0.3125 l 0,0.734375 c -0.28126,0.04688 -0.56511,0.174488 -0.85157,0.382813 -0.1875,0.135425 -0.45052,0.385425 -0.78906,0.75 -0.61458,0.656257 -0.92188,1.528652 -0.92187,2.617187 l 1.14843,-0.0078 c 0.86979,-0.0052 1.54948,0.210943 2.03907,0.648437 0.51562,0.458338 0.77343,1.117191 0.77343,1.976563 m -0.70312,0.02344 c -1e-5,-0.588538 -0.17969,-1.0651 -0.53906,-1.429687 -0.31251,-0.317704 -0.92969,-0.476558 -1.85157,-0.476563 l -0.85937,0 0,2.328125 c 0,0.50521 0.15104,0.91146 0.45312,1.21875 0.30208,0.307293 0.70573,0.460938 1.21094,0.460938 1.05729,0 1.58593,-0.70052 1.58594,-2.101563\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4352\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 401.80078,70.299782 -0.70312,0 0,-5.398438 c -1e-5,-0.749994 -0.38282,-1.124993 -1.14844,-1.125 l -1.3125,0 0,6.523438 -0.71875,0 0,-9.835938 0.71875,-0.0078 0,2.65625 1.47656,0 c 1.11979,7e-6 1.67968,0.497402 1.67969,1.492187 l 0.008,5.695313\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4354\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"tex12h\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 388.53516,115.70612 -0.71875,-0.008 0,-8.59375 -1.25,1.59375 -0.86719,0 2.17969,-2.85937 0.65625,0 0,9.86719\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4336\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 395.05859,115.72174 -5.14843,0 0,-0.69531 4.05468,-5.9375 c 0.22396,-0.32812 0.33594,-0.67447 0.33594,-1.03906 0,-0.26562 -0.0625,-0.52083 -0.1875,-0.76563 l -0.1875,-0.29687 c -0.13542,-0.10937 -0.25261,-0.1875 -0.35156,-0.23438 -0.32292,-0.15624 -0.71094,-0.23437 -1.16406,-0.23437 -0.90626,0 -1.51042,0.52084 -1.8125,1.5625 l -0.71094,0 c 0.33854,-1.5052 1.17708,-2.25781 2.51562,-2.25782 0.80208,1e-5 1.42708,0.19012 1.875,0.57032 0.47396,0.40105 0.71094,0.98698 0.71094,1.75781 0,0.40105 -0.0885,0.76303 -0.26562,1.08594 l -3.92969,5.76562 4.26562,0 0,0.71875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4338\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 400.14453,115.6983 -0.70312,0 0,-5.39843 c -1e-5,-0.75 -0.38282,-1.125 -1.14844,-1.125 l -1.3125,0 0,6.52343 -0.71875,0 0,-9.83593 0.71875,-0.008 0,2.65625 1.47656,0 c 1.11979,1e-5 1.67968,0.49741 1.67969,1.49219 l 0.008,5.69531\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4340\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"tex18h\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 388.53516,161.10464 -0.71875,-0.008 0,-8.59375 -1.25,1.59375 -0.86719,0 2.17969,-2.85937 0.65625,0 0,9.86718\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4329\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 395.00391,158.84683 c -1e-5,1.16146 -0.52605,1.89584 -1.57813,2.20313 -0.30209,0.0885 -0.60417,0.13281 -0.90625,0.13281 -1.52083,0 -2.34115,-0.77604 -2.46094,-2.32813 l -0.0313,-0.40625 c -0.005,-0.0885 -0.008,-0.17447 -0.008,-0.25781 0,-1.06249 0.48698,-1.89062 1.46094,-2.48437 -0.67709,-0.53646 -1.01563,-1.22656 -1.01563,-2.07032 0,-0.66145 0.17969,-1.21874 0.53907,-1.67187 0.38541,-0.49478 0.90104,-0.74218 1.54687,-0.74219 0.65625,10e-6 1.17708,0.26303 1.5625,0.78906 0.33333,0.45314 0.5,0.9948 0.5,1.625 0,0.81772 -0.34375,1.50782 -1.03125,2.07032 0.94791,0.54688 1.42187,1.59375 1.42188,3.14062 m -1.04688,-5.21875 c 0,-0.48957 -0.11198,-0.88801 -0.33594,-1.19531 -0.25,-0.34374 -0.61198,-0.51562 -1.08593,-0.51563 -0.46355,1e-5 -0.82292,0.17449 -1.07813,0.52344 -0.22917,0.31251 -0.34375,0.70834 -0.34375,1.1875 0,0.55209 0.16146,0.9948 0.48438,1.32813 0.27083,0.28125 0.58333,0.42188 0.9375,0.42187 0.45312,10e-6 0.80989,-0.18489 1.07031,-0.55469 0.23437,-0.32811 0.35156,-0.72655 0.35156,-1.19531 m 0.42188,4.78125 c -1e-5,-0.57291 -0.15886,-1.08854 -0.47657,-1.54687 -0.35938,-0.51562 -0.8125,-0.77344 -1.35937,-0.77344 -0.5573,0 -1.01823,0.25261 -1.38281,0.75781 -0.31771,0.44271 -0.47657,0.95834 -0.47657,1.54688 0,0.59375 0.15365,1.08333 0.46094,1.46875 0.33854,0.42187 0.79427,0.63281 1.36719,0.63281 0.60937,0 1.07812,-0.20052 1.40625,-0.60156 0.30729,-0.36979 0.46093,-0.86458 0.46094,-1.48438\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4331\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 400.30078,161.09683 -0.70312,0 0,-5.39844 c -1e-5,-0.74999 -0.38282,-1.12499 -1.14844,-1.125 l -1.3125,0 0,6.52344 -0.71875,0 0,-9.83594 0.71875,-0.008 0,2.65625 1.47656,0 c 1.11979,10e-6 1.67968,0.4974 1.67969,1.49219 l 0.008,5.69531\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4333\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#000000;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     id=\"tex23h\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 390.93359,206.5188 -5.14843,0 0,-0.69531 4.05468,-5.9375 c 0.22396,-0.32812 0.33594,-0.67448 0.33594,-1.03907 0,-0.26561 -0.0625,-0.52082 -0.1875,-0.76562 l -0.1875,-0.29688 c -0.13542,-0.10936 -0.25261,-0.18749 -0.35156,-0.23437 -0.32292,-0.15624 -0.71094,-0.23437 -1.16406,-0.23438 -0.90626,10e-6 -1.51042,0.52085 -1.8125,1.5625 l -0.71094,0 c 0.33854,-1.5052 1.17708,-2.2578 2.51562,-2.25781 0.80208,1e-5 1.42708,0.19012 1.875,0.57031 0.47396,0.40105 0.71094,0.98699 0.71094,1.75782 0,0.40105 -0.0885,0.76302 -0.26562,1.08593 l -3.92969,5.76563 4.26562,0 0,0.71875\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4322\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 396.19141,203.63599 c -1e-5,0.83854 -0.23178,1.51823 -0.69532,2.03906 -0.48437,0.54167 -1.14062,0.8125 -1.96875,0.8125 l -1.54687,0 0,-0.6875 1.51562,-0.008 c 0.60938,-0.005 1.10156,-0.21875 1.47657,-0.64063 0.35937,-0.40625 0.53905,-0.91927 0.53906,-1.53906 -1e-5,-0.625 -0.15105,-1.13541 -0.45313,-1.53125 -0.32812,-0.4375 -0.79687,-0.65625 -1.40625,-0.65625 l -1.00781,0 0,-0.71875 1.01563,0 c 0.57812,0 1.02864,-0.23958 1.35156,-0.71875 0.10416,-0.15104 0.17187,-0.32291 0.20312,-0.51563 0.0156,-0.0937 0.0234,-0.30988 0.0234,-0.64843 0,-0.43229 -0.19531,-0.79427 -0.58594,-1.08594 -0.34896,-0.26041 -0.7526,-0.39062 -1.21093,-0.39063 l -1.47657,0 0,-0.69531 1.4375,0 c 1.08854,1e-5 1.84375,0.41147 2.26563,1.23438 0.17187,0.33334 0.25781,0.64584 0.25781,0.9375 0,0.44792 -0.0443,0.81511 -0.13281,1.10156 -0.13542,0.4375 -0.42188,0.8073 -0.85938,1.10937 0.42708,0.1823 0.75521,0.54949 0.98438,1.10157 0.18229,0.44271 0.27343,0.94271 0.27344,1.5\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4324\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 401.26953,206.49536 -0.70312,0 0,-5.39844 c -1e-5,-0.74999 -0.38282,-1.12499 -1.14844,-1.125 l -1.3125,0 0,6.52344 -0.71875,0 0,-9.83594 0.71875,-0.008 0,2.65625 1.47656,0 c 1.11979,1e-5 1.67968,0.4974 1.67969,1.49219 l 0.008,5.69531\"	\n";
	svgout << "	       style=\"font-size:16px;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	       id=\"path4326\" />	\n";
	svgout << "	  </g>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#7800e9;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"58.049789\"	\n";
	svgout << "	     y=\"11.545778\"	\n";
	svgout << "	     id=\"editObserker\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3986\"	\n";
	svgout << "	       x=\"58.049789\"	\n";
	svgout << "	       y=\"11.545778\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[0] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"58.531723\"	\n";
	svgout << "	     y=\"26.376514\"	\n";
	svgout << "	     id=\"editCountry\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3990\"	\n";
	svgout << "	       x=\"58.531723\"	\n";
	svgout << "	       y=\"26.376514\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[1] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"58.531723\"	\n";
	svgout << "	     y=\"41.207249\"	\n";
	svgout << "	     id=\"editCity\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3994\"	\n";
	svgout << "	       x=\"58.531723\"	\n";
	svgout << "	       y=\"41.207249\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[2] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"58.087875\"	\n";
	svgout << "	     y=\"56.037983\"	\n";
	svgout << "	     id=\"editAntenna\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan3998\"	\n";
	svgout << "	       x=\"58.087875\"	\n";
	svgout << "	       y=\"56.037983\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[3] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"58.527328\"	\n";
	svgout << "	     y=\"70.868721\"	\n";
	svgout << "	     id=\"editPreamp\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4002\"	\n";
	svgout << "	       x=\"58.527328\"	\n";
	svgout << "	       y=\"70.868721\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[4] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"59.015121\"	\n";
	svgout << "	     y=\"85.699455\"	\n";
	svgout << "	     id=\"editReciever\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4006\"	\n";
	svgout << "	       x=\"59.015121\"	\n";
	svgout << "	       y=\"85.699455\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[5] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"59.015121\"	\n";
	svgout << "	     y=\"100.53019\"	\n";
	svgout << "	     id=\"editComputer\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4010\"	\n";
	svgout << "	       x=\"59.015121\"	\n";
	svgout << "	       y=\"100.53019\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[6] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"267.68707\"	\n";
	svgout << "	     y=\"11.545778\"	\n";
	svgout << "	     id=\"editLat\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4014\"	\n";
	svgout << "	       x=\"267.68707\"	\n";
	svgout << "	       y=\"11.545778\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << DecDegToDDMMSS(svginfo[8]) << svginfo[9] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"267.68707\"	\n";
	svgout << "	     y=\"27.212563\"	\n";
	svgout << "	     id=\"editLon\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4018\"	\n";
	svgout << "	       x=\"267.68707\"	\n";
	svgout << "	       y=\"27.212563\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << DecDegToDDMMSS(svginfo[7]) << svginfo[10]<< "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"267.69147\"	\n";
	svgout << "	     y=\"42.879349\"	\n";
	svgout << "	     id=\"editFrequency\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4022\"	\n";
	svgout << "	       x=\"267.69147\"	\n";
	svgout << "	       y=\"42.879349\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[11] << "</tspan></text>	\n";
	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;line-height:125%;letter-spacing:0px;word-spacing:0px;fill:#9000d3;fill-opacity:1;stroke:none;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"	\n";
	svgout << "	     x=\"267.94196\"	\n";
	svgout << "	     y=\"58.546131\"	\n";
	svgout << "	     id=\"editEmail\"	\n";
	svgout << "	     linespacing=\"125%\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       role=\"line\"	\n";
	svgout << "	       id=\"tspan4026\"	\n";
	svgout << "	       x=\"267.94196\"	\n";
	svgout << "	       y=\"58.546131\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\">" << svginfo[12] << "</tspan></text>	\n";

	//svgout << "	  <rect	";
	//svgout << "	     style=\"opacity:0.42049470000000000;fill:#ff0000;fill-opacity:1;stroke:none;stroke-opacity:1\"	";
	//svgout << "	     id=\"rect3868\"	";
	//svgout << "	     width=\"5.9932489\"	";
	//svgout << "	     height=\"5.9932513\"	";
	//svgout << "	     x=\" "<< x << "\"	";
	//svgout << "	     y=\"" << y << "\" />	";

		for (int i = 0; i < 31; ++i)
		{
			for (int j = 0; j < 24; ++j)
			{

				svgout << "	  <rect	\n";
				if(i == utc->tm_mday-1 && j == utc->tm_hour)
				{
					svgout << "	     style=\"opacity:1;fill:" << SvgColAll(MAXhourcount, MINhourcount, hourcount[(i*24)+j]) << ";stroke:#e6e6e6ff;stroke-opacity:1;stroke-width:1.5;\"	\n";
				}else{
					svgout << "	     style=\"opacity:1;fill:" << SvgColAll(MAXhourcount, MINhourcount, hourcount[(i*24)+j]) << ";stroke:" << SvgColAll(MAXhourcount, MINhourcount, hourcount[(i*24)+j]) << ";stroke-opacity:1;stroke-width:0.5;\"	\n";
				}
				svgout << "	     id=\"rect3868\"	\n";
				svgout << "	     width=\"5.9932489\"	\n";
				svgout << "	     height=\"5.9932513\"	\n";
				svgout << "	     x=\" "<< x+(7.898 * i) << "\"	\n";
				svgout << "	     y=\"" << y+(7.897 * j) << "\" />	\n";
				//std::cout<< "SvgGen: "<< i*24 + j << " >ma hodnotu> "<<hourcount[i*24+j]<<std::endl;

			}
		}

	svgout << "	  <rect	\n";
	svgout << "	     y=\"16.22628\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-9\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(0) << "," << SvgColGreen(0) << "," << SvgColBlue(0) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"24.224943\"	\n";
	svgout << "	     x=\"657.7077\"\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-5\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(1) << "," << SvgColGreen(1) << "," << SvgColBlue(1) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"32.223595\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-0\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(2) << "," << SvgColGreen(2) << "," << SvgColBlue(2) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"200.19554\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-6\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(23) << "," << SvgColGreen(23) << "," << SvgColBlue(23) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"192.19688\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-92\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(22) << "," << SvgColGreen(22) << "," << SvgColBlue(22) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"184.19821\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-44\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(21) << "," << SvgColGreen(21) << "," << SvgColBlue(21) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"168.20088\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-2\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(19) << "," << SvgColGreen(19) << "," << SvgColBlue(19) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"176.19955\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-8\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(20) << "," << SvgColGreen(20) << "," << SvgColBlue(20) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"120.2089\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-25\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(14) << "," << SvgColGreen(14) << "," << SvgColBlue(14) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"128.20757\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-99\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(15) << "," << SvgColGreen(15) << "," << SvgColBlue(15) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"136.20622\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-50\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(16) << "," << SvgColGreen(16) << "," << SvgColBlue(16) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"144.2049\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-1\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(17) << "," << SvgColGreen(17) << "," << SvgColBlue(17) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"152.20355\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-21\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(18) << "," << SvgColGreen(18) << "," << SvgColBlue(18) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"160.20222\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-87\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(19) << "," << SvgColGreen(19) << "," << SvgColBlue(19) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"112.21024\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-49\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(13) << "," << SvgColGreen(13) << "," << SvgColBlue(13) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"104.21157\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-3\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(12) << "," << SvgColGreen(12) << "," << SvgColBlue(12) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"96.212906\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-68\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(11) << "," << SvgColGreen(11) << "," << SvgColBlue(11) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"48.220921\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-7\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(5) << "," << SvgColGreen(5) << "," << SvgColBlue(5) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"56.219597\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-15\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(6) << "," << SvgColGreen(6) << "," << SvgColBlue(6) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"64.218254\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-18\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(7) << "," << SvgColGreen(7) << "," << SvgColBlue(7) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"80.215591\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-41\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(9) << "," << SvgColGreen(9) << "," << SvgColBlue(9) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"88.214249\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-51\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(10) << "," << SvgColGreen(10) << "," << SvgColBlue(10) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"40.22226\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-63\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(4) << "," << SvgColGreen(4) << "," << SvgColBlue(4) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <rect	\n";
	svgout << "	     y=\"72.216919\"	\n";
	svgout << "	     x=\"657.7077\"	\n";
	svgout << "	     height=\"5.9932513\"	\n";
	svgout << "	     width=\"5.9932489\"	\n";
	svgout << "	     id=\"rect3868-156\"	\n";
	svgout << "	     style=\"opacity:1;fill:rgb("<< SvgColRed(8) << "," << SvgColGreen(8) << "," << SvgColBlue(8) <<");fill-opacity:1;stroke:none\" />	\n";
	svgout << "	  <g	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:end;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:end;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	     id=\"texUpdated\">	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 10.075855,169.25497 0,7.84375 c -6e-6,0.64584 -0.2187553,1.15365 -0.6562502,1.52344 -0.4114626,0.34896 -0.9453162,0.52344 -1.6015625,0.52344 -0.6093774,0 -1.1276061,-0.16406 -1.5546875,-0.49219 -0.5104177,-0.39583 -0.7656257,-0.91927 -0.765625,-1.57031 l 0.00781,-7.82813 0.6875,0 0,7.8125 c -1.4e-6,0.45313 0.2005192,0.8073 0.6015625,1.0625 0.3229143,0.20834 0.6692681,0.31251 1.0390625,0.3125 0.3749966,1e-5 0.7057254,-0.10156 0.9921875,-0.30468 0.3541623,-0.25 0.5312454,-0.60156 0.53125,-1.05469 l 0,-7.82813 0.7187507,0\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4397\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 15.521167,177.79404 c -0.01563,0.13541 -0.03646,0.25521 -0.0625,0.35937 -0.130213,0.48438 -0.419275,0.78125 -0.867187,0.89063 -0.192712,0.0469 -0.463545,0.0703 -0.8125,0.0703 l -1.65625,-0.008 0,2.60937 -0.6875,0 0,-9.82031 2.929687,0 c 0.286455,1e-5 0.544267,0.11199 0.773438,0.33594 0.255203,0.25521 0.382807,0.58854 0.382812,1 l 0,4.5625 m -0.71875,-0.10157 0,-4.48437 c -0.07292,-0.42708 -0.309899,-0.64062 -0.710937,-0.64063 l -1.945313,0.008 0,5.875 1.921875,0 c 0.48958,0 0.734371,-0.25261 0.734375,-0.75782\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4399\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 21.036792,179.09091 -2.625,0 c -0.432293,0 -0.781251,-0.11458 -1.046875,-0.34375 -0.265626,-0.23437 -0.398438,-0.5651 -0.398437,-0.99219 l 0,-4.53125 c -1e-6,-0.10416 0.01562,-0.22134 0.04687,-0.35156 0.109374,-0.45832 0.390624,-0.7526 0.84375,-0.88281 0.171873,-0.0469 0.416664,-0.0703 0.734375,-0.0703 l 1.75,0.008 0,-2.67969 0.695312,0 0,9.84375 m -0.710937,-0.69531 0,-5.8125 -1.929688,0 c -0.489585,1e-5 -0.734376,0.25001 -0.734375,0.75 l 0,4.44531 c 0.06771,0.41146 0.325519,0.61719 0.773438,0.61719 l 1.890625,0\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4401\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 27.40398,179.0831 -0.414063,0 c -0.322921,0 -0.598963,-0.17708 -0.828125,-0.53125 -0.307295,0.35417 -0.718753,0.53125 -1.234375,0.53125 l -1.179687,0 c -0.81771,0 -1.226563,-0.44531 -1.226563,-1.33594 l 0,-4.19531 c 0,-1.10416 0.536457,-1.65624 1.609375,-1.65625 l 2.46875,0 -0.0078,5.39844 c -5e-6,0.72916 0.270828,1.09375 0.8125,1.09375 l 0,0.69531 m -1.515625,-1.71094 0,-4.79687 -1.789063,0 c -0.578126,0 -0.867189,0.3125 -0.867187,0.9375 l 0,4.27343 c -2e-6,0.40626 0.239581,0.60938 0.71875,0.60938 l 0.726562,0 c 0.807288,0 1.210934,-0.34115 1.210938,-1.02344\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4403\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 31.630542,172.59872 -1.320312,0 0,6.50782 -0.71875,0 0,-6.50782 -1.273438,0 0,-0.6875 1.273438,0 0,-2.65625 0.71875,0 0,2.65625 1.320312,0 0,0.6875\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4405\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 36.989917,175.72372 -3.414062,0 0,1.59375 c -2e-6,0.72917 0.367185,1.09376 1.101562,1.09375 l 2.203125,0 0,0.6875 -2.507812,0 c -0.593752,0 -1.020835,-0.23177 -1.28125,-0.69531 -0.166668,-0.29687 -0.250001,-0.64062 -0.25,-1.03125 l 0,-3.45312 c -10e-7,-0.58854 0.203124,-1.07812 0.609375,-1.46875 0.406248,-0.39583 0.906248,-0.59375 1.5,-0.59375 0.572913,0 1.057288,0.19011 1.453125,0.57031 0.395828,0.37501 0.593745,0.84896 0.59375,1.42187 l -0.0078,1.875 m -0.710937,-1.72656 c -4e-6,-0.41145 -0.117192,-0.74999 -0.351563,-1.01562 -0.234378,-0.27083 -0.55469,-0.40625 -0.960937,-0.40625 -0.343753,0 -0.640627,0.0964 -0.890625,0.28906 -0.333335,0.25521 -0.500002,0.63021 -0.5,1.125 l 0,1.05469 2.703125,0 0,-1.04688\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4407\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 42.536792,179.09091 -2.625,0 c -0.432293,0 -0.781251,-0.11458 -1.046875,-0.34375 -0.265626,-0.23437 -0.398438,-0.5651 -0.398437,-0.99219 l 0,-4.53125 c -10e-7,-0.10416 0.01562,-0.22134 0.04687,-0.35156 0.109374,-0.45832 0.390624,-0.7526 0.84375,-0.88281 0.171873,-0.0469 0.416664,-0.0703 0.734375,-0.0703 l 1.75,0.008 0,-2.67969 0.695312,0 0,9.84375 m -0.710937,-0.69531 0,-5.8125 -1.929688,0 c -0.489585,1e-5 -0.734376,0.25001 -0.734375,0.75 l 0,4.44531 c 0.06771,0.41146 0.325519,0.61719 0.773438,0.61719 l 1.890625,0\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4409\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	    <path	\n";
	svgout << "	       d=\"m 44.521167,174.7081 -0.710937,0 0,-0.71094 0.71875,0 -0.0078,0.71094 m 0,3.77344 -0.710937,0 0,-0.70313 0.71875,0 -0.0078,0.70313\"	\n";
	svgout << "	       style=\"font-size:16px;text-align:start;text-anchor:start;fill:#000000;fill-opacity:1\"	\n";
	svgout << "	       id=\"path4411\"	\n";
	svgout << "	       inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	  </g>	\n";


	//  zakladna hisntogramu  -- 34,86588

	float Dkrok = 0.00001; // Kolik px zabere v sloupci 1 meteor
	std::cout << DayMAXhourcount <<"|" ;
	if (DayMAXhourcount != 0)
	{
		Dkrok = (float)84/(float)DayMAXhourcount;
	}
	if (Dkrok < 0)
	{
		Dkrok = 0;
	}


	for (int i = 0; i < 744; ++i)
	{
		//if (hourcount[i] > 999 || hourcount[i] < 0)
		if (hourcount[i]==1111)
		{
			hourcount[i]=0;
		}
	}

	std::cout << DayMAXhourcount <<"|B "<< Dkrok<< "|C " << hourcount[(utc->tm_mday-1)*24 + 4] <<"|D " << 202.866002 - (Dkrok*hourcount[(utc->tm_mday-1)*24 + 4]) << "|E "<< Dkrok*hourcount[(utc->tm_mday-1)*24 + 4] << "|"<< hourcount[(utc->tm_mday-1)*24 + 4] << std::endl;



	svgout << "	  <text	\n";
	svgout << "	     xml:space=\"preserve\"	\n";
	svgout << "	     style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;text-align:start;line-height:125%;letter-spacing:0px;word-spacing:0px;text-anchor:start;fill:#000000;fill-opacity:1;stroke:none;font-family:Solid Edge ISO;-inkscape-font-specification:Solid Edge ISO\"	\n";
	svgout << "	     x=\"48.419983\"	\n";
	svgout << "	     y=\"179.09091\"	\n";
	svgout << "	     id=\"editUpdated\"	\n";
	svgout << "	     sodipodi:linespacing=\"125%\"><tspan	\n";
	svgout << "	       sodipodi:role=\"line\"	\n";
	svgout << "	       id=\"tspan3302\"	\n";
	svgout << "	       x=\"48.419983\"	\n";
	svgout << "	       y=\"179.09091\"	\n";
	svgout << "	       style=\"font-size:12px;font-style:normal;font-variant:normal;font-weight:normal;font-stretch:normal;fill:#9000d3;fill-opacity:1;font-family:Ubuntu;-inkscape-font-specification:Ubuntu\"> " << utc->tm_hour << ":" << utc->tm_min << ":" <<  utc->tm_sec << " UT </tspan></text>	\n";
	
	for (int i = 0; i < 24; ++i)
	{

	svgout << "	  <rect	\n";
	svgout << "	     width=\"8\"	\n";
	svgout << "	     height=\"" << Dkrok*hourcount[(utc->tm_mday-1)*24 + i] << "\"	\n";
	svgout << "	     x=\"" << 115.10423 + (i * 10.00151) << "\"		\n";
	svgout << "	     y=\"" << 202.866002 - (Dkrok*hourcount[(utc->tm_mday-1)*24 + i]) << "\"	\n";
	svgout << "	     id=\"recDay" << i <<"\"	\n";
	svgout << "	     style=\"fill:#f7444f;fill-opacity:1;stroke:none\" />	\n";
		
	}

	svgout << "	  <path	\n";
	svgout << "	     style=\"fill:none;stroke:#000000;stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;stroke-miterlimit:4;stroke-opacity:1;stroke-dasharray:3, 3;stroke-dashoffset:0;fill-opacity:1\"	\n";
	svgout << "	     d=\"m 98.758356,118.9899 266.554634,0\"	\n";
	svgout << "	     id=\"path4651\"	\n";
	svgout << "	     inkscape:connector-curvature=\"0\" />	\n";
	svgout << "	</svg>	\n";


	svgout.close();
}



int SvgPng(std::string path){
	Magick::Image svgImage(path + "rmob.svg");
	svgImage.magick("png");
	svgImage.write(path + "rmob.png");
}

int SvgJpg(std::string path, std::string svginfo[15]){

	time_t rawtime;
	struct tm * utc;

	time ( &rawtime );
	utc = gmtime ( &rawtime );

	Magick::Image svgImage( "./io/rmob.svg");
	svgImage.magick("jpg");
	std::stringstream JpgName;

	JpgName << svginfo[0] << "_";
	if (utc->tm_mon+1 < 10)
	{
		JpgName << "0" << utc->tm_mon+1;
	}else{
		JpgName << utc->tm_mon+1 ;
	}
	JpgName << utc->tm_year+1900 << ".jpg";

	std::string string;
	string = JpgName.str();
	svgImage.write(path + string);
}


void TxtGen(std::string svginfo[15], int hourcount[745],std::string path){


std::string strhourcount[745];
std::stringstream c;


unsigned int i=0; 

for (i; i < 745 ; ++i)
{	
	c.str("");
	if (hourcount[i] < 10)
	{
		c.str("");
		c << "   " << hourcount[i];
	}
	else if (hourcount[i] > 9 && hourcount[i] < 100)
	{
		c.str("");
		c << "  " << hourcount[i];
	}
	else if (hourcount[i] > 99 && hourcount[i] < 1000)
	{
		c.str("");
		c << " " << hourcount[i];
	}
	else if (hourcount[i]==1111)
	{
		c.str("");
		c << "??? ";
	}
	
	strhourcount[i] = c.str();
}



const char* const MonthNames[] = { "jan", "feb", "mar", "apr", "may", "Jun", "Jul", "aug", "sep", "oct", "nov", "dec"};


	time_t now = time(0);
	tm *ltm = localtime(&now);

	time_t rawtime;
	struct tm * utc;
	
	time ( &rawtime );
	utc = gmtime ( &rawtime );

	std::ofstream txtout;

	

// ZVPPCB_012014rmob.TXT

	std::stringstream JpgName;

	JpgName << path << svginfo[0] << "_";
	if (utc->tm_mon+1 < 10)
	{
		JpgName << "0" << utc->tm_mon+1;
	}else{
		JpgName << utc->tm_mon+1 ;
	}
	JpgName << utc->tm_year+1900 << "rmob.TXT";



	txtout.open (JpgName.str().c_str() );

	txtout << MonthNames[ utc->tm_mon ] << "| 00h| 01h| 02h| 03h| 04h| 05h| 06h| 07h| 08h| 09h| 10h| 11h| 12h| 13h| 14h| 15h| 16h| 17h| 18h| 19h| 20h| 21h| 22h| 23h|\n";
	for (int i = 0; i < 31; ++i)
	{
		txtout <<  i <<" |"<< strhourcount[24* i-0 +0] <<"|"<< strhourcount[24* i-0 +1] <<"|"<< strhourcount[24* i-0 +2] <<"|"<< strhourcount[24* i-0 +3] <<"|"<< strhourcount[24* i-0 +4] <<"|"<< strhourcount[24* i-0 +5] <<"|"<< strhourcount[24* i-0 +6] <<"|"<< strhourcount[24* i-0 +7] <<"|"<< strhourcount[24* i-0 +8] <<"|"<< strhourcount[24* i-0 +9] <<"|"<< strhourcount[24* i-0 + 10] <<"|"<< strhourcount[24* i-0 + 11] <<"|"<< strhourcount[24* i-0 + 12] <<"|"<< strhourcount[24* i-0 + 13] <<"|"<< strhourcount[24* i-0 + 14] <<"|"<< strhourcount[24* i-0 + 15] <<"|"<< strhourcount[24* i-0 + 16] <<"|"<< strhourcount[24* i-0 + 17] <<"|"<< strhourcount[24* i-0 + 18] <<"|"<< strhourcount[24* i-0 + 19] <<"|"<< strhourcount[24* i-0 + 20] <<"|"<< strhourcount[24* i-0 + 21] <<"|"<< strhourcount[24* i-0 + 22] <<"|"<< strhourcount[24* i-0 + 23] <<"|\n";
		//std::cout <<  i <<" |0 "<< hourcount[24* i-0 +0] <<"|1 "<< hourcount[24* i-0 +1] <<"|2 "<< hourcount[24* i-0 +2] <<"|3 "<< hourcount[24* i-0 +3] <<"|4 "<< hourcount[24* i-0 +4] <<"|5 "<< hourcount[24* i-0 +5] <<"|6 "<< hourcount[24* i-0 +6] <<"|7 "<< hourcount[24* i-0 +7] <<"|8 "<< hourcount[24* i-0 +8] <<"|9 "<< hourcount[24* i-0 +9] <<"|10 "<< hourcount[24* i-0 + 10] <<"|11 "<< hourcount[24* i-0 + 11] <<"|12 "<< hourcount[24* i-0 + 12] <<"|13 "<< hourcount[24* i-0 + 13] <<"|14 "<< hourcount[24* i-0 + 14] <<"|15 "<< hourcount[24* i-0 + 15] <<"|16 "<< hourcount[24* i-0 + 16] <<"|17 "<< hourcount[24* i-0 + 17] <<"|18 "<< hourcount[24* i-0 + 18] <<"|19 "<< hourcount[24* i-0 + 19] <<"|20 "<< hourcount[24* i-0 + 20] <<"|21 "<< hourcount[24* i-0 + 21] <<"|22 "<< hourcount[24* i-0 + 22] <<"|23 "<< hourcount[24* i-0 + 23] <<"|"<<std::endl;
	}


	txtout << "[Observer]" <<  svginfo[0] << "\n";
	txtout << "[Country]" <<  svginfo[1] << "\n";
	txtout << "[City]" <<  svginfo[2] << "\n";
	txtout << "[Longitude]" <<  svginfo[8].substr(0,3) <<"d"<< std::setw(2)<< std::setfill('0') << round((atoi(svginfo[8].substr(4,4).c_str())/10000 *60)) << std::setw(2)<< std::setfill('0') << round((atoi(svginfo[8].substr(4,4).c_str())/10000 *60)-round((atoi(svginfo[8].substr(4,4).c_str())/10000 *60))*100)  <<" "<< svginfo[9] << "\n";
	txtout << "[Latitude ]" <<  svginfo[7].substr(0,3) <<"d"<< std::setw(2)<< std::setfill('0') << round((atoi(svginfo[7].substr(4,4).c_str())/10000 *60)) << std::setw(2)<< std::setfill('0') << round((atoi(svginfo[7].substr(4,4).c_str())/10000 *60)-round((atoi(svginfo[7].substr(4,4).c_str())/10000 *60))*100)<<" "<< svginfo[10] << "\n";
	txtout << "[Longitude GMAP]" << svginfo[8] << "\n";
	txtout << "[Latitude GMAP]" << svginfo[7] << "\n";
	txtout << "[Frequencies]" <<  svginfo[11] << "\n";
	txtout << "[Antenna]" <<  svginfo[3] << "\n";
	txtout << "[Azimut Antenna]" <<  "-" << "\n";
	txtout << "[Elevation Antenna]" <<  "-" << "\n";
	txtout << "[Pre-Amplifier]" <<  svginfo[4] << "\n";
	txtout << "[Receiver]" <<  svginfo[5] << "\n";
	txtout << "[Observing Method]" <<  "Fordward scattering" << "\n";
	txtout << "[Remarks]" <<  svginfo[6] << "\n";
	txtout << "[Soft FTP] Astrozor RMOBgen v1.3.dev\n";
	txtout << "[E]" <<  "-" << "\n";

	txtout.close();
}
