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
import configparser
import svgwrite
import ftplib
import cairosvg

class rmob():
    def __init__(self):
        print("Rmob")
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
        print("#####################################################")
        print("#####################################################")
        print("rok:", self.genYear)
        print("mesic:", self.genMonth)
        print("den:", self.genDay)
        print("observator:", self.genObservatory)
        print("stanice:", self.genStation)
        print("data:", self.LastData)
        print("ftp:", self.ftp)
        print("cfg", self.configFiles)
        print("monthData: ", self.monthData)
        print("monthDataSize:", self.monthDataSize)
        print("StationName:", self.stationName)
        print("#####################################################")
        print("#####################################################")

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
        print("Pripojeni sftp na:", sftpUser+"@"+sftpURL, "bylo uspesne")
    
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
        print("/storage/bolidozor/" , str(self.genObservatory), "/", str(self.genStation), "/rmob.cfg")
        file = self.ftp.file("/storage/bolidozor/" + str(self.genObservatory) + "/" + str(self.genStation) + "/rmob.cfg")
        Config = configparser.ConfigParser()
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
        print("parse config file: DONE")

    def parseMonthData(self, ObservatoryName = None, StationName = None, Year = None, Month = None):
        monthPath = "/storage/bolidozor/" + self.genObservatory + "/" + self.genStation + "/data/" + str(self.genYear) + "/" + str(self.genMonth).zfill(2)
        try:
            data = np.load('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+".npz")
            self.monthData=data["monthData_"+str(self.genYear) + "_" +str(self.genMonth)]
            self.monthDataSize=data["monthDataSize_"+str(self.genYear) + "_" +str(self.genMonth)]

        except Exception as e:
            self.monthData.fill(-1)
            self.monthDataSize.fill(-1)
            print("e>", e)

        tmp = sorted(self.ftp.listdir(monthPath))
        days = []
        for tmpV in tmp:
            if tmpV.isdigit():
                days.append(tmpV) 
        for day in days:
            hours=[]
            for hour in sorted(self.ftp.listdir(monthPath+"/"+day)):
                if hour.find("meta.csv") != -1:
                    hours.append(hour)
            for hour in hours:
                if self.ftp.stat(monthPath+"/"+day+"/"+hour).st_size != self.monthDataSize[int(hour[8:10])][int(day)-1]:
                    file = self.ftp.file(monthPath+"/"+day+"/"+hour)
                    self.monthData[int(hour[8:10])][int(day)-1] = 0
                    for i in file:
                        if i.find("met") != -1:
                            self.monthData[int(hour[8:10])][int(day)-1] += 1
                    self.monthDataSize[int(hour[8:10])][int(day)-1] = self.ftp.stat(monthPath+"/"+day+"/"+hour).st_size
                    print("Hodina", hour[8:10], "NEW, MpH:",  self.monthData[int(hour[8:10])][int(day)-1], "dne:", int(day))
                else:
                    print("Hod", hour[8:10],", MpH:", self.monthData[int(hour[8:10])][int(day)-1], "dne:", int(day), "||")

                #np.savez('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+"_"+ str(self.genYear) + str(self.genMonth) +".npz", monthData=self.monthData, monthDataSize=self.monthDataSize)
                np.savez('./cache/'+str(self.genObservatory)+"_"+str(self.genStation)+".npz", **{"monthData_"+str(self.genYear) + "_" +str(self.genMonth): self.monthData, "monthDataSize_"+str(self.genYear) + "_" +str(self.genMonth): self.monthDataSize})
            print(day)
        self.LastData = True

    def getMonthData(self):
        return self.monthData

    
    def getRmobTxt(self):
        print("získávání rmox TXT souboru")
        monthDict = {1:'jan', 2:'feb', 3:'mar', 4:'apr', 5:'may', 6:'jun', 
            7:'jul', 8:'aug', 9:'sep', 10:'oct', 11:'nov', 12:'dec'}

        f = open(str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+"rmob.TXT", 'w')
        f.write(str(monthDict[self.genMonth]) + "| 00h| 01h| 02h| 03h| 04h| 05h| 06h| 07h| 08h| 09h| 10h| 11h| 12h| 13h| 14h| 15h| 16h| 17h| 18h| 19h| 20h| 21h| 22h| 23h|\n")
        for day in range(31):
            name=" "+str(day+1).zfill(2)+"|"
            for hour in range(24):
#               print "hour", hour, day
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
        f.write("[Longitude]"+str(int(deg)).zfill(3)+"d"+str(int(mnt)).zfill(2)+str(int(sec)).zfill(2)+" "+self.stationLonL+"\n")
        deg, mnt, sec = decdeg2dms(float(self.stationLat))
        f.write("[Latitude]"+str(int(deg)).zfill(3)+"d"+str(int(mnt)).zfill(2)+str(int(sec)).zfill(2)+" "+self.stationLatL+"\n")
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
        f.write("[Soft FTP]pyRMOBgen v1.10, bolidozor.cz MultiGen (RadioObserver) - https://github.com/bolidozor/rmob-export"+"\n")
        f.write("[E]"+self.stationEmail+"\n")
        f.close()

    def getRmobPlot(self):
        def decdeg2dms(dd):
            mnt, sec = divmod(dd*3600,60)
            deg, mnt = divmod(mnt, 60)
            return str(str(int(deg))+"d "+str(int(mnt))+'\" '+str(int(sec))+"\' ")

        try:
            sftp = self.ssh.open_sftp()
            monthPath = "/storage/bolidozor/" + self.genObservatory + "/" + self.genStation + "/data/" + str(self.genYear) + "/" + str(self.genMonth).zfill(2)
            localPath = str(self.genYear) + str(self.genMonth).zfill(2) + "_" + str(self.genStation) + "_badData.npy"
            print("pred ctenim -------------------", monthPath)
            
            #f = open(str(self.genYear) + str(self.genMonth).zfill(2) + "_" + str(self.genObservatory) + "_badData.npy","wb")
            sftp.get(monthPath+"/"+localPath,"./"+localPath)
            #f.close()          

            #file = self.ftp.file(monthPath+"/"+str(self.genYear) + str(self.genMonth).zfill(2) + "_" + str(self.genObservatory) + "_badData.npy")
            print("aaa")
            ##monthDataMask = np.load("./cache/"+str(self.genObservatory)+"_"+str(self.genStation)+"_dataMask_"+str(self.genYear) + "_" +str(self.genMonth)+".npy")
            monthDataMask = np.load(localPath)
            #f.close()
            sftp.close()
            print("Po cteni -------------------")
        except Exception as e:
            print("chyba - cteni mask:", e)
            monthDataMask = np.full((24,32), True, bool)

        monthDataMasked = ma.masked_array(self.monthData, np.invert(monthDataMask))

        monthMax=np.amax(monthDataMasked)
#       monthMax=int(np.median(monthDataMasked)+np.std(monthDataMasked)*5)
        monthMin= np.min(monthDataMasked[np.nonzero(monthDataMasked)])+1

        print(monthDataMask)
        print(monthDataMasked)
        
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
        dwg.add(dwg.text(str(np.amax(self.monthData)), insert=(667, 220), fill='#61218f', style = "font-size:10px; font-family:Arial"))

        dwg.add(dwg.path("M 48.96875 170.125 C 40.675247 174.50866 32.369668 179.34512 22.78125 180.25 C 18.829941 180.6229 14.897834 180.31114 11.21875 181.625 C 6.7179281 183.39665 4.071689 186.93901 3.625 192.625 C 4.082129 195.75457 4.551037 198.89676 7.875 201.34375 C 11.100399 204.18161 14.158495 203.72392 17.25 203.75 C 20.081423 203.30503 22.918577 201.93457 25.75 198.5625 C 28.190096 195.581 30.729452 192.30317 32.5 191.0625 C 36.603619 187.85305 40.625494 185.00825 44.3125 183.1875 C 44.840352 182.87168 45.866615 182.36793 45.875 182.25 C 45.978654 181.64789 43.293366 182.10116 42 182.03125 C 40.181407 182.20226 38.298818 182.52717 36.4375 182.8125 C 38.671326 180.77837 40.949935 178.83916 43.09375 176.625 C 45.126729 174.58377 46.841382 172.79531 48.96875 170.34375 C 49.02555 170.27825 48.91829 170.19631 48.96875 170.125 z M 15.90625 188.5625 L 18.875 191.5625 L 18.90625 198.3125 L 9.21875 198.375 L 9.1875 188.59375 L 15.90625 188.5625 z M 12.21875 191.625 L 12.25 195.3125 L 15.875 195.28125 L 15.875 191.625 L 12.21875 191.625 z"))
        dwg.add(dwg.path("M 62.6875 189.90625 C 62.264162 189.90626 61.932589 190.04732 61.6875 190.28125 C 61.45355 190.50407 61.343749 190.77068 61.34375 191.09375 C 61.343749 191.41683 61.45355 191.68345 61.6875 191.90625 C 61.932589 192.11793 62.264162 192.21876 62.6875 192.21875 C 63.110834 192.21876 63.462517 192.11793 63.71875 191.90625 C 63.986117 191.68345 64.124996 191.41683 64.125 191.09375 C 64.124996 190.77068 63.986117 190.50407 63.71875 190.28125 C 63.462517 190.04732 63.110834 189.90626 62.6875 189.90625 z M 40.28125 189.9375 C 39.958174 189.9486 39.655679 189.9777 39.34375 190 C 39.031815 190.0223 38.716009 190.06035 38.4375 190.09375 C 38.170128 190.12721 37.930417 190.1541 37.71875 190.1875 L 37.71875 201.71875 C 38.0084 201.78555 38.342145 201.8416 38.6875 201.875 C 39.043992 201.9084 39.384534 201.9264 39.71875 201.9375 C 40.0641 201.9598 40.366595 201.96875 40.65625 201.96875 L 41.40625 201.96875 C 41.985547 201.96875 42.547863 201.88368 43.09375 201.75 C 43.639625 201.61631 44.107906 201.43476 44.53125 201.15625 C 44.965719 200.87774 45.337511 200.49698 45.59375 200.0625 C 45.84997 199.61689 45.96874 199.10158 45.96875 198.5 C 45.96874 198.04324 45.883676 197.64672 45.75 197.3125 C 45.627446 196.97829 45.4728 196.7027 45.25 196.46875 C 45.027183 196.2348 44.769534 196.03994 44.46875 195.90625 C 44.167951 195.77257 43.834206 195.6807 43.5 195.625 L 43.5 195.53125 C 43.878768 195.44213 44.201372 195.30325 44.46875 195.125 C 44.736113 194.93561 44.957885 194.73396 45.125 194.5 C 45.292098 194.25492 45.4019 193.97716 45.46875 193.6875 C 45.546724 193.39786 45.593741 193.10216 45.59375 192.8125 C 45.593741 192.23321 45.463831 191.75378 45.21875 191.375 C 44.973652 190.99623 44.662188 190.71168 44.25 190.5 C 43.848937 190.28835 43.367344 190.1405 42.84375 190.0625 C 42.331284 189.97341 41.827127 189.93751 41.28125 189.9375 C 40.958174 189.9375 40.615459 189.9264 40.28125 189.9375 z M 56.59375 190.09375 L 56.59375 200.125 C 56.593749 200.80457 56.790786 201.29296 57.125 201.59375 C 57.459212 201.8834 57.927492 202.03125 58.5625 202.03125 C 58.952412 202.03125 59.319862 201.99535 59.6875 201.90625 C 60.05513 201.81713 60.352998 201.7141 60.53125 201.625 L 60.28125 199.9375 C 60.091859 200.0155 59.946181 200.0402 59.8125 200.0625 C 59.689951 200.0848 59.539932 200.125 59.40625 200.125 C 59.183438 200.125 59.037761 200.022 58.9375 199.84375 C 58.837234 199.66551 58.781247 199.38992 58.78125 199 L 58.78125 190.09375 L 56.59375 190.09375 z M 70.90625 190.09375 L 70.90625 193.5 C 70.683435 193.41088 70.472804 193.3459 70.25 193.3125 C 70.027187 193.268 69.720349 193.25001 69.375 193.25 C 68.127267 193.25001 67.177393 193.64653 66.53125 194.4375 C 65.885103 195.22848 65.562499 196.32403 65.5625 197.75 C 65.562499 199.22054 65.858196 200.30929 66.4375 201 C 67.016801 201.6907 67.827796 202.03125 68.875 202.03125 C 69.443158 202.03125 69.931549 201.92145 70.34375 201.6875 C 70.767081 201.44241 71.089685 201.10866 71.3125 200.71875 L 71.375 200.71875 L 71.6875 201.8125 L 73.25 201.8125 C 73.160864 201.24434 73.10488 200.7179 73.09375 200.25 C 73.08264 199.7821 73.062492 199.31165 73.0625 198.84375 L 73.0625 190.09375 L 70.90625 190.09375 z M 41.3125 191.8125 C 41.568725 191.8126 41.797295 191.8304 42.03125 191.875 C 42.265193 191.91957 42.477997 192.0136 42.65625 192.125 C 42.845632 192.23641 42.982339 192.37313 43.09375 192.5625 C 43.205147 192.7519 43.281243 192.99161 43.28125 193.28125 C 43.281243 193.71574 43.124426 194.07639 42.8125 194.34375 C 42.511702 194.61113 42.142082 194.80382 41.71875 194.9375 C 41.58506 194.9598 41.430413 194.9889 41.21875 195 C 41.018218 195.0107 40.812212 195.00001 40.65625 195 L 39.9375 195 L 39.9375 191.875 C 40.071182 191.8528 40.254907 191.85495 40.5 191.84375 C 40.745086 191.83305 41.022844 191.81251 41.3125 191.8125 z M 51.09375 193.21875 C 49.846018 193.21876 48.878205 193.60631 48.1875 194.375 C 47.496792 195.13255 47.156249 196.21017 47.15625 197.625 C 47.156249 198.28229 47.250283 198.89163 47.40625 199.4375 C 47.573355 199.98339 47.801926 200.45384 48.125 200.84375 C 48.459211 201.22253 48.884818 201.50709 49.375 201.71875 C 49.865176 201.93042 50.42532 202.03125 51.09375 202.03125 C 52.341474 202.03125 53.320427 201.6638 54 200.90625 C 54.690699 200.13756 55.031242 199.03984 55.03125 197.625 C 55.031242 196.96772 54.948348 196.35839 54.78125 195.8125 C 54.625276 195.26663 54.385565 194.81628 54.0625 194.4375 C 53.73942 194.04759 53.333922 193.74293 52.84375 193.53125 C 52.353565 193.31959 51.762171 193.21876 51.09375 193.21875 z M 78.53125 193.21875 C 77.283518 193.21876 76.315705 193.60631 75.625 194.375 C 74.934292 195.13255 74.593749 196.21017 74.59375 197.625 C 74.593749 198.28229 74.656533 198.89163 74.8125 199.4375 C 74.979605 199.98339 75.239426 200.45384 75.5625 200.84375 C 75.896711 201.22253 76.291068 201.50709 76.78125 201.71875 C 77.271426 201.93042 77.86282 202.03125 78.53125 202.03125 C 79.778974 202.03125 80.726677 201.6638 81.40625 200.90625 C 82.096949 200.13756 82.437492 199.03984 82.4375 197.625 C 82.437492 196.96772 82.354598 196.35839 82.1875 195.8125 C 82.031526 195.26663 81.791815 194.81628 81.46875 194.4375 C 81.14567 194.04759 80.740172 193.74293 80.25 193.53125 C 79.759815 193.31959 79.199671 193.21876 78.53125 193.21875 z M 94.90625 193.21875 C 93.658518 193.21876 92.690705 193.60631 92 194.375 C 91.309291 195.13255 90.968749 196.21017 90.96875 197.625 C 90.968749 198.28229 91.031533 198.89163 91.1875 199.4375 C 91.354606 199.98339 91.614426 200.45384 91.9375 200.84375 C 92.271711 201.22253 92.666068 201.50709 93.15625 201.71875 C 93.646426 201.93042 94.23782 202.03125 94.90625 202.03125 C 96.153974 202.03125 97.132927 201.6638 97.8125 200.90625 C 98.503199 200.13756 98.843742 199.03984 98.84375 197.625 C 98.843742 196.96772 98.760849 196.35839 98.59375 195.8125 C 98.437776 195.26663 98.198065 194.81628 97.875 194.4375 C 97.55192 194.04759 97.146422 193.74293 96.65625 193.53125 C 96.166065 193.31959 95.574671 193.21876 94.90625 193.21875 z M 104.25 193.25 C 103.81552 193.25001 103.44807 193.37095 103.125 193.59375 C 102.80192 193.81657 102.53313 194.11906 102.34375 194.53125 L 102.28125 194.53125 L 102.03125 193.4375 L 100.34375 193.4375 L 100.34375 201.8125 L 102.5 201.8125 L 102.5 196.40625 C 102.58912 196.08318 102.77502 195.82554 103.03125 195.625 C 103.29862 195.41334 103.64133 195.31251 104.03125 195.3125 C 104.30976 195.31251 104.62339 195.34621 104.96875 195.46875 L 105.25 193.4375 C 104.88236 193.31498 104.53965 193.25001 104.25 193.25 z M 61.65625 193.4375 L 61.65625 201.8125 L 63.8125 201.8125 L 63.8125 193.4375 L 61.65625 193.4375 z M 83.40625 193.4375 L 83.40625 195.28125 L 87.53125 195.28125 L 86.6875 196 L 83.40625 199.96875 L 83.40625 201.8125 L 89.9375 201.8125 L 89.9375 199.96875 L 85.84375 199.96875 L 86.6875 199.3125 L 89.9375 195.28125 L 89.9375 193.4375 L 83.40625 193.4375 z M 51.09375 195.0625 C 51.706469 195.06251 52.150014 195.30222 52.40625 195.78125 C 52.662474 196.24915 52.812493 196.85632 52.8125 197.625 C 52.812493 198.51624 52.653505 199.15031 52.375 199.5625 C 52.096484 199.9747 51.661907 200.1875 51.09375 200.1875 C 50.792954 200.1875 50.535305 200.12254 50.3125 200 C 50.100828 199.86631 49.946182 199.7027 49.8125 199.46875 C 49.678811 199.2348 49.56684 198.93694 49.5 198.625 C 49.433156 198.31307 49.406247 197.99264 49.40625 197.625 C 49.406247 196.71149 49.542955 196.05731 49.84375 195.65625 C 50.144538 195.2552 50.559005 195.06251 51.09375 195.0625 z M 78.53125 195.0625 C 79.143969 195.06251 79.587514 195.30222 79.84375 195.78125 C 80.099974 196.24915 80.218744 196.85632 80.21875 197.625 C 80.218744 198.51624 80.059755 199.15031 79.78125 199.5625 C 79.502734 199.9747 79.099407 200.1875 78.53125 200.1875 C 78.230454 200.1875 77.972805 200.12254 77.75 200 C 77.538328 199.86631 77.352432 199.7027 77.21875 199.46875 C 77.085061 199.2348 76.97309 198.93694 76.90625 198.625 C 76.839406 198.31307 76.812497 197.99264 76.8125 197.625 C 76.812497 196.71149 76.980455 196.05731 77.28125 195.65625 C 77.582038 195.2552 77.996505 195.06251 78.53125 195.0625 z M 94.90625 195.0625 C 95.518969 195.06251 95.962514 195.30222 96.21875 195.78125 C 96.474974 196.24915 96.593744 196.85632 96.59375 197.625 C 96.593744 198.51624 96.466005 199.15031 96.1875 199.5625 C 95.908984 199.9747 95.474408 200.1875 94.90625 200.1875 C 94.605454 200.1875 94.347805 200.12254 94.125 200 C 93.913328 199.86631 93.727432 199.7027 93.59375 199.46875 C 93.460062 199.2348 93.37934 198.93694 93.3125 198.625 C 93.245656 198.31307 93.218747 197.99264 93.21875 197.625 C 93.218747 196.71149 93.355455 196.05731 93.65625 195.65625 C 93.957038 195.2552 94.371505 195.06251 94.90625 195.0625 z M 69.65625 195.09375 C 69.957037 195.09376 70.185608 195.1207 70.375 195.1875 C 70.564382 195.24321 70.750278 195.31496 70.90625 195.4375 L 70.90625 199 C 70.80598 199.38992 70.620084 199.69459 70.375 199.90625 C 70.129906 200.10678 69.798332 200.1875 69.375 200.1875 C 68.829114 200.1875 68.443727 199.96573 68.1875 199.53125 C 67.942408 199.09677 67.812497 198.52549 67.8125 197.8125 C 67.812497 196.80987 67.949205 196.0997 68.25 195.6875 C 68.561928 195.27531 69.043522 195.09376 69.65625 195.09375 z M 39.9375 196.75 L 41.15625 196.75 C 41.445897 196.75 41.741594 196.7791 42.03125 196.8125 C 42.320896 196.84593 42.578545 196.90871 42.8125 197.03125 C 43.046443 197.14266 43.230167 197.31959 43.375 197.53125 C 43.519818 197.74292 43.593743 198.00737 43.59375 198.375 C 43.593743 198.66466 43.528788 198.94459 43.40625 199.15625 C 43.283698 199.36792 43.138021 199.54268 42.9375 199.6875 C 42.736966 199.82119 42.486115 199.90195 42.21875 199.96875 C 41.962515 200.03561 41.684756 200.0625 41.40625 200.0625 L 41.03125 200.0625 C 40.88642 200.0518 40.738572 200.0625 40.59375 200.0625 C 40.460061 200.0514 40.310042 200.04235 40.1875 200.03125 C 40.064952 200.02015 39.9932 199.99105 39.9375 199.96875 L 39.9375 196.75 z "))
        dwg.add(dwg.text("pyRMOBgen,   v1.10 - MULTIgen,   bolidozor.cz", insert=(405, 218), fill='#61218f', style = "font-size:11px; font-family:Arial"))

        def getColor(value, range):
            value = value*3
            range = range*3
            if value < 0:
            #   print "hodnota min",
                red = 5
                green= 5
                blue = 5
            elif value == 0:
            #   print "hodnota = 0",
                red = 0
                green= 0
                blue = 255
            elif value <= range/3:
            #   print "hodnota 1",
                red=0
                green=int(float(value)*((float(225)/(float(range)/3))))
                blue=255
            elif value <= range/3*2:
            #   print "hodnota 2",
                red=int(float(value)*(float(255)/(float(range)/3)))-254
                green=255
                blue=int(float(range-value)*(float(255)/(float(range)/3)))-254
            elif value <= range:
            #   print "hodnota 3",
                red=255
                green=int(float(range-value)*((float(255)/(float(range)/3))))
                blue=0
            elif value >= range:
                red=250
                green=250
                blue=250
            else:
            #   print "hodnota ost",
                red = 5
                green= 5
                blue = 5
            return str("rgb("+str(red)+","+str(green)+","+str(blue)+")")

    # Vygenerovat barevnou skalu
        for step in range(24):
            dwg.add(dwg.rect(insert=(657, 16+step*8), size=(8, 8), stroke = "black", fill = getColor(step+1,23+1)))


    # Generovat ctverecky pro kazdy den
        for day in range(31):
            print("day:", day)
            for hour in range(24):
                #print day, hour," - ", monthDataMasked[hour][day]
                if monthDataMask[hour][day] != False:
                    dwg.add(dwg.rect(insert=(405+day*8, 16+hour*8), size=(8, 8), stroke = "black", fill = getColor(monthDataMasked[hour][day],monthMax)))
                else:
                    dwg.add(dwg.rect(insert=(405+day*8, 16+hour*8), size=(8, 8), stroke = "black", fill = "white"))
                    dwg.add(dwg.line((405+day*8, 16+hour*8),(405+day*8+8, 16+hour*8+8), stroke="black", stroke_width=1.5))
                    dwg.add(dwg.line((405+day*8+8, 16+hour*8),(405+day*8, 16+hour*8+8), stroke="black", stroke_width=1.5))

    # Oznacit aktualni cas (posledni hodina v ramecku)
        if self.genActual:
            dwg.add(dwg.rect(insert=(405+(time.gmtime().tm_mday-1)*8, 16+time.gmtime().tm_hour*8), size=(8, 8), stroke = "white", fill = getColor(monthDataMasked[time.gmtime().tm_hour][self.genDay],np.amax(monthDataMasked))))

    
    # Vykresli denni histogram predchoziho dne
        for todayhour in range(24):
            try:
                if monthDataMasked[todayhour][self.genDay-2] != -1:
                    if monthDataMask[todayhour][self.genDay-2] != False:
                        today_max = float(np.amax(monthDataMasked, axis=0)[self.genDay-1])
                        yestearday_max = float(np.amax(monthDataMasked, axis=0)[self.genDay-2])
                        height_value = float(monthDataMasked[todayhour][self.genDay-2])/today_max if float(monthDataMasked[todayhour][self.genDay-2])/today_max<1 else 1
                        dwg.add(dwg.rect(insert=(123+10*todayhour, 205-95.0*height_value), size=(8, 95.0*height_value), stroke = "#61218f", fill = getColor(monthDataMasked[todayhour][self.genDay-2],np.amax(monthDataMasked)), opacity = 0.2 ))

            except Exception as e:
                print(e)

    # Nakreslit caru ukazujici stredni hodnotu
        dwg.add(dwg.line((120,163),(365,163), stroke = "#61218f", fill = "black"))

    # Nakreslit dnesni historam
        for todayhour in range(24):
            try:
                if monthDataMasked[todayhour][self.genDay-1] != -1:
                    if monthDataMask[todayhour][self.genDay-1] != False:
                        dwg.add(dwg.rect(insert=(123+10*todayhour, 205-85.0*(float(monthDataMasked[todayhour][self.genDay-1])/float(np.amax(monthDataMasked, axis=0)[self.genDay-1])) ), size=(8, 85.0*(float(monthDataMasked[todayhour][self.genDay-1])/float(np.amax(monthDataMasked, axis=0)[self.genDay-1])) ), stroke = "#61218f", fill = getColor(monthDataMasked[todayhour][self.genDay-1],np.amax(monthDataMasked)) ))
                    else:
                        dwg.add(dwg.rect(insert=(123+10*todayhour, 110), size=(8, 205 ), stroke = "#61218f", fill = "white" ))
                    #   dwg.add(dwg.line(123+10*todayhour, 110),123+10*todayhour, 110)))
            except Exception as e:
                print(e)
        dwg.add(dwg.line((101,120),(364,120), stroke = "black", fill = "black", style = 'stroke-dasharray: 1 4;'))
        dwg.add(dwg.text(str(np.amax(monthDataMasked, axis=0)[self.genDay-1]), insert=(101, 116), fill='#61218f', style = "font-size:10px; font-family:Arial"))

        dwg.save()
        file = str(self.stationName)+"_"+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)
        print(">>>>", self.stationName)
        print(os.getcwd())
        cairosvg.svg2png(url=file+'.svg', write_to=file+'.jpg') 
        print("Svg to jpg")

        #svg = dwg.tostring()
        #out=open(str(self.stationName)+'_'+   str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+".jpg",'w')
        #cairosvg.svg2png(bytestring=svg,write_to=out)
        #out.close()
        

    def rmobupload(self):
        print("upload zahajen")
        session = ftplib.FTP('217.169.242.217','radiodata','meteor')

        file0 = str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+".jpg"
        file1 = str(self.stationName)+'_'+str(self.genMonth).zfill(2)+str(self.genYear).zfill(2)+"rmob.TXT"
        print("Upload:", file0)
        file = open(file0, 'rb')
        session.storbinary('STOR /' +file0, file)
        file = open(file1, 'rb')
        session.storbinary('STOR /' +file1, file)

        file.close()
        session.quit()
