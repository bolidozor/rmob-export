#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import datetime
import ftplib

import paramiko
import rmob

if __name__ == "__main__":
	#gui.main()
	os.chdir(r"./out/")
	rmob = rmob.rmob()
	rmob.setSftp('space.astro.cz', 'roman')
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
					print("po txt gen")
					rmob.getRmobPlot()
					print("po plot")
					rmob.rmobupload()
					print("done :::::::::::::::::::")
				except Exception as e:
					print(">>", e)
		except Exception as e:
			print(">", e)



	#sftpURL   =  'space.astro.cz'
	#sftpUser  =  'ZVPP'

	#ssh = paramiko.SSHClient()
	# automatically add keys without requiring human intervention
	#ssh.set_missing_host_key_policy( paramiko.AutoAddPolicy() )

	#ssh.connect(sftpURL, username=sftpUser)

	#ftp = ssh.open_sftp()
	#files = ftp.listdir("/storage/bolidozor/ZVPP/ZVPP-R2")
	#print files
#print ftp.get()
