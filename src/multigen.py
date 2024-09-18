#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import datetime, time
import ftplib

import paramiko
import rmob

period = 10 # in minutes

if __name__ == "__main__":
	rmob = rmob.rmob()

	while True:
		start = datetime.datetime.now()
		try:
			for observatory in rmob.getObservatorys():
				rmob.setGenPreferences(observatory)
				rmob.setActual(True)
				#rmob.setGenPreferences("ZVPP")
				try:
					for station in rmob.getStations():
						try:
							print("Selected station:", station)
							rmob.setGenPreferences_stanice(str(station))
							rmob.parseConfigData()
							rmob.parseMonthData()
							rmob.getRmobTxt()
							rmob.getRmobPlot()
							rmob.rmobupload()
							print("done :::::::::::::::::::")
						except Exception as e:
							print(">>", e)
				except Exception as e:
					print(">", e)
		except Exception as e:
			print(e)
		end = datetime.datetime.now()
		print("Time elapsed: ", end - start)

		time.sleep(period * 60 - (end - start).seconds)

		

