rmob-export
===========

Generator of colorgramme graphs to rmob observers database. This program generate rmob (http://www.rmob.org/livedata/main.php) compitible graphs from radio meteor detection sofware data. 

rmob-export is not a primary stand-alone station-based application. Instead of this is primarilly intended as a service for observers, to process the station's data uploaded by [data-uploader](https://github.com/MLAB-project/data-uploader) to the central Bolidozor network data server.

### Ubuntu 13.04

    sudo apt-get install g++ libmagick++ libmagick++5 libmagick++-dev libmysqlclient-dev
 

## Howto

### Compiling

1. cd to project in rmob-export/ directory

2. make

### Setting

1. go to rmob-export/ directory

2. run configure.py
    
    python Configure.py


### Running

1. go to project directory - rmob-export

2. python Run.py


## Multigen

Multigen can be automatically launched from system cron with:

  */10 * * * * cd /home/<data>/rmob-export/; python3 multigen.py


## FAQ

after run Run.py
    
    what():  Magick: unable to open image `./io/gen/ZVPP_022014.jpg':  @ error/blob.c/OpenBlob/2587
    
type

    mkdir ./io/gen/
    

## License

Everything in this repository is GNU GPL v3 licensed.
