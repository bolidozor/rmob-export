#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import ftplib
import paramiko
import numpy
import numpy as np
import ConfigParser

class rmob():
	def __init__(self):
		print "Rmob"
		now = datetime.datetime.now()
		self.genYear  = now.year
		self.genMonth = now.month
		self.genObservatory = None
		self.cenStation = None
		self.LastData = False
		self.ftp = None
		self.configFiles = []
		self.monthData = np.zeros((24, 31), dtype=numpy.int)
		self.stationName = None
		self.stationCountry = None
		self.stationCity = None
		self.stationLatL = None
		self.stationLat =None
		self.stationLonL = None
		self.stationLon = None
		self.stationEmail = None
		self.stationComputer = None
		self.stationAntenna = None
		self.stationPreAmp = None
		self.stationReciver = None
		self.stationFreq = None


	def setGenPreferences(self, ObservatoryName = None, GenYear = None, GenMonth = None):
		if ObservatoryName:
			self.genObservatory = ObservatoryName
			self.LastData = False
		if GenYear:
			self.genYear = GenYear
			self.LastData = False
		if GenMonth:
			self.genMonth = GenMonth
			self.LastData = False

	def setGenPreferences_stanice(self, stanice):
		self.genStation = "stanice"
		self.genStation = stanice

	def setSftp(self, ftp):
		self.ftp = ftp

	def setSftp(self, sftpURL, sftpUser):
		self.ssh = paramiko.SSHClient()
		self.ssh.set_missing_host_key_policy( paramiko.AutoAddPolicy() )
		self.ssh.connect(sftpURL, username=sftpUser)
		self.ftp = self.ssh.open_sftp()
		print "Pripojeni sftp na:", sftpUser+"@"+sftpURL, "bylo uspesne"
	
	#def getStations(self):


	def getStations(self):
		stations = self.ftp.listdir("/storage/bolidozor/"+self.genObservatory)
		for station in sorted(stations):
			if not "." in station:
				stations = self.ftp.listdir("/storage/bolidozor/"+self.genObservatory+"/"+station)
				if "rmob.cfg" in stations:
					self.configFiles.append(station)
		return self.configFiles

	def parseConfigData(self):
		file = self.ftp.file("/storage/bolidozor/" + self.genObservatory + "/" + self.genStation + "/rmob.cfg")
		Config = ConfigParser.ConfigParser()
		Config.readfp(file)
		#print Config.get("RmobConfig","stationname")
		
		self.stationName = Config.get("RmobConfig", "stationname")
		self.stationCountry = Config.get("RmobConfig", "country")
		self.stationCity = Config.get("RmobConfig", "city")
		self.stationLatL = Config.get("RmobConfig", "latitudens")
		self.stationLat = Config.get("RmobConfig", "latitudedeg")
		self.stationLonL = Config.get("RmobConfig", "longtitudeew")
		self.stationLon = Config.get("RmobConfig", "longtitudedeg")
		self.stationEmail = Config.get("RmobConfig", "email")
		self.stationComputer = Config.get("RmobConfig", "computer")
		self.stationAntenna = Config.get("RmobConfig", "antenna")
		self.stationPreAmp = Config.get("RmobConfig", "preamp")
		self.stationReciver = Config.get("RmobConfig", "reciver")
		self.stationFreq = Config.get("RmobConfig", "frequency")


	def parseMonthData(self, ObservatoryName = None, StationName = None, Year = None, Month = None):
		monthPath = "/storage/bolidozor/" + self.genObservatory + "/" + self.genStation + "/data/" + str(self.genYear) + "/" + str(self.genMonth).zfill(2)
		days = sorted(self.ftp.listdir(monthPath))
		print days
		for day in days:
			print int(day), "z", len(days)
			hours = sorted(self.ftp.listdir(monthPath+"/"+day))
			print hours
			for hour in hours:
				if hour.find("meta"):
					file = self.ftp.file(monthPath+"/"+day+"/"+hour)
					for i in file:
						if i.find("met"):
							#print int(hour[8:10]), int(day), i
							self.monthData[int(hour[8:10])][int(day)-1] += 1
					print int(hour[8:10]), day, self.monthData[int(hour[8:10])][int(day)-1]
		print self.monthData

		self.LastData = True

	
	def getRmobTxt(self):
		print "získávání rmox TXT souboru"
		monthDict = {1:'jan', 2:'feb', 3:'mar', 4:'apr', 5:'may', 6:'jun', 
            7:'jul', 8:'aug', 9:'sep', 10:'oct', 11:'nov', 12:'dec'}

		#f = open(+self.StationName+"_"+self.genMonth+self.genYear+"rmob.TXT", 'w')
		f = open("rmob.TXT", 'w')
		f.write(str(monthDict[self.genMonth]) + "| 00h| 01h| 02h| 03h| 04h| 05h| 06h| 07h| 08h| 09h| 10h| 11h| 12h| 13h| 14h| 15h| 16h| 17h| 18h| 19h| 20h| 21h| 22h| 23h|\n\r")
		for day in range(31):
			name=" "+str(day+1).zfill(2)+"|"
			for hour in range(24):
				print "hour", hour, day
				name += str(self.monthData[hour][day]).zfill(3)+" |"
			name += "\n\r"
			f.write(name)

		def decdeg2dms(dd):
			mnt,sec = divmod(dd*3600,60)
			deg,mnt = divmod(mnt,60)
			return deg,mnt,sec


		f.write("[Observer]"+self.stationName+"\n\r")
		f.write("[Country]"+self.stationCountry+"\n\r")
		f.write("[City]"+self.stationCity+"\n\r")
		deg, mnt, sec = decdeg2dms(float(self.stationLon)+"\n\r")
		f.write("[Longitude]"+str(deg)+"d"+str(mnt)+str(sec)+self.stationLonL+"\n\r")
		deg, mnt, sec = decdeg2dms(float(self.stationLat)+"\n\r")
		f.write("[Latitude]"+str(deg)+"d"+str(mnt)+str(sec)+self.stationLatL+"\n\r")
		f.write("[Longitude GMAP]"+self.stationLon+"\n\r")
		f.write("[Latitude GMAP]"+self.stationLat+"\n\r")
		f.write("[Frequencies]"+self.stationFreq+"\n\r")
		f.write("[Antenna]"+self.stationAntenna+"\n\r")
		f.write("[Azimut Antenna] 0"+"\n\r")
		f.write("[Elevation Antenna] 0"+"\n\r")
		f.write("[Pre-Amplifier]"+self.stationPreAmp+"\n\r")
		f.write("[Receiver]"+self.stationReciver+"\n\r")
		f.write("[Observing Method]"+"Fordward scattering"+"\n\r")
		f.write("[Remarks]"+self.stationComputer+"\n\r")
		f.write("[Soft FTP] Astrozor pyRMOBgen v1.8 - Bolidozor MultiGen (RadioObserver) - https://github.com/bolidozor/rmob-export"+"\n\r")
		f.write("[E]-"+"\n\r")
		f.close()
	def getRmobPlot(self):
		pass