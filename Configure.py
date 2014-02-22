#!/usr/bin/python
import os
import datetime

ObsInfo = {}
i=0
read = open('./io/Observatory.info', 'r')
for line in iter(read):
	if line[:1] != "#":
		i += 1
		ObsInfo[i]= line
		#print i, " - ", ObsInfo[i]
read.close()

print "####################################################################################################\nrmob-export configurator\n####################################################################################################"

print "\n\n============================================================\n\tObservatory name: "
print "Old value: ",ObsInfo[1]
var = raw_input("Enter new value [string] or press enter to use old value:")
if var != "":
	ObsInfo[1] = var+"\n"

print "\n\n============================================================\n\tObservatory Prefix:\n\t\t Prefix is used in names of files"
print "Old value: ",ObsInfo[16]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[16] = var+"\n"

print "\n\n============================================================\n\tCountry: "
print "Old value: ",ObsInfo[2]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[2] = var+"\n"

print "\n\n============================================================\n\tCity: "
print "Old value: ",ObsInfo[3]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[3] = var+"\n"

print "\n\n============================================================\n\tAntenna: "
print "Old value: ",ObsInfo[4]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[4] = var+"\n"

print "\n\n============================================================\n\tPreamp: "
print "Old value: ",ObsInfo[5]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[5] = var+"\n"

print "\n\n============================================================\n\tReciver: "
print "Old value: ",ObsInfo[6]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[6] = var+"\n"

print "\n\n============================================================\n\tComputer: "
print "Old value: ",ObsInfo[7]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[7] = var+"\n"

print "\n\n============================================================\n\tLongtitude E/W: "
print "Old value: ",ObsInfo[10]
var = raw_input("Enter new value ['E';'W'] or press enter to use old value: ")
if var != "":
	ObsInfo[10] = var+"\n"

print "\n\n============================================================\n\tLongtitude ddd.dddddd: "
print "Old value: ",ObsInfo[8]
var = raw_input("Enter new value [ddd.dddddd] or press enter to use old value: ")
if var != "":
	ObsInfo[8] = var+"\n"

print "\n\n============================================================\n\tLatitude N/S: "
print "Old value: ",ObsInfo[11]
var = raw_input("Enter new value ['N';'S'] or press enter to use old value: ")
if var != "":
	ObsInfo[11] = var+"\n"

print "\n\n============================================================\n\tLatitude ddd.dddddd: "
print "Old value: ",ObsInfo[9]
var = raw_input("Enter new value [ddd.dddddd] or press enter to use old value: ")
if var != "":
	ObsInfo[9] = var+"\n"

print "\n\n============================================================\n\tFrequency: "
print "Old value: ",ObsInfo[12]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[12] = var+"\n"

print "\n\n============================================================\n\tEmail: "
print "Old value: ",ObsInfo[13]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[13] = var+"\n"

print "\n\n============================================================\n\tPath to source files:\n\t\t e.g.:  /home/roman/ion/home/roman/MetData/ZVPP/Sort/data/"
print "Old value: ",ObsInfo[14]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[14] = var+"\n"

print "\n\n============================================================\n\tData type\n\t\t e.g.: \"Bolidozor_14\", \"Bolidozor\", \"Rmob\", \"MySQL\""
print "Old value: ",ObsInfo[15]
var = raw_input("Enter new value [string] or press enter to use old value: ")
if var != "":
	ObsInfo[15] = var+"\n"

print "\n\n============================================================\n End of Configure.py"


write = open('./io/Observatory.info', 'w')
write.write("#################################################################################################### \n")
write.write("##\n")
write.write("##   THIS FILE IS GENERATED AUTOMATICLY BY Configure.py\n")
write.write("## \n")
write.write("##   !!! DO NOT CHANGE this file\n")
write.write("## \n")
write.write("##   for edit this file type 'python Configure.py in 'rmob-export/' dictionary'\n")
write.write("## \n")
write.write("#################################################################################################### \n")
write.write("#################################################################################################### \n")
write.write("# Observatory name\n")
write.write(ObsInfo[1])
write.write("# Country\n")
write.write(ObsInfo[2])
write.write("# City\n")
write.write(ObsInfo[3])
write.write("# Antenna\n")
write.write(ObsInfo[4])
write.write("# Pramp\n")
write.write(ObsInfo[5])
write.write("# Reciever\n")
write.write(ObsInfo[6])
write.write("# Computer\n")
write.write(ObsInfo[7])
write.write("# Latitude xxx.xxxxxx\n")
write.write(ObsInfo[8])
write.write("# Longtitude yyy.yyyyyy\n")
write.write(ObsInfo[9])
write.write("# Latitude direction E\W\n")
write.write(ObsInfo[10])
write.write("# Longtitude direction S\N\n")
write.write(ObsInfo[11])
write.write("# Frequency\n")
write.write(ObsInfo[12])
write.write("# email\n")
write.write(ObsInfo[13])
write.write("# path to source file\n")
write.write(ObsInfo[14])
write.write("# input data eg. \"Bolidozor_14\", \"Bolidozor\", \"Rmob\", \"MySQL\"\n")
write.write(ObsInfo[15])
write.write("# Observatory Prefix \n")
write.write(ObsInfo[16])
write.write("#################################################################################################### \n")
write.write("## \n")
write.write("##   END\n")

write.close()