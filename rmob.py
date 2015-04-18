#!/usr/bin/python
# -*- coding: utf-8 -*-


import os
import datetime
import time
import time
import ftplib
import paramiko
import numpy
import numpy as np
import numpy.ma as ma
import ConfigParser
import svgwrite
import ftplib
import cairosvg

class rmob():
	def __init__(self):
		print "Rmob"
		now = datetime.datetime.now()
		self.genYear  = now.year
		self.genMonth = now.month
		self.genDay = now.day
		self.genObservatory = None
		self.genStation = None
		self.LastData = False
		self.ftp = None
		self.configFiles = []
		self.monthData = np.zeros((24, 32), dtype=numpy.int)
		self.monthDataSize = np.zeros((24, 32))
		self.stationName = None
		self.stationCountry = None
		self.stationCity = None
		self.stationLatL = None
		self.stationLat = None
		self.stationLonL = None
		self.stationLon = None
		self.stationEmail = None
		self.stationComputer = None
		self.stationAntenna = None
		self.stationPreAmp = None
		self.stationReciver = None
		self.stationFreq = None
		self.genActual = False
		self.UsePlotMask = True

	def info(self):
		print "#####################################################"
		print "#####################################################"
		print "rok:", self.genYear
		print "mesic:", self.genMonth
		print "den:", self.genDay
		print "observator:", self.genObservatory
		print "stanice:", self.genStation
		print "data:", self.LastData
		print "ftp:", self.ftp
		print "cfg", self.configFiles
		print "monthData: ", self.monthData
		print "monthDataSize:", self.monthDataSize
		print "StationName:", self.stationName
		print "#####################################################"
		print "#####################################################"

	def setActual(self, actual = True):
		self.genActual = actual

	def setGenPreferences(self, ObservatoryName = None, StationName = None, GenYear = None, GenMonth = None, GenDay = None):
		if ObservatoryName:
			self.genObservatory = ObservatoryName
			self.LastData = False
		if StationName:
			self.genStation = StationName
			self.LastData = False
		if GenYear:
			self.genYear = GenYear
			self.LastData = False
		if GenMonth:
			self.genMonth = GenMonth
			self.LastData = False
		if GenDay:
			self.genDay = GenDay
			self.LastData = False

	def setGenPreferences_stanice(self, stanice):
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
	def getObservatorys(self):
		observatorys = sorted(self.ftp.listdir("/storage/bolidozor/"))
		return observatorys

	def getStations(self):
		stations = self.ftp.listdir("/storage/bolidozor/"+self.genObservatory)
		for station in sorted(stations):
			if not "." in station:
				stations = self.ftp.listdir("/storage/bolidozor/"+self.genObservatory+"/"+station)
				if "rmob.cfg" in stations:
					self.configFiles.append(station)
		return self.configFiles

	def parseConfigData(self):
		print "/storage/bolidozor/" , str(self.genObservatory), "/", str(self.genStation), "/rmob.cfg"
		file = self.ftp.file("/storage/bolidozor/" + str(self.genObservatory) + "/" + str(self.genStation) + "/rmob.cfg")
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
		try:
#			data = np.load('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+"_"+ str(self.genYear) + str(self.genMonth) +".npz")
#			self.monthData=data['monthData']
#			self.monthDataSize=data['monthDataSize']
			data = np.load('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+".npz")
			self.monthData=data["monthData_"+str(self.genYear) + "_" +str(self.genMonth)]
			self.monthDataSize=data["monthDataSize_"+str(self.genYear) + "_" +str(self.genMonth)]
			print self.monthData
#			print self.monthDataSize
		except Exception, e:
			print "je nastaveno na -1"
			self.monthData.fill(-1)
			self.monthDataSize.fill(-1)
			print e

		days = sorted(self.ftp.listdir(monthPath))
		print days
		for day in days:
			print int(day), "z", len(days)
			hours=[]
			for hour in sorted(self.ftp.listdir(monthPath+"/"+day)):
				if hour.find("meta") != -1:
					hours.append(hour)
#			print hours
			for hour in hours:
				if self.ftp.stat(monthPath+"/"+day+"/"+hour).st_size != self.monthDataSize[int(hour[8:10])][int(day)-1]:
					file = self.ftp.file(monthPath+"/"+day+"/"+hour)
					self.monthData[int(hour[8:10])][int(day)-1] = 0
					for i in file:
						if i.find("met") != -1:
							self.monthData[int(hour[8:10])][int(day)-1] += 1
					#self.monthData[int(hour[8:10])][int(day)-1] += 1
					self.monthDataSize[int(hour[8:10])][int(day)-1] = self.ftp.stat(monthPath+"/"+day+"/"+hour).st_size
					print "Hodina", hour[8:10], "byla pozměněna, MpH:",  self.monthData[int(hour[8:10])][int(day)-1], "dne:", int(day)
				else:
					print "Hodina", hour[8:10]," má lakální zálohu, MpH:", self.monthData[int(hour[8:10])][int(day)-1], "dne:", int(day)

				#np.savez('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+"_"+ str(self.genYear) + str(self.genMonth) +".npz", monthData=self.monthData, monthDataSize=self.monthDataSize)
                np.savez('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+".npz", **{"monthData_"+str(self.genYear) + "_" +str(self.genMonth): self.monthData, "monthDataSize_"+str(self.genYear) + "_" +str(self.genMonth): self.monthDataSize})
		self.LastData = True

	def getMonthData(self):
		return self.monthData

	
	def getRmobTxt(self):
		print "získávání rmox TXT souboru"
		monthDict = {1:'jan', 2:'feb', 3:'mar', 4:'apr', 5:'may', 6:'jun', 
            7:'jul', 8:'aug', 9:'sep', 10:'oct', 11:'nov', 12:'dec'}

		f = open(str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+"rmob.TXT", 'w')
		f.write(str(monthDict[self.genMonth]) + "| 00h| 01h| 02h| 03h| 04h| 05h| 06h| 07h| 08h| 09h| 10h| 11h| 12h| 13h| 14h| 15h| 16h| 17h| 18h| 19h| 20h| 21h| 22h| 23h|\n")
		for day in range(31):
			name=" "+str(day+1).zfill(2)+"|"
			for hour in range(24):
#				print "hour", hour, day
				if self.monthData[hour][day] == -1:
					name += "???"+" |"
				else:	
					name += str(self.monthData[hour][day]).zfill(3)+" |"
			name += "\n"
			f.write(name)

		def decdeg2dms(dd):
			mnt,sec = divmod(dd*3600,60)
			deg,mnt = divmod(mnt,60)
			return deg,mnt,sec

		f.write("[Observer]"+self.stationName+"\n")
		f.write("[Country]"+self.stationCountry+"\n")
		f.write("[City]"+self.stationCity+"\n")
		deg, mnt, sec = decdeg2dms(float(self.stationLon))
		f.write("[Longitude]"+str(int(deg)).zfill(3)+"d"+str(int(mnt))+str(int(sec))+" "+self.stationLonL+"\n")
		deg, mnt, sec = decdeg2dms(float(self.stationLat))
		f.write("[Latitude]"+str(int(deg)).zfill(3)+"d"+str(int(mnt))+str(int(sec))+" "+self.stationLatL+"\n")
		f.write("[Longitude GMAP]"+self.stationLon+"\n")
		f.write("[Latitude GMAP]"+self.stationLat+"\n")
		f.write("[Frequencies]"+self.stationFreq+"\n")
		f.write("[Antenna]"+self.stationAntenna+"\n")
		f.write("[Azimut Antenna] 0"+"\n")
		f.write("[Elevation Antenna] 0"+"\n")
		f.write("[Pre-Amplifier]"+self.stationPreAmp+"\n")
		f.write("[Receiver]"+self.stationReciver+"\n")
		f.write("[Observing Method]"+"Fordward scattering"+"\n")
		f.write("[Remarks]"+self.stationComputer+"\n")
		f.write("[Soft FTP]Astrozor pyRMOBgen v1.9 - astrozor.cz, bolidozor.cz MultiGen (RadioObserver) - https://github.com/bolidozor/rmob-export"+"\n")
		f.write("[E]"+self.stationEmail+"\n")
		f.close()

	def getRmobPlot(self):
		def decdeg2dms(dd):
			mnt, sec = divmod(dd*3600,60)
			deg, mnt = divmod(mnt, 60)
			return str(str(int(deg))+"d "+str(int(mnt))+'\" '+str(int(sec))+"\' ")

		try:
			monthDataMask = np.load("./cache/"+str(self.genObservatory)+"_"+str(self.genStation)+"_dataMask_"+str(self.genYear) + "_" +str(self.genMonth)+".npy")
		except Exception, e:
			monthDataMask = np.full((23,30), True, bool)

		monthDataMasked = ma.masked_array(self.monthData, np.invert(monthDataMask))
		

		monthMax=np.amax(monthDataMasked)
#		monthMax=int(np.median(monthDataMasked)+np.std(monthDataMasked)*5)
		monthMin= np.min(monthDataMasked[np.nonzero(monthDataMasked)])+1

		print monthDataMask
		print monthDataMasked
		
		dwg = svgwrite.Drawing(str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+".svg", size=(700,220))
		dwg.add(dwg.rect(insert=(120, 110), size=(245, 95), stroke = "black", fill = "white"))
		dwg.add(dwg.rect(insert=(405, 16), size=(248, 192), stroke = "black", fill = "black"))
		dwg.add(dwg.rect(insert=(657, 16), size=(8, 192), stroke = "black", fill = "black"))
		#dwg.add(dwg.rect(insert=(657, 16), size=(6, 6), stroke = "blue", fill = "blue"))
		#dwg.add(dwg.rect(insert=(121, 120), size=(7, 85), stroke = "rgb(50,50,50)", fill = "red"))
		dwg.add(dwg.text('Observer:', insert=(3, 11), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Country:', insert=(3, 26), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('City:', insert=(3, 41), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Antenna:', insert=(3, 56), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('RF preamp:', insert=(3, 71), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Receiver:', insert=(3, 86), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Computer:', insert=(3, 101), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Hourly count histogram', insert=(3, 146), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Updated:', insert=(3, 161), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Location:', insert=(203, 11), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Frequency:', insert=(203, 41), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Email:', insert=(203, 56), fill='#505f76', style = "font-size:10px; font-family:Arial"))
		dwg.add(dwg.text('Month:', insert=(203, 71), fill='#505f76', style = "font-size:10px; font-family:Arial"))

		dwg.add(dwg.text(self.stationName, insert=(60, 11), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationCountry, insert=(60, 26), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationCity, insert=(60, 41), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationAntenna, insert=(60, 56), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationPreAmp, insert=(60, 71), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationReciver, insert=(60, 86), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationComputer, insert=(60, 101), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(decdeg2dms(float(self.stationLat)), insert=(255, 11), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(decdeg2dms(float(self.stationLon)), insert=(255, 26), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationFreq, insert=(255, 41), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(self.stationEmail, insert=(255, 56), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str(self.genYear) + "_" + str(self.genMonth).zfill(2), insert=(255, 71), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(str(time.gmtime().tm_hour).zfill(2) + ":" + str(time.gmtime().tm_min).zfill(2) + ":" + str(time.gmtime().tm_sec).zfill(2), insert=(60, 161), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str(self.genYear).zfill(4) + "-" + str(self.genMonth).zfill(2) + "-" + str(self.genDay).zfill(2), insert=(212, 108), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(str("0h UT"), insert=(120, 216), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("24h"), insert=(350, 216), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(str("1  Days --->"), insert=(405, 11), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("15"), insert=(517, 11), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("31"), insert=(643, 11), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(str("0h"), insert=(382, 24), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("UT"), insert=(382, 39), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("12h"), insert=(382, 116), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		dwg.add(dwg.text(str("24h"), insert=(382, 207), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text(str(monthMin), insert=(667, 24), fill='#61218f', style = "font-size:12px; font-family:Arial"))
		
                dwg.add(dwg.text(".", insert=(667, 70), fill='#61218f', style = "font-size:12px; font-family:Arial"))
                dwg.add(dwg.text(".", insert=(667, 116), fill='#61218f', style = "font-size:12px; font-family:Arial"))
                dwg.add(dwg.text(".", insert=(667, 161), fill='#61218f', style = "font-size:12px; font-family:Arial"))
                dwg.add(dwg.text(str(monthMax), insert=(667, 207), fill='#61218f', style = "font-size:12px; font-family:Arial"))

		dwg.add(dwg.text("pyRMOBgen,   v1.9 - MULTIgen,   astrozor.cz", insert=(405, 218), fill='#61218f', style = "font-size:11px; font-family:Arial"))

		def getColor(value, range):
			value = value*3
			range = range*3
			if value < 0:
			#	print "hodnota min",
				red = 5
				green= 5
				blue = 5
			elif value == 0:
			#	print "hodnota = 0",
				red = 0
				green= 0
				blue = 255
			elif value <= range/3:
			#	print "hodnota 1",
				red=0
				green=int(float(value)*((float(225)/(float(range)/3))))
				blue=255
			elif value <= range/3*2:
			#	print "hodnota 2",
				red=int(float(value)*(float(255)/(float(range)/3)))-254
				green=255
				blue=int(float(range-value)*(float(255)/(float(range)/3)))-254
			elif value <= range:
			#	print "hodnota 3",
				red=255
				green=int(float(range-value)*((float(255)/(float(range)/3))))
				blue=0
			elif value >= range:
				red=250
				green=250
				blue=250
			else:
			#	print "hodnota ost",
				red = 5
				green= 5
				blue = 5
			return str("rgb("+str(red)+","+str(green)+","+str(blue)+")")


		for step in range(24):
			dwg.add(dwg.rect(insert=(657, 16+step*8), size=(8, 8), stroke = "black", fill = getColor(step+1,23+1)))

		for day in range(31):
			for hour in range(24):
				print day, hour," - ", monthDataMasked[hour][day]
				dwg.add(dwg.rect(insert=(405+day*8, 16+hour*8), size=(8, 8), stroke = "black", fill = getColor(monthDataMasked[hour][day],monthMax)))
		if self.genActual:
			dwg.add(dwg.rect(insert=(405+(time.gmtime().tm_mday-1)*8, 16+time.gmtime().tm_hour*8), size=(8, 8), stroke = "white", fill = getColor(monthDataMasked[time.gmtime().tm_hour][self.genDay],np.amax(monthDataMasked))))

		
		dwg.add(dwg.line((120,163),(365,163), stroke = "#61218f", fill = "black"))
		for todayhour in range(24):
			try:
				if monthDataMasked[todayhour][self.genDay-1] != -1:
					dwg.add(dwg.rect(insert=(123+10*todayhour, 205-85.0*(float(monthDataMasked[todayhour][self.genDay-1])/float(np.amax(monthDataMasked, axis=0)[self.genDay-1])) ), size=(8, 85.0*(float(monthDataMasked[todayhour][self.genDay-1])/float(np.amax(monthDataMasked, axis=0)[self.genDay-1])) ), stroke = "#61218f", fill = getColor(monthDataMasked[todayhour][self.genDay-1],np.amax(monthDataMasked)) ))
			except Exception, e:
				print e
		dwg.add(dwg.line((101,120),(364,120), stroke = "black", fill = "black"))
		dwg.add(dwg.text(str(np.amax(monthDataMasked, axis=0)[self.genDay-1]), insert=(101, 116), fill='#61218f', style = "font-size:10px; font-family:Arial"))

		dwg.save()
		svg = dwg.tostring()
		out=open(str(self.stationName)+'_'+   str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+".jpg",'w')
		cairosvg.svg2png(bytestring=svg,write_to=out)
		out.close()

	def rmobupload(self):
		print "upload zahajen"
		session = ftplib.FTP('217.169.242.217','radiodata','meteor')

		file0 = str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+".jpg"
		file1 =  str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+"rmob.TXT"
		file = open(file0, 'rb')
		session.storbinary('STOR /' +file0, file)
                file = open(file1, 'rb')
                session.storbinary('STOR /' +file1, file)

		file.close()
		session.quit()
