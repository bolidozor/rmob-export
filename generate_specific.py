#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import ftplib

import paramiko
import rmob


serveraddress  = 'space.astro.cz'		# server adress
serverusername = 'ZVPP'					# server username for ssh acces
genObservatory = 'ZVPP'					# name of observatory
genStation     =  None					# name of station, set None for all stations in observatory
genYear        =  None					# generation of year, set None for actual year
genMonth       =  None					# generation of month, set None for actual month
GenDay         =  None					# generation of day, set None for actual day


if __name__ == "__main__":
	#gui.main()

	rmob = rmob.rmob()
	rmob.setSftp('space.astro.cz', 'ZVPP')
	rmob.setGenPreferences(self, ObservatoryName = genObservatory, GenYear = genYear, GenMonth = genMonth, GenDay = GenDay):
	rmob.parseConfigData()
	rmob.parseMonthData()
	rmob.getRmobTxt()
	rmob.getRmobPlot()