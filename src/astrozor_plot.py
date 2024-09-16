#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import ftplib
import numpy as np
import matplotlib 
import matplotlib.pyplot as plt

import paramiko
import rmob


serveraddress  = 'space.astro.cz'		# server adress
serverusername = 'indexer'				# server username for ssh acces
genObservatory = 'ZVPP'					# name of observatory
genStation     = 'ZVPP'				# name of station, set None for all stations in observatory
genYear        =  None					# generation of year, set None for actual year
genMonth       =  None					# generation of month, set None for actual month
GenDay         =  None					# generation of day, set None for actual day


if __name__ == "__main__":
	#gui.main()
	os.chdir(r"./out/")
	rmob = rmob.rmob()
	rmob.setSftp('space.astro.cz', 'indexer')
	#for month in range(1):
	rmob.setGenPreferences(ObservatoryName = genObservatory, StationName = "ZVPP-R2", GenYear = genYear, GenMonth = genMonth, GenDay = GenDay)
	rmob.parseConfigData()
	rmob.parseMonthData()
	data = rmob.getMonthData()
	arr1d = np.swapaxes(data,0,1).flatten()
	print data
	print arr1d
	plt.plot(arr1d)
	plt.savefig('foo.png')
	try:
		#plt.show()
		pass
	except Exception, e:
		raise e