#------------------------------------------------------------------------------

SOURCE=RmobGen.cpp
MYPROGRAM=RmobGen
ARG_magick=`Magick++-config --cppflags --cxxflags --ldflags --libs`
ARG_curl= -lcurl
CC=g++ -g -ggdb3

#------------------------------------------------------------------------------

$(MYPROGRAM): $(SOURCE) Makefile

	$(CC)  $(SOURCE)  -o $(MYPROGRAM) $(ARG_magick) $(ARG_curl)
