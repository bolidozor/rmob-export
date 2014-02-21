#!/usr/bin/python
import os
import datetime
import ftplib

#dt = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

log =open('log_AutoCron15.txt', 'at')
log.write('Zacatek prenosu '+ datetime.datetime.now().isoformat() )

os.system('./RmobGen -input-./io/Observatory.info')

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
