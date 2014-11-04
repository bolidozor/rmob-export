#!/usr/bin/python
import os
import datetime
import ftplib
import ConfigParser
from HTMLParser import HTMLParser
from urllib import urlopen
#import subprocess

ArrayObservator = []
ArrayHTML = []
ArrayStanice = []
ArrayRMOB = []
ArrayGenPath = []

#subprocess.Popen(['notify-send', "START OF rmob-export/Run.py"])


class MyHTMLParser(HTMLParser):
	global ArrayHTML
	#def handle_endtag(self, tag):
	#	print "Encountered an end tag :", tag
	#def handle_data(self, data):
	#	print "Encountered some data  :", data
	def handle_starttag(self, tag, attrs):
	#	print "Encountered a start tag:", tag
		if tag == "a":
			#print "tag a obsahuje odkaz",
			for name, value in attrs:
			#	print  value
				ArrayHTML.append(value)


log =open('log_AutoCron15.txt', 'at')
dir = "./io/gen"
try:
    os.stat(dir)
except:
    os.mkdir(dir)

dir = "./io/old"
try:
    os.stat(dir)
except:
    os.mkdir(dir)


url_meteors = "http://space.astro.cz/bolidozor/"
html = urlopen(url_meteors).read()

parser = MyHTMLParser()
parser.feed(html)
#ArrayHTML.remove("/")
ArrayObservator=ArrayHTML[1:]
print "----------",ArrayObservator

for observator in ArrayObservator:
	ArrayHTML=[]
	url_observator = url_meteors+observator
	html = urlopen(url_observator).read()
	parser.feed(html)
	ArrayStanice=ArrayHTML[1:]
	print "--------------------",ArrayStanice
	for stanice in ArrayStanice:
		if stanice[-1:] is "/":
			ArrayHTML=[]
			url_stanice = url_meteors+observator+stanice
			html = urlopen(url_stanice).read()
			parser.feed(html)
			ArrayRMOB=ArrayHTML[1:]
			print "-----------------------------",ArrayRMOB
			if "rmob.cfg" in ArrayRMOB:
				print "rmob.cfg found in", ArrayRMOB, url_stanice
				ArrayGenPath.append(url_stanice)
	

print ArrayGenPath


log.write('Zacatek prenosu '+ datetime.datetime.now().isoformat() + ' \n')

#os.system('./RmobGen -input-./io/Observatory.info')
for RmobStanice in ArrayGenPath:
	print "||||||||||||||||||||||||||||||||||||||||||||||||||||"
	print "Zacatek generovani pro ", RmobStanice
	log.write(' >> ' + 'Stanice: ' + RmobStanice + '\t\t ' + datetime.datetime.now().isoformat()  + ' \n')
	html = urlopen(RmobStanice+'rmob.cfg').read()
	
#	subprocess.Popen(['notify-send', "START OF rmob-export/RmobGen \n"+RmobStanice+"\n "+datetime.datetime.now().isoformat()])
	os.system('./RmobGen ' + RmobStanice)

	session = ftplib.FTP('217.169.242.217','radiodata','meteor')

	for root, dirs, file in os.walk('./io/gen'):
		for fname in file:
			full_fname = os.path.join(root, fname)
			file = open(full_fname, 'rb')
			session.storbinary('STOR /' + fname, file)
		file.close()
	session.quit()

os.system('mv ./io/gen/*TXT ./io/old/')
os.system('mv ./io/gen/*jpg ./io/old/')

log.write('Konec prenosu ' + datetime.datetime.now().isoformat()  + ' \n')
log.close()
#subprocess.Popen(['notify-send', "END OF rmob-export/Run.py"])
exit(0)
