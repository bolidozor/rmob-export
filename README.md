rmob-export
===========

Generator of colorgramme graphs to rmob observers database. This program generate rmob (http://www.rmob.org/livedata/main.php) compitible graphs from radio meteor detection sofware data. 

### Ubuntu 13.04

    sudo apt-get install libmagick++5 libmagick++-dev libmysqlclient-dev
 

## Howto

### Compiling

1. cd to project in rmob-export/ directory

2. make

### Setting

1. Open file rmob-export/io/Observatory.info

2. In Observatory.info file change all parameters


### Running

1. go to project directory - rmob-export

2. python Run.py

## FAQ
after run Run.py
  what():  Magick: unable to open image `./io/gen/ZVPP_022014.jpg':  @ error/blob.c/OpenBlob/2587


## License

Everything in this repository is GNU GPL v3 licensed.
