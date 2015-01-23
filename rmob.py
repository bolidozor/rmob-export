#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import ftplib
import paramiko

class rmob():
	def __init__(self):
		print "Rmob"
		now = datetime.datetime.now()
		self.GenYear  = now.year
		self.GenMonth = now.month
		self.GenStation = None
		self.LastData = False
		self.ftp = None
		self.configFile = None

	def setGenPreferences(self, StationName = None, GenYear = None, GenMonth = None):
		if StationName:
			self.GenStation = StationName
			self.LastData = False
		if GenYear:
			self.GenYear = GenYear
			self.LastData = False
		if GenMonth:
			self.GenMonth = GenMonth
			self.LastData = False

	def setSftp(self, ftp):
		self.ftp = ftp

	def setSftp(self, sftpURL, sftpUser):
		self.ssh = paramiko.SSHClient()
		self.ssh.set_missing_host_key_policy( paramiko.AutoAddPolicy() )
		self.ssh.connect(sftpURL, username=sftpUser)
		self.ftp = self.ssh.open_sftp()
		print "Pripojeni sftp na:", sftpUser+"@"+sftpURL, "bylo uspesne"

	def getStationConfig(self):

		observatorys = self.ftp.listdir("/storage/bolidozor/"+self.GenStation)
		for observatory in sorted(observatorys):
			print "   "+observatory
			if not "." in observatory:
				stations = self.ftp.listdir("/storage/bolidozor/"+self.GenStation+"/"+observatory)
				if "rmob.cfg" in stations:
					print "Rmob config file founded"
					self.configFile = "/"+self.GenStation+"/"+observatory




	def parseMonthData(self):
		files = self.ftp.listdir("/storage/bolidozor/ZVPP/ZVPP-R2")
		print files
		self.LastData = True
	
	def getRmobTxt(self):
		pass

	def getRmobPlot(self):
		pass