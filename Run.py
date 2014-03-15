#!/usr/bin/python
import os
import datetime
import ftplib
import ConfigParser
from HTMLParser import HTMLParser
from urllib import urlopen

ArrayObservator = []
ArrayHTML = []
ArrayStanice = []
ArrayRMOB = []
ArrayGenPath = []

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


url_meteors = "http://space.astro.cz/meteors/"
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
		ArrayHTML=[]
		url_stanice = url_meteors+observator+stanice
		html = urlopen(url_stanice).read()
		parser.feed(html)
		ArrayRMOB=ArrayHTML[1:]
		print "-----------------------------",ArrayRMOB
		if "rmob.cfg" in ArrayRMOB:
			ArrayGenPath.append(url_stanice)
	

print ArrayGenPath


log.write('Zacatek prenosu '+ datetime.datetime.now().isoformat() )

#os.system('./RmobGen -input-./io/Observatory.info')
for RmobStanice in ArrayGenPath:
	print "||||||||||||||||||||||||||||||||||||||||||||||||||||"
	print "Zacatek generovani pro ", RmobStanice
	html = urlopen(RmobStanice+'rmob.cfg').read()

	os.system('./RmobGen ' + RmobStanice)
	

#session = ftplib.FTP('217.169.242.217','radiodata','meteor')

#for root, dirs, file in os.walk('./io/gen'):
#	for fname in file:
#		full_fname = os.path.join(root, fname)
#		file = open(full_fname, 'rb')
#		session.storbinary('STOR /' + fname, file)
#		file.close()
#session.quit()

os.system('mv ./io/gen/*TXT ./io/old/')
os.system('mv ./io/gen/*jpg ./io/old/')

log.write(' >> ' + datetime.datetime.now().isoformat()  + ' - konec prenosu \n')
log.close()
exit(0)
