#------------------------------------------------------------------------------

SOURCE=RmobGen.cpp
MYPROGRAM=RmobGen
ARG_magick=`Magick++-config --cppflags --cxxflags --ldflags --libs`
ARG_mysql=-lmysqlclient
CC=g++

#------------------------------------------------------------------------------

$(MYPROGRAM): $(SOURCE)

	$(CC) $(SOURCE) -o $(MYPROGRAM)  $(ARG_magick) $(ARG_mysql)
