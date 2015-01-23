#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import ftplib

import paramiko
import rmob


if __name__ == "__main__":
	#gui.main()

	rmob = rmob.rmob()
	rmob.setSftp('space.astro.cz', 'ZVPP')
	rmob.setGenPreferences("ZVPP")
	rmob.parseMonthData()
	rmob.getStationConfig()






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
