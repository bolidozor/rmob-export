#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import datetime
import ftplib
import numpy
import numpy as np
import ConfigParser
import sys


if __name__ == "__main__":
	#gui.main()

	print "otevírání souboru" + sys.argv[0] + "."

	year = 2015
	month = 4


	#manthData = np.load("ZVPP_ZVPP-R2_dataMask_"+str(year) + "_" +str(month)+".npy")
			#np.save("ZVPP_ZVPP-R2_dataMask_"+str(year) + "_" +str(month)+".npy", monthDataMask)
	try:
		monthDataMask = np.load("./out/cache/ZVPP_ZVPP-R2_dataMask_"+str(year) + "_" +str(month)+".npy")
	except Exception, e:
		monthDataMask = np.full((24,32), True, bool)
		print e
	monthDataMask=monthDataMask.astype(bool)
	monthDataMask=numpy.resize(monthDataMask,(24,32))





	print "a .......................... Nová maska"
	print "r .......................... Odstranit masku"
	print "w .......................... Ukázat masky"
	print "s .......................... Ulozit a ukončit"
	print "c .......................... Ukončit"


	run = True
	while run:
		var = raw_input("\n\nHodnota: ")
		if var == 'a':
			day = raw_input("den: ")
			hou = raw_input("hodina: ")
			monthDataMask[int(hou)-1,int(day)-1] = False
		elif var == 'r':
			day = raw_input("den: ")
			hou = raw_input("hodina: ")
			monthDataMask[int(hou)-1,int(day)-1] = True
		elif var == 'w':
			for x in xrange(0,24):
				for y in xrange(0,31):
					print monthDataMask[x,y],
				print ""
		elif var == 's':
			np.save("./out/cache/ZVPP_ZVPP-R2_dataMask_"+str(year) + "_" +str(month)+".npy", monthDataMask)

			run = False
		elif var == 'c':
			run = False
		else:
			print "není definováno"
