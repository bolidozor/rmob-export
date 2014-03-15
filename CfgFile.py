#!/usr/bin/python
import os
import datetime
import array 
import ConfigParser

config = ConfigParser.RawConfigParser()

config.add_section('RmobConfig')
config.set('RmobConfig', 'StationName', 'ZVPP')
config.set('RmobConfig', 'Country', 'Czech republic')
config.set('RmobConfig', 'City', 'Ceske Budejovice')
config.set('RmobConfig', 'LatitudeNS', 'N')
config.set('RmobConfig', 'LatitudeDeg', 'E')
config.set('RmobConfig', 'LongtitudeEW', 'ZVPP')
config.set('RmobConfig', 'LongtitudeDeg', 'ZVPP')
config.set('RmobConfig', 'Email', 'roman-dvorak@email.cz')
config.set('RmobConfig', 'Computer', 'Ion PC')
config.set('RmobConfig', 'Antenna', '1/4GP')
config.set('RmobConfig', 'Preamp', 'LNA01A (www.mlab.cz)')
config.set('RmobConfig', 'Reciver', 'RMDS01B')
config.set('RmobConfig', 'Frequency', '140 050 000 Hz')

with open('rmob.cfg', 'wb') as configfile:
    config.write(configfile)