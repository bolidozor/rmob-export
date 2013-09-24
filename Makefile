#------------------------------------------------------------------------------

SOURCE=RmobGen.cpp
MYPROGRAM=RmobGen
ARG_magick=`Magick++-config --cppflags --cxxflags --ldflags --libs`
CC=g++

#------------------------------------------------------------------------------

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o $(MYPROGRAM)  $(ARG_magick)
